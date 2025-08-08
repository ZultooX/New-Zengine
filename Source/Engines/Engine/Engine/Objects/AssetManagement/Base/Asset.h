#pragma once

#include <Engine/Objects/Base/Object.h>

namespace Zengine
{
	class Asset : public virtual Object
	{
	public:
		Asset();
		Asset(const size_t& _id);
		virtual ~Asset() = default;

	public:
		const std::string& GetPath() const;
		void SetPath(const std::string& _path);

		inline void SetDirty() { __noop; }

	protected:
		std::string path = "";
		unsigned references = 0;
	};
}