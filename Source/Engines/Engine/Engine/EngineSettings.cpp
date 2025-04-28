#include "EngineSettings.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <External/nlohmann/json.hpp>

const Vector2i& EngineSettings::GetResolution() const{ return data.Resolution; }
void EngineSettings::SetResolution(const Vector2i& aResolution)
{
	data.Resolution = aResolution;
	Save();
}

const std::wstring& EngineSettings::GetEngineName() const{ return data.engineName; }
void EngineSettings::SetEngineName(const std::wstring& anEngineName)
{
	data.engineName = anEngineName;
	Save();
}

const std::wstring& EngineSettings::GetWindowName() const{ return data.windowName; }
void EngineSettings::SetWindowName(const std::wstring& anWindowName)
{
	data.windowName = anWindowName;
	Save();
}

void EngineSettings::Save()
{
	std::ofstream file(engineSettingsPath);

	nlohmann::json json;
	json["Resolution"] = { data.Resolution.x, data.Resolution.y };
	json["EngineName"] = std::string(data.engineName.begin(), data.engineName.end());
	json["WindowName"] = std::string(data.windowName.begin(), data.windowName.end());
	json["MaxAnimationBones"] = data.maxAnimationBones;

	file << json.dump(4);
	file.close();
}

void EngineSettings::Load()
{
	std::ifstream file(engineSettingsPath);
	if (!file.is_open())
	{
		CreateFile();
		return;
	}

	std::stringstream buff;
	buff << file.rdbuf();
	std::string jsonString = buff.str();

	nlohmann::json json = nlohmann::json::parse(jsonString);

	data.Resolution.x = json["Resolution"][0];
	data.Resolution.y = json["Resolution"][1];

	std::string name = json["EngineName"];
	data.engineName = std::wstring(name.begin(), name.end());

	name = json["WindowName"];
	data.windowName = std::wstring(name.begin(), name.end());

	data.maxAnimationBones = json["MaxAnimationBones"];

}

void EngineSettings::CreateFile()
{
	std::ofstream file(engineSettingsPath);
	data = EngineSettingsData();

	Save();
}
