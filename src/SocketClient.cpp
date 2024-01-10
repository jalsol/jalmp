#include "SocketClient.hpp"

#include "jalsock.hpp"
#include "types/addr_info.hpp"

#include <QDebug>
#include <fstream>

SocketClient& SocketClient::instance() {
	static SocketClient instance{"localhost", "8080"};
	return instance;
}

SocketClient::SocketClient(std::string_view host, std::string_view port)
	: mHost{host}, mPort{port} {}

void SocketClient::init() {
	if (mConnected) {
		return;
	}

	qDebug() << "initializing socket client";

	AddrInfo hints;
	hints.setFamily(AIFamily::Unspec).setSocket(AISockType::Stream);

	const auto& [error, addresses] =
		jalsock::getAddressInfo(mHost, mPort, hints);

	if (error != ErrAI::Success) {
		qDebug() << "Can't get address info: "
				 << gai_strerror(static_cast<int>(error));
		mConnected = false;
		return;
	}

	for (const auto& address : addresses) {
		Socket socket(address.family(), address.sockType(), address.protocol());

		if (socket.error()) {
			qDebug() << "Can't create socket: " << std::strerror(errno);
			continue;
		}

		if (!jalsock::connect(socket, address)) {
			qDebug() << "Can't connect socket: " << std::strerror(errno);
			continue;
		}

		mServerSock = std::move(socket);
		break;
	}

	if (mServerSock.error()) {
		qDebug() << "Can't connect socket";
		mConnected = false;
		return;
	}

	mEpoll.add(mServerSock.fd(), EpollEventFlag::In);
	mEpoll.add(STDIN_FILENO, EpollEventFlag::In);
	qDebug() << "socket client initialized";

	mConnected = true;
}

std::optional<QString> SocketClient::sendRequest(RequestType requestType,
												 const QString& request) {
	retryConnection();

	QString fileName = "../../";
	switch (requestType) {
	case RequestType::Audio:
		fileName += QString{"audio.mp3"};
		break;
	case RequestType::Lyrics:
		fileName += QString{"lyrics.txt"};
		break;
	default:
		__builtin_unreachable();
	}

	qDebug() << "Sending request: " << request;

	if (!jalsock::send(mServerSock.fd(), request.toStdString(), 0)) {
		qDebug() << "Can't send data: " << std::strerror(errno);
		mConnected = false;
		return std::nullopt;
	}

	// first response is the file size
	const auto& fileSize_opt = readStreamSize();
	if (!fileSize_opt) {
		qDebug() << "Can't read file size";
		mConnected = false;
		return std::nullopt;
	}

	const auto& [fileSize, remainingData] = *fileSize_opt;
	qDebug() << "File size: " << fileSize;
	qDebug() << "Remaining data size: " << remainingData.size();

	std::ofstream outFile{fileName.toStdString(), std::ios::binary};
	if (!outFile) {
		qDebug() << "Can't open file: " << std::strerror(errno);
		mConnected = false;
		return std::nullopt;
	}

	outFile.write(remainingData.data(), remainingData.size());
	outFile.seekp(0, std::ios::end);
	qint64 bytesReceived = remainingData.size();

	while (bytesReceived < fileSize) {
		const auto& data_opt = readData();
		if (!data_opt) {
			qDebug() << "Can't read data: " << std::strerror(errno);
			mConnected = false;
			return std::nullopt;
		}

		const auto& data = *data_opt;
		outFile.write(data.data(), data.size());
		bytesReceived += data.size();

		qDebug() << "Received " << bytesReceived << " bytes";
		outFile.seekp(0, std::ios::end);
	}

	return fileName;
}

std::optional<std::string> SocketClient::readData() {
	qDebug() << "Reading data";
	const auto& recv_opt = jalsock::recv(mServerSock.fd(), 0);

	if (!recv_opt) {
		qDebug() << "Can't receive data: " << std::strerror(errno);
		mConnected = false;
		return std::nullopt;
	}

	return *recv_opt;
}

std::optional<QPair<qint64, std::string>> SocketClient::readStreamSize() {
	const auto& recv_opt = jalsock::recv(mServerSock.fd(), 0);
	if (!recv_opt) {
		return std::nullopt;
	}

	const auto& data = *recv_opt;

	// the first 8 bytes are the file size,
	// the rest is a part of the file itself

	if (data.size() < 8) {
		qDebug() << "Can't read file size";
		mConnected = false;
		return std::nullopt;
	}

	const auto& fileSize = *reinterpret_cast<const qint64*>(data.data());
	const auto& remainingData = data.substr(sizeof(qint64));
	return QPair<qint64, std::string>{fileSize, remainingData};
}

void SocketClient::retryConnection() {
	for (int _ = 0; _ < 10 && !mConnected; ++_) {
		init();
	}
}
