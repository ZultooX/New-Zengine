#pragma once

#include <Engine/ComponentSystem/Component.h>

// RENAME CLASS TO NETWORKSYNCER

namespace Zengine::ComponentSystem 
{
	class NetworkTransform : public Component
	{
	public:
		void LateUpdate() override;
	};
}