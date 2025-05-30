#pragma once

#include <d3d11.h>
#include <OpenGL/glfw3.h>

class IGraphicsAPI
{
public:
	virtual bool Initialize() = 0;
	bool Update();

	virtual void Present() = 0;

	virtual void OnResize() = 0;
	virtual void Cleanup() = 0;

public:
	void UpdateDrawCalls();
	void UpdateDrawCalls(const int& anAmount);
	void ClearDrawCalls();

	const int& GetDrawCalls() const;

protected:
	virtual bool PreUpdate() = 0;
	virtual bool MainUpdate() = 0;
	virtual bool PostUpdate() = 0;

private:
	int myDrawCalls = 0;
};


#ifdef USE_DX11
class DX11GraphicsEngine final : public IGraphicsAPI
{
public:
	bool Initialize() override;
	
	void Present() override;

	void OnResize() override;
	void Cleanup() override;


public:
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11Device* GetDevice();

	ID3D11RenderTargetView* GetRTV();
	ID3D11DepthStencilView* GetDSV();
	ID3D11ShaderResourceView* GetSRV();

	void SetBackBufferAsTarget();

	void CreateBuffer(ID3D11Buffer** aBuffer, const D3D11_BUFFER_DESC& aBufferDescription, const D3D11_SUBRESOURCE_DATA& someData);

private:
	bool PreUpdate() override;
	bool MainUpdate() override;
	bool PostUpdate() override;

	void ScreenShot();

private:
	bool CreateDepthStencil();
	bool CreateDeviceAndSwapchain();
	bool CreateRenderTarget();
	bool CreateTextureSamplers();

private:
	ID3D11DeviceContext* myContext;
	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11SamplerState* myDefaultSampler;

	ID3D11RenderTargetView* myBackBuffer;
	ID3D11DepthStencilView* myDepthBuffer;
	ID3D11ShaderResourceView* mySRV;
	D3D11_VIEWPORT myViewPort = { 0 };
};
#endif // USE_DX11


#ifdef USE_OPENGL
class OpenGLGraphicsEngine final : public IGraphicsAPI
{
public:
	bool Initialize() override;

	void Present() override;

private:
	bool PreUpdate() override;
	bool MainUpdate() override;
	bool PostUpdate() override;

	GLFWwindow* myWindow;
};
#endif // USE_OPENGL