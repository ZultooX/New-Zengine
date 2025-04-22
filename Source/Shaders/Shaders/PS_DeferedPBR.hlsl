#include "Common/CBuffers.hlsli"
#include "Common/IO.hlsli"


float4 main(PostProcessVertexToPixel input) : SV_TARGET0
{
    return GBuffer_Albedo.Sample(Sampler, input.myUV);
}