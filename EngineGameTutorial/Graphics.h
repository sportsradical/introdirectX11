#pragma once
//#include<d3d11.h>
//#include<wrl/client.h>
//#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"DirectXTK.lib")

#include<d3dcommon.h>

#include"AdapterReader.h"
#include"Shaders.h"
#include"Vertex.h"


class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialized(HWND hwnd, int widht, int height);
	
	void RenderFrame();
protected:
	bool InitializedDirectX(HWND hwnd, int widht, int height);
	bool InitializedShaders();
	bool InitializedScene();
	
private:

	// Create DirectX
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	// Create Buffer for Draw 
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	// Rasterized
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;


	// Create shader Vertex and Pixel Shader
	VertexShader vertexShader;
	PixelShader pixelShader;


};

