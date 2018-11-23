#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<d3dcompiler.h>
#include<string>

#pragma comment(lib, "D3DCompiler.lib")


class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	bool  Initialized(Microsoft::WRL::ComPtr<ID3D11Device> & device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElememts);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	ID3D11InputLayout* GetInputLayout();

private:
	Microsoft::WRL::ComPtr <ID3D11VertexShader> vertex_shader;
	Microsoft::WRL::ComPtr<ID3D10Blob> vertex_shader_buffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

class PixelShader
{
public:
	PixelShader();
	~PixelShader();
	bool  Initialized(Microsoft::WRL::ComPtr<ID3D11Device> & device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElememts);
	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetBuffer();



private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D10Blob> pixel_buffer;

protected:



};