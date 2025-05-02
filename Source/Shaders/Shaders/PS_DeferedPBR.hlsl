#include "Common/IO.hlsli"
#include "Common/ConstantBuffers.h"


float4 main(PostProcessVertexToPixel input) : SV_TARGET0
{
    
    float3 normal = (GBuffer_Normal.Sample(Sampler, input.myUV).rgb * 2.f) - 1.f;
    float ao = GBuffer_AmbientOcclusion.Sample(Sampler, input.myUV).r;
    
    float3 lightDir = normalize(float3(0.f, 0.f, -1.f));
    float NdotL = saturate(dot(normal, lightDir));

    float3 outputColor = GBuffer_Albedo.Sample(Sampler, input.myUV).rgb * NdotL * ao;
    
    return float4(outputColor, 1.f);
}