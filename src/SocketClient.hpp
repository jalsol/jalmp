#ifndef SOCKETCLIENT_HPP
#define SOCKETCLIENT_HPP

#include "epoll/epoll.hpp"
#include "socket/socket.hpp"

#include <QString>
#include <optional>
#include <string_view>

enum class RequestType { Audio, Lyrics };

class SocketClient {
public:
	static SocketClient& instance();

	SocketClient(const SocketClient&) = delete;
	SocketClient& operator=(const SocketClient&) = delete;
	SocketClient(SocketClient&&) = delete;
	SocketClient& operator=(SocketClient&&) = delete;

	std::optional<QString> sendRequest(RequestType requestType,
									   const QString& request);

private:
	SocketClient(std::string_view host, std::string_view port);

	std::string_view mHost;
	std::string_view mPort;
	Socket mServerSock{};
	EpollInstance mEpoll{};
	bool mConnected = false;

	void init();
	std::optional<std::string> readData();
	std::optional<QPair<qint64, std::string>> readStreamSize();
	void retryConnection();
};

#endif // SOCKETCLIENT_HPP
