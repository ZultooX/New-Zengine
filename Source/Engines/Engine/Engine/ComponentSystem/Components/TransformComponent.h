#pragma once

#include <Engine/ComponentSystem/Component.h>

#include <Zultools/Math/Vector3.hpp>
#include <Zultools/Math/Matrix4x4.hpp>

#include <Eigen/Dense>

namespace Zengine::ComponentSystem
{
	class Transform final : public Component
	{
	public:
		void UpdateTransformMatricies();
		void UpdateDirectionVectors();

		void SetPosition(Vector3f aPos);

	private:
		void UpdateRotationMatrix(Eigen::Matrix3f aMatrix);

		public:
		Vector3f position = { 0.f, 0.f, 0.f };
		Vector3f scale = { 1.f, 1.f, 1.f };
		Vector3f eulerAngles = { 0.f, 0.f, 0.f };

		Vector3f forward;
		Vector3f right;
		Vector3f up;

		Matrix4x4f transformMatrix;
		Matrix4x4f transformMatrixNoScale;
		Matrix4x4f rotationMatrix;

		Eigen::Quaternionf  rotation;
	};
}

namespace CS = Zengine::ComponentSystem;