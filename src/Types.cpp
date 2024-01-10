#include "Types.hpp"

EntityId::EntityId(int64_t value) : mValue(value) {}

EntityId::operator int64_t() const { return mValue; }

// bool EntityId::operator==(EntityId other) const {
// 	return mValue == other.mValue;
// }

// bool EntityId::operator!=(EntityId other) const {
// 	return mValue != other.mValue;
// }

bool EntityId::operator==(int64_t value) const { return mValue == value; }

bool EntityId::operator!=(int64_t value) const { return mValue != value; }
