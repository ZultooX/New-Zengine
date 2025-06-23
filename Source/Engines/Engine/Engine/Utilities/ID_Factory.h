#pragma once

#include <vector>

namespace Zengine
{
	class ID_Factory
	{
	public:
		static size_t GenerateID();

	private:
		static std::vector<size_t> generatedIDs;
	};
}