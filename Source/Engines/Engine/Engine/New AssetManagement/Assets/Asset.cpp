#include "Asset.h"

void Asset::SetID(const size_t& aID) { myID = aID; }

const size_t& Asset::GetID() const { return myID; }

const std::string& Asset::GetName() const { return myName; }

void Asset::SetName(const std::string& aName) { myName = aName; }
