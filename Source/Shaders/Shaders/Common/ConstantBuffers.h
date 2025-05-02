
#ifdef __cplusplus
#pragma once
#endif

#define MAX_BONES 128


#ifdef __cplusplus

#include <Zultools/Math/Vector2.hpp>
#include <Zultools/Math/Vector3.hpp>
#include <Zultools/Math/Vector4.hpp>
#include <Zultools/Math/Matrix4x4.hpp>
#include <Zultools/Math/Color.h>

#define vec2f Vector2f
#define vec2i Vector2i
#define vec3f Vector3f
#define vec3i Vector3i
#define vec4f Vector4f
#define vec4i Vector4i
#define mat4x4f Matrix4x4f

#define color Color

#else

#define vec2f float2
#define vec2i int2
#define vec3f float3
#define vec3i int3
#define vec4f float4
#define vec4i int4
#define mat4x4f float4x4

#define color float4

#endif

#ifdef __cplusplus
#define ConstantBuffer(Name, Bindslot) struct Name
#else
#define ConstantBuffer(Name, Bindslot) cbuffer Name : register(b##Bindslot)
#endif




#ifndef __cplusplus
// Regular
Texture2D Albedo : register(t0);
Texture2D NormalMap : register(t1);
Texture2D MaterialMap : register(t2);


// GBuffer
Texture2D GBuffer_Position : register(t3);
Texture2D GBuffer_Albedo : register(t4);
Texture2D GBuffer_Normal : register(t5);
Texture2D GBuffer_Material : register(t6);
Texture2D GBuffer_AmbientOcclusion : register(t7);


// Lights
Texture2D SpotLightTexture : register(t8);
Texture2D PointLightTexture : register(t9);


// Shadows
Texture2D ShadowMapTexture : register(t10);
Texture2D SpotLightShadowTexture : register(t11);
TextureCube PointLightShadowTexture : register(t12);


// Skybox
TextureCube SkyBoxCubeMap : register(t13);


// PBR
Texture2D BRDF_LUT_Texture : register(t32);
Texture2D ShadowAtlas : register(t33);
Texture2D Depth : register(t34);


TextureCube TESTING : register(t49);


SamplerState Sampler : register(s0);
SamplerComparisonState ShadowSampler : register(s1);
#endif





ConstantBuffer(FrameBufferData, 0)
{
    mat4x4f FB_InvViewMatrix;
    mat4x4f FB_ViewMatrix;
    mat4x4f FB_CameraProjection;

    vec4f FB_CameraPosition;
    vec4f FB_CameraViewDir;
};


ConstantBuffer(ObjectBufferData, 1)
{
    mat4x4f OB_Transform;
};


ConstantBuffer(DirectionalLightData, 2)
{
    vec4f LB_DirectionalLightDirection;

    mat4x4f LB_DirectionalView;
    mat4x4f LB_DirectionalProj;

    vec3f LB_DirectionalLightColor;
    float LB_DirectionalLightIntensity;
};


ConstantBuffer(SpotLightBufferData, 3)
{
    vec4f LBS_position;

    vec4f LBS_direction;

    mat4x4f LBS_DirectionalView;
    mat4x4f LBS_DirectionalProj;

    vec3f LBS_color;
    int LBS_IsSet;

    float LBS_innerAngle;
    float LBS_outerAngle;
    float LBS_range;
    float LBS_intensity;

    vec2i LBS_ShadowTopLeft;
    vec2i LBS_ShadowResolution;
};


ConstantBuffer(PointLightBufferData, 4)
{
    vec4f LBP_position;
    vec4f LBP_color;


    int LBP_IsSet;
    float LBP_intensity;
    float LBP_range;
    float LBP_padding;
};


ConstantBuffer(MaterialBufferData, 5)
{
    color MB_albedoColor;

    float MB_roughness = 0;
    float MB_metallic = 0;
    float MB_AOStrength;
    float MB_BloomIntensity;

    int MB_textureIsSetFlag;
    int MB_NormalMappingFlags;
    int MB_BitSetCapacity = 0;
    int MB_TextureSetBitSet;
};


ConstantBuffer(PostProcessingBufferData, 6)
{
    vec3f PP_Contrast;
    float PP_BloomScale;

    vec3f PP_BlackPoint;
    float PP_Saturation;

    vec3f PP_Tint;
    float PP_Exposure;
};


ConstantBuffer(AnimationBuffer, 7)
{
    mat4x4f AB_Bones[MAX_BONES];
};