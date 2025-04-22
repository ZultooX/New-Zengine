struct PostProcessVertexToPixel
{
    float4 myPosition : SV_POSITION;
    float2 myUV : UV;
};






struct VertexInputType
{
    float4 Position : SV_POSITION;
    
    float4 Color0 : COLOR0;
    float4 Color1 : COLOR1;
    float4 Color2 : COLOR2;
    float4 Color3 : COLOR3;
    
    float2 UVs0 : UV0;
    float2 UVs1 : UV1;
    float2 UVs2 : UV2;
    float2 UVs3 : UV3;
    
    float3 Normal : NORMAL;
    
    float3 Tangent : TANGENT;
    
    float3 BiNormal : BINORMAL;

    uint4 BoneIDs : BONES;
    float4 BoneWeights : BONEWEIGHTS;
};

struct PixelInputType
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : WORLDPOSITION;
    
    float4 inputPosition : VXPOSITION;
    
    float4 Color : COLOR;
    
    float2 UVs : UV;
    
    float3 Normal : NORMAL;
    float3 WorldNormal : NORMALWORLD;
    
    float3 Tangent : TANGENT;
    float3 WorldTangent : TANGENTWORLD;
    
    float3 BiNormal : BINORMAL;
    float3 WorldBiNormal : BINORMALWORLD;
};

struct GBufferOutput
{
    float4 WorldPosition : SV_TARGET0;
    float4 AlbedoColor : SV_TARGET1;
    float4 Normal : SV_TARGET2;
    float4 Material : SV_TARGET3;
    float4 AmbientOcclusionAndCustom : SV_TARGET4;
};