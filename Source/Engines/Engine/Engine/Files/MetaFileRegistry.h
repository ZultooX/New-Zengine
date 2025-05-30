#pragma once

#include <string>
#include <nlohmann/json.hpp>

class MetaFileRegistry {
public:
	static void Load();
	static void Unload();

public:
	template<typename T>
	static T GetMetaData(const std::string& aFilePath, const std::string& aDataThingie);

	template<typename T>
	static void SetMetaData(const std::string& aFilePath, const std::string& aDataThingie, const T& someData);

	static void ValidateFiles();
private:
	static nlohmann::json MetaFileJson;
};

template<typename T>
inline T MetaFileRegistry::GetMetaData(const std::string& aFilePath, const std::string& aDataThingie)
{
	nlohmann::json& meta = MetaFileJson[aFilePath];

	return meta[aDataThingie  ];
}

template<typename T>
inline void MetaFileRegistry::SetMetaData(const std::string& aFilePath, const std::string& aDataThingie, const T& someData)
{
	MetaFileJson[aFilePath][aDataThingie] = someData;
}