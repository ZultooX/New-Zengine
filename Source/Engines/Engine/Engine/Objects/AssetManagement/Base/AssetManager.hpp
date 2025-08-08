#pragma once

#include <typeindex>
#include <type_traits>

#include <Engine/Objects/Base/List.hpp>
#include <Engine/Objects/Base/AssetPointer.hpp>

#include <Engine/Objects/AssetManagement/AssetLoaders/Texture2DLoader.h>
#include <Engine/Objects/AssetManagement/Assets/Texture/Texture2D.h>

#include <Engine/Objects/AssetManagement/Assets/Mesh.h>
#include <Engine/Objects/AssetManagement/AssetLoaders/MeshLoader.h>

#include <Engine/Objects/AssetManagement/Assets/Shaders/PixelShader.h>
#include <Engine/Objects/AssetManagement/AssetLoaders/PixelShaderLoader.h>

#include <Engine/Objects/AssetManagement/Assets/Shaders/VertexShader.h>
#include <Engine/Objects/AssetManagement/AssetLoaders/VertexShaderLoader.h>

#include <Engine/Objects/AssetManagement/Assets/Material.h>
#include <Engine/Objects/AssetManagement/AssetLoaders/MaterialLoader.h>

namespace Zengine
{
	class AssetManager final
	{
	public:
		template<typename T>
		AssetPointer<T> Get(const char* path);

		template<typename T>
		AssetPointer<T> Get(const char* path, const size_t& id);

	private:
		template<typename T>
		AssetPointer<T> Load(const char* path, const size_t& id);

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

		return Get<T>(id);
	}

	template<typename T>
	inline AssetPointer<T> AssetManager::Get(const char* path, const size_t& id)
	{
		List<T>* list = GetOrCreateList<T>();
		if (list->Exists(id))
		{
			T& t = list->GetOrAdd(id);
			return AssetPointer<T>(t.GetID(), list);
		}

		return Load<T>(path, id);
	}

	template<typename T>
	inline AssetPointer<T> AssetManager::Load(const char* path, const size_t& id)
	{
		List<T>* list = GetOrCreateList<T>();
		T& t = list->GetOrAdd(id);
		if constexpr (std::is_same<T, Mesh>::value) MeshLoader::Load(path, t);
		else if constexpr (std::is_same<T, Texture2D>::value) Texture2DLoader::Load(path, t);
		else if constexpr (std::is_same<T, Material>::value) MaterialLoader::Load(id, t);
		else if constexpr (std::is_same<T, VertexShader>::value) VertexShaderLoader::Load(path, t);
		else if constexpr (std::is_same<T, PixelShader>::value) PixelShaderLoader::Load(path, t);

		return AssetPointer<T>(t.GetID(), list);
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
}