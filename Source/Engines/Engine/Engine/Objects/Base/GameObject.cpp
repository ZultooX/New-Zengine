#include "Object.h"

#include <Engine/Utilities/ID_Factory.h>

namespace Zengine
{
	Object::Object() : id(ID_Factory::GenerateID()) {}
	Object::Object(const size_t& _id) : id(_id) {}

	const std::string& Object::GetName() const { return name; }
	void Object::SetName(const std::string& _name) { name = _name; }

	const size_t& Object::GetID() const { return id; }
	void Object::SetID(const size_t& _id) { id = _id; }

	bool Object::GetFlag(const int& idx) { return flags.GetBit(idx); }
	void Object::SetFlag(const int& idx, const bool& state) { flags.SetBit(idx, state); }

	const std::string& Object::ToString() const { return name; }
}