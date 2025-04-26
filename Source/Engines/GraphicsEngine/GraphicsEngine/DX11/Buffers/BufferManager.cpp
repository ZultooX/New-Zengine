#include "BufferManager.h"

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

void Zengine::Buffers::BufferManager::Init()
{
	CreateBuffer(&myFrameBufferData, sizeof(FrameBufferData), &myFrameBuffer);
	CreateBuffer(&myObjectBufferData, sizeof(ObjectBufferData), &myObjectBuffer);
	CreateBuffer(&myMaterialBufferData, sizeof(MaterialBufferData), &myMaterialBuffer);
}

void Zengine::Buffers::BufferManager::UpdateFrameBuffer(const Matrix4x4f& aCameraInverse, const Matrix4x4f& aProjection, const Vector4f& aCameraPosition, const Vector4f& aCameraViewDir)
{
	myFrameBufferData.CameraViewInverse = aCameraInverse;
	myFrameBufferData.CameraView = aCameraInverse.GetInverse();
	myFrameBufferData.Projection		= aProjection;
	myFrameBufferData.CameraPosition	= aCameraPosition;
	myFrameBufferData.CameraViewDir		= aCameraViewDir;
	
	myBufferMask.SetBit(FRAME_BUFFER, true);
}

void Zengine::Buffers::BufferManager::UpdateObjectBuffer(const Matrix4x4f& aObjectTransform)
{
	myObjectBufferData.ModelToWorld = aObjectTransform;

	myBufferMask.SetBit(OBJECT_BUFFER, true);
}

void Zengine::Buffers::BufferManager::UpdateMaterialBuffer(const MaterialBufferData& aMaterialData)
{
	memcpy(&myMaterialBufferData, &aMaterialData, sizeof(MaterialBufferData));
	myBufferMask.SetBit(MATERIAL_BUFFER, true);
}

void Zengine::Buffers::BufferManager::UpdateBuffers()
{
	if (myBufferMask.GetBit(FRAME_BUFFER)) UpdateBuffer(&myFrameBufferData, sizeof(FrameBufferData), myFrameBuffer);
	if (myBufferMask.GetBit(OBJECT_BUFFER)) UpdateBuffer(&myObjectBufferData, sizeof(ObjectBufferData), myObjectBuffer);
	if (myBufferMask.GetBit(MATERIAL_BUFFER)) UpdateBuffer(&myMaterialBufferData, sizeof(MaterialBufferData), myMaterialBuffer);
	
	myBufferMask.SetAll(false);
}

void Zengine::Buffers::BufferManager::Bind()
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ge->GetContext()->VSSetConstantBuffers(FRAME_BUFFER, 1, &myFrameBuffer);
	ge->GetContext()->VSSetConstantBuffers(OBJECT_BUFFER, 1, &myObjectBuffer);
	ge->GetContext()->VSSetConstantBuffers(MATERIAL_BUFFER, 1, &myMaterialBuffer);
	ge->GetContext()->PSSetConstantBuffers(MATERIAL_BUFFER, 1, &myMaterialBuffer);
}

void Zengine::Buffers::BufferManager::CreateBuffer(void* aBufferData, const size_t& aSize, ID3D11Buffer** aOutBuffer)
{
	D3D11_BUFFER_DESC bufferDescription = { 0 };
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDescription.MiscFlags = 0;
	bufferDescription.StructureByteStride = 0;

	bufferDescription.ByteWidth = static_cast<UINT>(aSize + (16 - (aSize % 16)));

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = aBufferData;

	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ge->GetDevice()->CreateBuffer(&bufferDescription, &data, aOutBuffer);
}

void Zengine::Buffers::BufferManager::UpdateBuffer(void* aBufferData, const size_t& aSize, ID3D11Buffer* aOutBuffer)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	D3D11_MAPPED_SUBRESOURCE mappedBuffer = {};
	ge->GetContext()->Map(aOutBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);
	memcpy(mappedBuffer.pData, aBufferData, aSize);
	ge->GetContext()->Unmap(aOutBuffer, 0);
}
