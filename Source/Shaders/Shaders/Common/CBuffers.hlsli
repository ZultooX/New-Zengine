
// Regular
Texture2D Albedo                    : register(t0);
Texture2D NormalMap                 : register(t1);
Texture2D MaterialMap               : register(t2);


// GBuffer
Texture2D GBuffer_Position          : register(t3);
Texture2D GBuffer_Albedo            : register(t4);
Texture2D GBuffer_Normal            : register(t5);
Texture2D GBuffer_Material          : register(t6);
Texture2D GBuffer_AmbientOcclusion  : register(t7);


// Lights
Texture2D SpotLightTexture          : register(t8);
Texture2D PointLightTexture         : register(t9);


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


cbuffer FrameBuffer : register(b0)
{
    float4x4 FB_InvViewMatrix;
    float4x4 FB_ViewMatrix;
    float4x4 FB_CameraProjection;
    float4x4 FB_InvCameraProjection;

    float4 FB_CameraPosition;
    float4 FB_CameraViewDir;
    
    int2 FB_Resolution;
    int2 Padding0;
}




cbuffer ObjectBuffer : register(b1)
{
    float4x4 OB_Transform;
    float4x4 OB_InvTransform;
}


cbuffer LB_DirectionalBuffer : register(b2)
{
    float4 LB_DirectionalLightDirection;
     
    float4x4 LB_DirectionalView;
    float4x4 LB_DirectionalProj;
    
    float3 LB_DirectionalLightColor;
    float LB_DirectionalLightIntensity;
}


cbuffer LB_SpotLightBuffer : register(b3)
{
    float4 LBS_position;
    
    float4 LBS_direction;

    float4x4 LBS_DirectionalView;
    float4x4 LBS_DirectionalProj;
    
    float3 LBS_color;
    int LBS_IsSet;
        
    float LBS_innerAngle;
    float LBS_outerAngle;
    float LBS_range;
    float LBS_intensity;
    
    int2 LBS_ShadowTopLeft;
    int2 LBS_ShadowResolution;
}


cbuffer LB_PointLightBuffer : register(b4)
{
    float4 LBP_position;
    float4 LBP_color;
    
    
    int LBP_IsSet;
    float LBP_intensity;
    float LBP_range;
    float LBP_padding;
}


cbuffer MaterialBuffer : register(b5)
{
    float4 MB_albedoColor;
    
    float MB_roughness = 0;
    float MB_metallic = 0;
    float MB_AOStrength;
    float MB_BloomIntensity;
    
    int MB_textureIsSetFlag;
    int MB_NormalMappingFlags;
    float Garbage2;
    float Garbage3;
};


cbuffer PostProcessingBuffer : register(b6)
{
    float3 PP_Contrast;
    float PP_BloomScale;
    
    float3 PP_BlackPoint;
    float PP_Saturation;
    
    float3 PP_Tint;
    float PP_Exposure;
};


cbuffer AnimationBuffer : register(b7)
{
    float4x4 AB_Bones[128];
};