#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

enum class EntityType : int64_t { Default, Artist, Playlist, Track };

class EntityId {
public:
	static constexpr int64_t Invalid = -1;

	EntityId() = default;
	EntityId(const int64_t value);

	operator int64_t() const;
	bool operator==(EntityId other) const;
	bool operator!=(EntityId other) const;
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
};

class TrackId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
	using EntityId::operator int64_t;
};

class PlaylistId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
	using EntityId::operator int64_t;
};

#endif // TYPES_H
