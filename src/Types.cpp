#include "Types.hpp"

EntityId::EntityId(int64_t value) : mValue(value) {}

EntityId::operator int64_t() const { return mValue; }

bool EntityId::operator==(const EntityId& other) const {
	return mValue == other.mValue;
}

bool EntityId::operator<(const EntityId& other) const {
	return mValue < other.mValue;
}
