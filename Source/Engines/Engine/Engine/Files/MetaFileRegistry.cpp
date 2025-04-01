#include "MetaFileRegistry.h"

#include <fstream>

nlohmann::json MetaFileRegistry::MetaFileJson;

void MetaFileRegistry::Load()
{
	std::fstream file(ZENGINE_SETTINGS_PATH "meta.ini", std::ios::binary);
	
	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string jsonString = buffer.str();
	if (jsonString.empty()) return;
 
	MetaFileJson = nlohmann::json::parse(jsonString);
}

void MetaFileRegistry::Unload()
{
	std::string jsonString = MetaFileJson.dump(4);
	std::ofstream file(ZENGINE_SETTINGS_PATH "meta.ini", std::ios::binary);
	file << jsonString;
}

void MetaFileRegistry::ValidateFiles()
{
	for (auto it = MetaFileJson.begin(); it != MetaFileJson.end(); it++)
	{
		std::fstream file(it.key());
		if (!file.is_open()) MetaFileJson.erase(it);
	}
}
