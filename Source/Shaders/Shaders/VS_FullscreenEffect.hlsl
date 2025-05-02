#include "Common/IO.hlsli"
#include "Common/ConstantBuffers.h"

struct PostProcessInput
{
    unsigned int myIndex : SV_VertexID;
};

PostProcessVertexToPixel main(PostProcessInput input)
{
    float4 pos[3] =
    {
        float4(-1.0f, -1.0f, 0.0f, 1.0f),
		float4(-1.0f, 3.0f, 0.0f, 1.0f),
		float4(3.0f, -1.0f, 0.0f, 1.0f)
    };

    float2 uv[3] =
    {
        float2(0.0f, 1.0f),
		float2(0.0f, -1.0f),
		float2(2.0f, 1.0f)
    };

    PostProcessVertexToPixel returnValue;
    returnValue.myPosition = pos[input.myIndex];
    returnValue.myUV = uv[input.myIndex];
    return returnValue;
}