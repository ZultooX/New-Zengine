#pragma once

#include <typeindex>

#include <Engine/Objects/Base/List.hpp>
#include <Engine/Objects/Base/AssetPointer.hpp>

#include <Engine/Objects/AssetManagement/AssetLoaders/Texture2DLoader.h>
#include <Engine/Objects/AssetManagement/Assets/Texture/Texture2D.h>
#include <Engine/Objects/AssetManagement/Assets/Mesh.h>
#include <Engine/Objects/AssetManagement/AssetLoaders/MeshLoader.h>

namespace Zengine
{
	class AssetManager final
	{
	public:
		template<typename T>
		AssetPointer<T> Get(const char* path);

	private:
		template<typename T>
		AssetPointer<T> Load(const char* path);

		template<> AssetPointer<Texture2D> Load(const char* path);
		template<> AssetPointer<Mesh> Load(const char* path);

	private:
		template<typename T>
		List<T>* GetOrCreateList();

	private:	
		std::unordered_map<std::type_index, BaseList*> lists;
	};

	template<typename T>
	inline AssetPointer<T> AssetManager::Get(const char* path)
	{
		const std::type_index type = typeid(T);
		List<T>* list = GetOrCreateList<T>();

		const size_t id = std::hash<std::string>{}(std::string(path));
		if (list->Exists(id))
		{
			return AssetPointer<T>(list->GetOrAdd(id));
		}

		return Load<T>(path);
	}

	template<typename T>
	inline List<T>* AssetManager::GetOrCreateList()
	{
		const std::type_index type = typeid(T);

		if (lists.find(type) == lists.end())
		{
			lists[type] = new List<T>();
		}

		return lists[type];
	}









	template<>
	inline AssetPointer<Texture2D> AssetManager::Load(const char* path)
	{
		const size_t id = std::hash<std::string>{}(std::string(path));

		List<Texture2D>* list = GetOrCreateList<Texture2D>();
		Texture2D& texture = list->GetOrAdd(id);

		Texture2DLoader::Load(path, texture);

		return AssetPointer<Texture2D>(texture.GetID(), list);
	}

	template<>
	inline AssetPointer<Mesh> AssetManager::Load(const char* path)
	{
		const size_t id = std::hash<std::string>{}(std::string(path));

		List<Mesh>* list = GetOrCreateList<Mesh>();
		Mesh& mesh = list->GetOrAdd(id);

		MeshLoader::Load(path, mesh);

		return AssetPointer<Mesh>(mesh.GetID(), list);
	}
}