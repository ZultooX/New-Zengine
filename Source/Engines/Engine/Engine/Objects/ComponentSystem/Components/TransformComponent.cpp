#include "TransformComponent.h"

namespace Zengine
{
	void Transform::UpdateRotationMatrix(Eigen::Matrix3f aMatrix)
	{
		myQuaternion = Eigen::Quaternionf(
			Eigen::AngleAxisf(myEulerAngles.z, Eigen::Vector3f::UnitZ()) *
			Eigen::AngleAxisf(myEulerAngles.y, Eigen::Vector3f::UnitY()) *
			Eigen::AngleAxisf(myEulerAngles.x, Eigen::Vector3f::UnitX())
		);

		myQuaternion.normalize();

		myRotationMatrix = Matrix4x4f();

		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				myRotationMatrix(i, j) = aMatrix(i - 1, j - 1);
			}
		}

		myRotationMatrix(1, 4) = 0.f;
		myRotationMatrix(2, 4) = 0.f;
		myRotationMatrix(3, 4) = 0.f;

		myRotationMatrix(4, 1) = 0.f;
		myRotationMatrix(4, 2) = 0.f;
		myRotationMatrix(4, 3) = 0.f;
		myRotationMatrix(4, 4) = 1.f;
	}

	void Transform::UpdateTransformMatricies()
	{
		//if (!GetBit(IsDirty)) return;

		UpdateRotationMatrix(myQuaternion.toRotationMatrix());
		UpdateDirectionVectors();

		
		{ // Transform
			myTransformMatrix = Matrix4x4f();

			myTransformMatrix *= Matrix4x4f::CreateScaleMatrix(myScale);
			myTransformMatrix *= myRotationMatrix;
			myTransformMatrix *= Matrix4x4f::CreateTranslation(myPosition);

			if (myParent) myTransformMatrix *= myParent->GetTransformMatrix();
		}

		{ // Transform no scale
			myTransformMatrixNoScale = Matrix4x4f();

			myTransformMatrixNoScale *= myRotationMatrix;
			myTransformMatrixNoScale *= Matrix4x4f::CreateTranslation(myPosition);

			if (myParent) myTransformMatrixNoScale *= myParent->GetTransformMatrixNoScale();
		}


		SetBit(IsDirty, false);
	}

	void Transform::UpdateDirectionVectors()
	{
		static Eigen::Vector3f EigenUp(0.f, 1.f, 0.f);
		static Eigen::Vector3f EigenForward(0.f, 0.f, 1.f);

		Eigen::Vector3f upDirection = myQuaternion * EigenUp;
		myUp = { upDirection.x(), upDirection.y(), upDirection.z() };

		Eigen::Vector3f forwardDirection = myQuaternion * EigenForward;
		myForward = { forwardDirection.x(), forwardDirection.y(), forwardDirection.z() };

		Eigen::Vector3f rightDirection = forwardDirection.cross(upDirection).normalized();
		myRight = { rightDirection.x(), rightDirection.y(), rightDirection.z() };
		myRight = myRight * -1.f;
	}

#pragma region GETTERS - SETTERS

	void Transform::SetPosition(const Vector3f& aPos)
	{
		myPosition = aPos;
		SetDirty();
	}

	const Vector3f& Transform::GetPosition() const
	{
		return myPosition;
	}

	void Transform::SetScale(const Vector3f& aScale)
	{
		myScale = aScale;
		SetDirty();
	}

	const Vector3f& Transform::GetScale() const
	{
		return myScale;
	}

	void Transform::SetEulerAngles(const Vector3f& aEulerAngles)
	{
		myEulerAngles = aEulerAngles;
		SetDirty();
	}

	const Vector3f& Transform::GetEulerAngles() const
	{
		return myEulerAngles;
	}

	void Transform::SetQuaternion(const Eigen::Quaternionf& aQuaternion)
	{
		myQuaternion = aQuaternion;
		SetDirty();
	}


	const Eigen::Quaternionf& Transform::GetQuaternion() const
	{
		return myQuaternion;
	}


	const Vector3f& Transform::GetForward() const
	{
		return myForward;
	}


	const Vector3f& Transform::GetRight() const
	{
		return myRight;
	}


	const Vector3f& Transform::GetUp() const
	{
		return myUp;
	}

	const Matrix4x4f& Transform::GetTransformMatrix()
	{
		UpdateTransformMatricies();
		return myTransformMatrix;
	}

	const Matrix4x4f& Transform::GetTransformMatrix() const
	{
		return myTransformMatrix;
	}

	const Matrix4x4f& Transform::GetTransformMatrixNoScale()
	{
		UpdateTransformMatricies();
		return myTransformMatrixNoScale;
	}

	const Matrix4x4f& Transform::GetTransformMatrixNoScale() const
	{
		return myTransformMatrixNoScale;
	}

	const Matrix4x4f& Transform::GetRotationMatrix()
	{
		UpdateTransformMatricies();
		return myRotationMatrix;
	}

	const Matrix4x4f& Transform::GetRotationMatrix() const
	{
		return myRotationMatrix;
	}


#pragma endregion

	void Transform::SetParent(Transform* aTransform) { myParent = aTransform; }
}