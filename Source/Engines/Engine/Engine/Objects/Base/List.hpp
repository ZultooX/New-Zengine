#pragma once

#include <vector>
#include <unordered_map>

namespace Zengine
{
	class BaseList {};

	template<typename T>
	class List final : public BaseList
	{
	public:
		T& GetOrAdd(const size_t& id);
		void Remove(const size_t& id);

		bool Exists(const size_t& id);

	private:
		void Add(const size_t& id);

	private:
		std::unordered_map<size_t, unsigned> idToIdx;
		std::vector<T> list;
	};

	template<typename T>
	inline T& List<T>::GetOrAdd(const size_t& id)
	{
		if (idToIdx.find(id) == idToIdx.end())
		{
			Add(id);
		}

		const unsigned& idx = idToIdx[id];
		return list[idx];
	}

	template<typename T>
	inline void List<T>::Remove(const size_t& id)
	{

	}

	template<typename T>
	inline bool List<T>::Exists(const size_t& id)
	{
		return (bool)(idToIdx.find(id) != idToIdx.end());
	}

	template<typename T>
	inline void List<T>::Add(const size_t& id)
	{
		idToIdx[id] = (unsigned)list.size();
		list.push_back(T(id));
	}
}