#include "Common/IO.hlsli"
#include "Common/ConstantBuffers.h"

float4 main(PixelInputType input) : SV_TARGET0
{
    return float4(input.Color.rgb, 1.f);
}