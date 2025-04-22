#include "Common/CBuffers.hlsli"
#include "Common/IO.hlsli"

float4 main(PixelInputType input) : SV_TARGET0
{
    return float4(input.Color.rgb, 1.f);
}