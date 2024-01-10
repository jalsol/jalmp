#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

enum class EntityType : int64_t { Default, Artist, Playlist, Track };

enum QueueType { Invalid = -1, User, System };

class EntityId {
public:
	static constexpr int64_t Invalid = -1;

	EntityId() = default;
	EntityId(const int64_t value);

	operator int64_t() const;
	// bool operator==(EntityId other) const;
	// bool operator!=(EntityId other) const;
	bool operator==(int64_t value) const;
	bool operator!=(int64_t value) const;

protected:
	int64_t mValue = Invalid;
};

class ArtistId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
	using EntityId::operator int64_t;
	using EntityId::operator==;
	using EntityId::operator!=;
};

class TrackId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
	using EntityId::operator int64_t;
	using EntityId::operator==;
	using EntityId::operator!=;
};

class PlaylistId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
	using EntityId::operator int64_t;
	using EntityId::operator==;
	using EntityId::operator!=;

	static constexpr int64_t UserQueue = -2;
	static constexpr int64_t Favorites = -3;
	static constexpr int64_t Search = -4;
	static constexpr int64_t Tracklist = -5;
};

#endif // TYPES_H
