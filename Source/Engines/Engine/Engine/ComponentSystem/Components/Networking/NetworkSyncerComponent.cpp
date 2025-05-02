#include "NetworkSyncerComponent.h"

#include <Engine/Engine.h>
#include <Client.h>
#include <NetworkEncoder.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>



namespace Zengine::ComponentSystem
{
	void NetworkSyncer::LateUpdate()
	{
		if (!Engine::GetNetworkManager().GetClient()->IsRunning()) return;

		const std::vector<std::type_index> dirtyComps = gameobject->GetDirtyComponents();
		if (dirtyComps.empty()) return;

		Encoder* encoder = Engine::GetNetworkManager().GetClient()->GetEncoder();
		if (!encoder) return;

		encoder->Begin(gameobject->GetID());

		for (const std::type_index& type : dirtyComps)
		{
			if (type == typeid(Transform))
			{
				Datas::TransformData data = { gameobject->transform->GetPosition(), gameobject->transform->GetEulerAngles(), gameobject->transform->GetScale() };

				encoder->Write(MessageIdentifier::Transform, data);
			}
		}

		encoder->End();
	}
}