#include "TransformComponent.h"

namespace Zengine::ComponentSystem
{
	void Transform::UpdateRotationMatrix(Eigen::Matrix3f aMatrix)
	{
		rotation = Eigen::Quaternionf(
			Eigen::AngleAxisf(eulerAngles.z, Eigen::Vector3f::UnitZ()) *
			Eigen::AngleAxisf(eulerAngles.y, Eigen::Vector3f::UnitY()) *
			Eigen::AngleAxisf(eulerAngles.x, Eigen::Vector3f::UnitX())
		);

		rotation.normalize();

		rotationMatrix = Matrix4x4f();

		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				rotationMatrix(i, j) = aMatrix(i - 1, j - 1);
			}
		}

		rotationMatrix(1, 4) = 0.f;
		rotationMatrix(2, 4) = 0.f;
		rotationMatrix(3, 4) = 0.f;

		rotationMatrix(4, 1) = 0.f;
		rotationMatrix(4, 2) = 0.f;
		rotationMatrix(4, 3) = 0.f;
		rotationMatrix(4, 4) = 1.f;
	}

	void Transform::UpdateTransformMatricies()
	{
		UpdateRotationMatrix(rotation.toRotationMatrix());
		UpdateDirectionVectors();

		transformMatrix = Matrix4x4f();

		transformMatrix *= Matrix4x4f::CreateScaleMatrix(scale);
		transformMatrix *= rotationMatrix;
		transformMatrix *= Matrix4x4f::CreateTranslation(position);


		transformMatrixNoScale = Matrix4x4f();

		transformMatrixNoScale *= rotationMatrix;
		transformMatrixNoScale *= Matrix4x4f::CreateTranslation(position);
	}

	void Transform::UpdateDirectionVectors()
	{
		static Eigen::Vector3f EigenUp(0.f, 1.f, 0.f);
		static Eigen::Vector3f EigenForward(0.f, 0.f, 1.f);

		Eigen::Vector3f upDirection = rotation * EigenUp;
		up = { upDirection.x(), upDirection.y(), upDirection.z() };

		Eigen::Vector3f forwardDirection = rotation * EigenForward;
		forward = { forwardDirection.x(), forwardDirection.y(), forwardDirection.z() };

		Eigen::Vector3f rightDirection = forwardDirection.cross(upDirection).normalized();
		right = { rightDirection.x(), rightDirection.y(), rightDirection.z() };
		right = right * -1.f;
	}

	void Transform::SetPosition(Vector3f aPos)
	{

	}
}