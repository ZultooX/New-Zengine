#pragma once

#include "BufferDatas.h"
#include <Engine/Utilities/BitMask.hpp>

struct ID3D11Buffer;
namespace Zengine::Buffers
{
	enum BufferSlot
	{
		FRAME_BUFFER,
		OBJECT_BUFFER
	};

	class BufferManager
	{
	public:
		void Init();

		void UpdateFrameBuffer(const Matrix4x4f& aCameraInverse, const Matrix4x4f& aProjection, 
			const Vector4f& aCameraPosition, const Vector4f& aCameraViewDir);
		void UpdateObjectBuffer(const Matrix4x4f& aObjectTransform);

		void UpdateBuffers();

		void Bind();

	private:
		void CreateBuffer(void* aBufferData, const size_t& aSize, ID3D11Buffer** aOutBuffer);
		void UpdateBuffer(void* aBufferData, const size_t& aSize, ID3D11Buffer* aOutBuffer);

	private:
		FrameBufferData myFrameBufferData;
		ObjectBufferData myObjectBufferData;

		ID3D11Buffer* myFrameBuffer;
		ID3D11Buffer* myObjectBuffer;

		Zengine::Utilities::BitMask<> myBufferMask;
	};
}