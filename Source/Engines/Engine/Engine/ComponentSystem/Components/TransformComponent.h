#pragma once

#include <Engine/ComponentSystem/Component.h>

#include <Zultools/Math/Vector3.hpp>
#include <Zultools/Math/Matrix4x4.hpp>

#include <Eigen/Dense>

namespace Zengine::ComponentSystem
{
	class Transform final : public Component
	{
		COMPONENT_BASICS(Transform)

	public:
		void UpdateTransformMatricies();
		void UpdateDirectionVectors();

	public:
		void SetPosition(const Vector3f& aPos);
		const Vector3f& GetPosition() const;
		void Move(const Vector3f& aDisplacement);

		void SetScale(const Vector3f& aScale);
		const Vector3f& GetScale() const;

		void SetEulerAngles(const Vector3f& aEulerAngles);
		const Vector3f& GetEulerAngles() const;

		void SetQuaternion(const Eigen::Quaternionf& aQuaternion);
		const Eigen::Quaternionf& GetQuaternion() const;

		const Vector3f& GetForward() const;

		const Vector3f& GetRight() const;

		const Vector3f& GetUp() const;

		const Matrix4x4f& GetTransformMatrix();
		const Matrix4x4f& GetTransformMatrix() const;

		const Matrix4x4f& GetTransformMatrixNoScale();
		const Matrix4x4f& GetTransformMatrixNoScale() const;

		const Matrix4x4f& GetRotationMatrix();
		const Matrix4x4f& GetRotationMatrix() const;

	public:
		void SetParent(Transform* aTransform);

	private:
		void UpdateRotationMatrix(Eigen::Matrix3f aMatrix);

	private:
		Transform* myParent = nullptr;

		Vector3f myPosition = { 0.f, 0.f, 0.f };
		Vector3f myScale = { 1.f, 1.f, 1.f };
		Vector3f myEulerAngles = { 0.f, 0.f, 0.f };

		Vector3f myForward;
		Vector3f myRight;
		Vector3f myUp;

		Matrix4x4f myTransformMatrix;
		Matrix4x4f myTransformMatrixNoScale;
		Matrix4x4f myRotationMatrix;

		Eigen::Quaternionf  myQuaternion;
	};
}

namespace CS = Zengine::ComponentSystem;