#pragma once

#include <Zultools/Math/Vector2.hpp>
#include <string>


struct EngineSettingsData {
	Vector2i Resolution = { 1280, 720 };
	int maxAnimationBones = 64;

	std::wstring engineName = L"Zulle";
	std::wstring windowName = L"Zengine";
};

struct EngineSettings 
{
	friend class Engine;

public:
	const Vector2i& GetResolution() const;
	void SetResolution(const Vector2i& aResolution);

	const std::wstring& GetEngineName() const;
	void SetEngineName(const std::wstring& anEngineName);

	const std::wstring& GetWindowName() const;
	void SetWindowName(const std::wstring& anWindowName);

	void Save();

private:
	EngineSettingsData data;

private:
	const std::string engineSettingsPath = "Settings/Engine.ini";

	void Load();
	void CreateFile();
};