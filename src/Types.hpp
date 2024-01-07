#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

class EntityId {
public:
	static constexpr int64_t Invalid = -1;

	EntityId() = default;
	EntityId(const int64_t value);

	operator int64_t() const;
	bool operator==(const EntityId& other) const;
	bool operator<(const EntityId& other) const;

protected:
	int64_t mValue = Invalid;
};

class ArtistId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
};

class TrackId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
};

class PlaylistId : public EntityId {
public:
	using EntityId::EntityId;
	using EntityId::Invalid;
};

#endif // TYPES_H
