#include "Common/CBuffers.hlsli"
#include "Common/IO.hlsli"


float4 main(PostProcessVertexToPixel input) : SV_TARGET0
{
    
    float3 normal = (GBuffer_Normal.Sample(Sampler, input.myUV).rgb * 2.f) - 1.f;
    float ao = GBuffer_AmbientOcclusion.Sample(Sampler, input.myUV).r;
    
    float3 lightDir = normalize(float3(0.f, 0.f, -1.f));
    float NdotL = saturate(dot(normal, lightDir));

    float3 color = GBuffer_Albedo.Sample(Sampler, input.myUV).rgb * NdotL * ao;
    
    return float4(color, 1.f);
}