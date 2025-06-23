#include "Asset.h"

namespace Zengine
{
	Asset::Asset() : Object() {}
	Asset::Asset(const size_t& _id) : Object(_id) {}

	const std::string& Asset::GetPath() const { return path; }
	void Asset::SetPath(const std::string& _path) { path = _path; }
}