#include "Common/CBuffers.hlsli"
#include "Common/IO.hlsli"


GBufferOutput main(PixelInputType input)
{
    GBufferOutput output;
    output.AlbedoColor = float4(Albedo.Sample(Sampler, input.UVs).rgb, 1.f);
    output.AmbientOcclusionAndCustom = float4(0.3, 1.f, 0.4f, 1.f);
    output.Material = float4(0.3, 1.f, 0.4f, 1.f);
    output.WorldPosition = input.WorldPosition;

    float3 normal = NormalMap.Sample(Sampler, input.UVs).xyz;
    float3x3 TBN = float3x3(
        normalize(input.Tangent.xyz),
        normalize(-input.BiNormal.xyz),
        normalize(input.Normal.xyz)
    );
    TBN = transpose(TBN);
    float3 pixelNormal = normalize(mul(TBN, normal));
    
    pixelNormal = 2.f * pixelNormal - 1.f;
    output.Normal = float4(pixelNormal, 1.f);


    return output;
}