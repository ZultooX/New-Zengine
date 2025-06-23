#include "ID_Factory.h"

#include <random>

namespace Zengine
{
	std::vector<size_t> ID_Factory::generatedIDs;

	size_t ID_Factory::GenerateID()
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<size_t> dist(std::numeric_limits<size_t>::min(), std::numeric_limits<size_t>::max());

		size_t id = dist(mt);
		bool exists = true;
		while (exists)
		{
			if (generatedIDs.size() == 0) break;

			for (int i = 0; i < generatedIDs.size(); i++)
			{
				if (generatedIDs[i] == id)
				{
					id = dist(mt);
					break;
				}

				if (i == generatedIDs.size() - 1) exists = false;
			}
		}

		generatedIDs.push_back(id);
		return id;
	}
}