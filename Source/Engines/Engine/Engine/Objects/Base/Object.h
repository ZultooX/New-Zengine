#pragma once

#include <string>
#include <Zultools/BitMask.hpp>

namespace Zengine
{
	class Object 
	{
	public:
		Object();
		Object(const size_t& _id);
		virtual ~Object() = default;

	public:
		const std::string& GetName() const;
		void SetName(const std::string& _name);

		const size_t& GetID() const;
		void SetID(const size_t& _id);

		bool GetFlag(const int& idx);
		void SetFlag(const int& idx, const bool& state);

		const std::string& ToString() const;

	private:
		size_t id;
		std::string name = "";

		Zengine::Utilities::BitMask<> flags;
	};
}