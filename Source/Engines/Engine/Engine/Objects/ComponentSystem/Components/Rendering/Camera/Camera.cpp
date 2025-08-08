#include "Camera.h"

#include <Engine/EngineSettings.h>
#include <Engine/Engine.h>

#include <d3d11.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>

namespace Zengine
{
	Camera* Camera::MainCamera;


	void Camera::Awake()
	{
		MainCamera = this;
	}

	void Camera::Update()
	{
		Matrix4x4f viewMatrix = Matrix4x4f();
		const Vector3f& pos = gameobject->transform->GetPosition();
		viewMatrix.SetPosition({ pos.x, pos.y, pos.z, 1.f});
		inverseView = viewMatrix.GetInverse() * gameobject->transform->GetRotationMatrix();
	}

	void Camera::SetOrthographicView()
	{
		projection = ProjectionType::Orthographic;
		UpdateProjection();
	}


	/// <summary>
	/// Sets the view to orthographic.
	/// </summary>
	/// <param name="aResolution">A resolution of the camera.</param>
	/// <param name="aNear">A near plane.</param>
	/// <param name="aFar">A far plane.</param>
	void Camera::SetOrthographicView(Vector2f aResolution, float aNear, float aFar)
	{
		projection = ProjectionType::Orthographic;

		resolution = aResolution;
		nearPlane = aNear;
		farPlane = aFar;

		UpdateProjection();
	}


	/// <summary>
	/// Just changes the view to perspective to the last values set or default.
	/// </summary>
	void Camera::SetPerspectiveView()
	{
		projection = ProjectionType::Perspective;
		UpdateProjection();
	}


	/// <summary>
	/// Changes the view to perspective.
	/// </summary>
	/// <param name="aSize">The size of the camera.</param>
	/// <param name="aFOV">The fov angle of the camera.</param>
	/// <param name="aNear">A near plane.</param>
	/// <param name="aFar">A far plane.</param>
	void Camera::SetPerspectiveView(Vector2f aSize, float aFOV, float aNear, float aFar)
	{
		projection = ProjectionType::Perspective;

		fov = aFOV;
		nearPlane = aNear;
		farPlane = aFar;
		resolution = aSize;

		UpdateProjection();
	}


	void Camera::UpdateProjection()
	{
		switch (projection)
		{
		case Camera::ProjectionType::Orthographic:
		{
			const float left = -resolution.x * 0.5f;
			const float right = resolution.x * 0.5f;
			const float bottom = -resolution.y * 0.5f;
			const float top = resolution.y * 0.5f;

			projectionMatrix = Matrix4x4f();
			projectionMatrix(1, 1) = 2.f / resolution.x;
			projectionMatrix(2, 2) = 2.f / resolution.y;

			projectionMatrix(3, 3) = 1.f / (farPlane - nearPlane);
			projectionMatrix(4, 3) = 1.f / (nearPlane - farPlane);

			break;
		}

		case Camera::ProjectionType::Perspective:
		{
			const float fovRadians = fov * (PI / 180.f);
			const float aspectRatio = size.x / size.y;
			const float scaleY = 1.f / tanf(fovRadians * 0.5f);
			const float scaleX = scaleY / aspectRatio;

			projectionMatrix(1, 1) = scaleX;
			projectionMatrix(2, 2) = scaleY;
			projectionMatrix(3, 3) = farPlane / (farPlane - nearPlane);
			projectionMatrix(3, 4) = 1.f;
			projectionMatrix(4, 3) = (-nearPlane * farPlane) / (farPlane - nearPlane);
			projectionMatrix(4, 4) = 0.f;

			break;
		}

		default: // just how?
			break;
		}

		invProjectionMatrix = projectionMatrix.GetInverse();
	}
}