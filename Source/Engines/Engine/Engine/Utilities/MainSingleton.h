#pragma once

#include <unordered_map>
#include <typeinfo>
#include <assert.h>
#include <string>
#include <stdexcept>

class MainSingleton
{
public:
	static void Setup();

	template<typename T>
	static T& GetInstance();

	static const bool& IsSetup();

private:
	template <typename T>
	static void RegisterInstance();

private:
	static std::unordered_map<std::string, void*> mySingletons;
	static bool myIsInitialized;
};

template<typename T>
inline T& MainSingleton::GetInstance()
{
	auto it = mySingletons.find(typeid(T).name());  
	if (it != mySingletons.end()) {
		return *(static_cast<T*>(it->second));
	}

	assert("Singleton not registered.");
	throw std::runtime_error("Singleton not registered.");
}

template<typename T>
inline void MainSingleton::RegisterInstance()
{
	mySingletons[typeid(T).name()] = static_cast<void*>(new T);
}
