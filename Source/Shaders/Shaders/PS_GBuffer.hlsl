#include "Common/IO.hlsli"
#include "Common/ConstantBuffers.h"

float3 UnpackNormal(float2 xy)
{
    float3 normal = xy.xyy;
    normal.z = sqrt(1.f - saturate(normal.x * normal.x + normal.y * normal.y));
    return normalize(normal);
}


GBufferOutput main(PixelInputType input)
{
    GBufferOutput output;
   
    float4 albedoTexture = Albedo.Sample(Sampler, input.UVs);
    
    // =======================
    // [CALCULATE ALBEDO COLOR]
    // =======================
    if (MB_textureIsSetFlag & (1 << 0))
    {
        output.AlbedoColor = float4(albedoTexture.rgb, 1.f);
    }
    else
    {
        output.AlbedoColor = float4(input.Color.rgb, 1.f);
    }
    
    output.AlbedoColor *= MB_albedoColor;
   
    
    
    
    // =======================
    // [CALCULATE NORMAL]
    // =======================
    float3 tangentNormal = NormalMap.Sample(Sampler, input.UVs).xyz;
    tangentNormal = UnpackNormal(tangentNormal.xy);
    
    //tangentNormal = tangentNormal * 2.f - 1.f;

    float3x3 TBN = float3x3(
        normalize(input.WorldTangent.xyz),
        normalize(input.WorldBiNormal.xyz),
        normalize(input.WorldNormal.xyz)
    );
    TBN = transpose(TBN);
    
    float3 worldNormal = normalize(mul(TBN, tangentNormal));
    
    //output.Normal = float4(worldNormal, 1.f);
    output.Normal = float4((worldNormal * 0.5f) + 0.5f, 1.f);
    
    
    
    // =======================
    // [SET MATERIAL, POS AND AO]
    // =======================
    output.Material = float4(MaterialMap.Sample(Sampler, input.UVs).rgb, 1.f);
    output.WorldPosition = input.WorldPosition;
    output.AmbientOcclusionAndCustom = float4((float3) albedoTexture.a, 1.f);
    
    return output;
}