#pragma once

#include <Engine/Objects/ComponentSystem/Component.h>

#include <Zultools/Math/Vector2.hpp>
#include <Zultools/Math/Matrix4x4.hpp>


namespace Zengine
{
	class Camera : public Component
	{
		COMPONENT_BASICS(Camera)

	public:
		bool isMainCamera = false;

		float fov = 60.f;
		float nearPlane = 0.1f;
		float farPlane = 10000.f;

		Vector2f resolution = { 1920, 1080 };
		Vector2f size = { 1920, 1080 };

		bool isOrhographics = false;

		Matrix4x4f projectionMatrix = {};
		Matrix4x4f invProjectionMatrix = {};

		Matrix4x4f view = {};
		Matrix4x4f inverseView = {};

		enum class ProjectionType {
			Orthographic,
			Perspective,
			Count
		} projection;

	public:
		void Awake() override;
		void Update() override;

	public:
		void SetOrthographicView();
		void SetOrthographicView(Vector2f aResolution, float aNear, float aFar);

		void SetPerspectiveView();
		void SetPerspectiveView(Vector2f size, float aFOV, float aNear, float aFar);

	private:
		void UpdateProjection();

	public:
		static Camera* MainCamera;
	};
}