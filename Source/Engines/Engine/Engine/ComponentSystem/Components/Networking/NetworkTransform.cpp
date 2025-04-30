#include "NetworkTransform.h"

#include <Engine/Engine.h>
#include <Client.h>
#include <NetworkEncoder.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>

void Zengine::ComponentSystem::NetworkTransform::LateUpdate()
{
	Encoder* encoder = Engine::GetNetworkManager().GetClient()->GetEncoder();

	encoder->Begin(gameobject->GetID());

	encoder->Write(MessageIdentifier::Transform, gameobject->transform->position);

	encoder->End();
}
