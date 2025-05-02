#include "Common/IO.hlsli"
#include "Common/ConstantBuffers.h"

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    
    float4 vxWorldPos = mul(OB_Transform, input.Position);
    float4 vxViewPos = mul(FB_InvViewMatrix, vxWorldPos);
    float4 ndcCoords = mul(FB_CameraProjection, vxViewPos);
    
    output.WorldPosition = vxWorldPos;
    output.Position = ndcCoords;
    output.inputPosition = input.Position;
    
    output.Normal = input.Normal;
    output.Tangent = input.Tangent;
    output.BiNormal = input.BiNormal;

    float3x3 rot = (float3x3) OB_Transform;
    output.WorldNormal = normalize(mul(rot, input.Normal));
    output.WorldTangent = normalize(mul(rot, input.Tangent));
    output.WorldBiNormal = normalize(mul(rot, input.BiNormal));
   
    output.Color = input.Color0;
    output.UVs = input.UVs0;
    
    return output;
}