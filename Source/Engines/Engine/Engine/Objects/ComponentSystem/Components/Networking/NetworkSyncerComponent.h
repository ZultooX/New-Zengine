#pragma once

#include <Engine/ComponentSystem/Component.h>
#include <Zultools/Math/Vector3.hpp>

namespace Datas {
	struct TransformData {
		Vector3f pos;
		Vector3f eulerAngles;
		Vector3f scale;
	};
}

namespace Zengine::ComponentSystem 
{
	class NetworkSyncer : public Component
	{
	public:
		void LateUpdate() override;
	};
}