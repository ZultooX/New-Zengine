#pragma once

#include <Zultools\Math\Matrix4x4.hpp>
#include <TgaFbx\TGAFbx.h>
#include <Zultools\Math\Vector3.hpp>
#include <Zultools\Math\Vector2.hpp>
#include <Zultools\Math\Color.h>
#include <Engine/Utilities/BitMask.hpp>



// A buffer shared between all instances
/// Buffer 0
struct FrameBufferData
{
	Matrix4x4f	CameraViewInverse;
	Matrix4x4f	CameraView;
	Matrix4x4f	Projection;

	Vector4f	CameraPosition = { 0.f, 0.f, 0.f , 0.f};
	Vector4f	CameraViewDir = { 0.f, 0.f, 0.f, 0.f};
};



// A buffer that all instances has one instance of
/// Buffer 1
struct ObjectBufferData
{
	Matrix4x4f ModelToWorld;
};




struct DirectionalLightData
{
	Vector4f lightDirection;

	Matrix4x4f CameraView;
	Matrix4x4f CameraProj;

	Vector3f lightColor = { 1.f, 1.f, 1.f };
	float directionalIntensity = 1.f;
};

struct SpotLightBufferData
{
	Vector4<float> position = { 0.f ,0.f ,0.f ,1.f };
	Vector4<float> direction = { 0.f ,-1.f ,0.f ,1.f };

	Matrix4x4f CameraView;
	Matrix4x4f CameraProj;

	Vector3<float> color = { 1.f,1.f, 1.f };
	int isSet = 0;

	float innerAngle = 15.f;
	float outerAngle = 30.f;
	float range = 10.f;
	float intensity = 1.f;

	Vector2i LBS_ShadowTopLeft;
	Vector2i LBS_ShadowResolution;
};


struct PointLightBufferData
{
	Vector4<float> position = { 0.f ,0.f ,0.f ,1.f };
	Vector4<float> color = { 1.f,1.f, 1.f, 1.f };

	int isSet = 0;
	float intensity = 1;
	float range = 1;

	float padding;
};



// A buffer that every mesh renderer has.
struct MaterialBufferData
{
	Color Color = { 1.f, 1.f, 1.f, 1.f };

	float	 Roughness = 1.f;
	float	 Metallic = 0.f;
	float	 AO_Strength = 0.f;
	float	 BloomIntensity = 1.f;

	int		 TextureSetFlags = 0;
	int		 NormalMappingFlags = 0;
	Zengine::Util::BitMask<> myTextureSet;
};



/// Buffer 6
struct PostProcessingBufferData
{
	Vector3f Contrast = { 1.f,1.f,1.f };
	float	 BloomScale = 0.f;

	Vector3f BlackPoint = { 0.f,0.f,0.f };
	float	 Saturation = 1.f;

	Vector3f Tint = { 1.f,1.f,1.f };
	float	 Exposure = 0.f;
};



//  Buffer 7
struct AnimationBuffer
{
	Matrix4x4f JointTransforms[128];
};