#pragma once

#include <Shaders/Common/ConstantBuffers.h>

#include <Engine/Utilities/BitMask.hpp>

struct ID3D11Buffer;
namespace Zengine::Buffers
{
	enum BufferSlot
	{
		FRAME_BUFFER,
		OBJECT_BUFFER,
		MATERIAL_BUFFER = 5,
	};

	class BufferManager
	{
	public:
		void Init();

		void UpdateFrameBuffer(const Matrix4x4f& aCameraInverse, const Matrix4x4f& aProjection, 
			const Vector4f& aCameraPosition, const Vector4f& aCameraViewDir);
		void UpdateObjectBuffer(const Matrix4x4f& aObjectTransform);
		void UpdateMaterialBuffer(const MaterialBufferData& aMaterialData);

		void UpdateBuffers();

		void Bind();

	private:
		void CreateBuffer(void* aBufferData, const size_t& aSize, ID3D11Buffer** aOutBuffer);
		void UpdateBuffer(void* aBufferData, const size_t& aSize, ID3D11Buffer* aOutBuffer);

	private:
		FrameBufferData myFrameBufferData;
		ObjectBufferData myObjectBufferData;
		MaterialBufferData myMaterialBufferData;

		ID3D11Buffer* myFrameBuffer;
		ID3D11Buffer* myObjectBuffer;
		ID3D11Buffer* myMaterialBuffer;

		Zengine::Utilities::BitMask<> myBufferMask;
	};
}