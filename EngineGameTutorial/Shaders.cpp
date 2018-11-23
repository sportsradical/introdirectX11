#include"Shaders.h"

VertexShader::VertexShader()
{
	this->vertex_shader = nullptr;
	this->vertex_shader_buffer = nullptr;
	this->inputLayout = nullptr;
}

VertexShader::~VertexShader()
{
}

bool VertexShader::Initialized(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElememts)
{

	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), this->vertex_shader_buffer.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Load Vertex Shade", "Load Vertex Shade", MB_ICONERROR);
		return true;
	}


	hr = device->CreateVertexShader(this->vertex_shader_buffer->GetBufferPointer(), this->vertex_shader_buffer->GetBufferSize(), NULL, this->vertex_shader.GetAddressOf());

	
	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Create Vertex Shade", "Load Vertex Shade", MB_ICONSTOP);
		return false;
	}

	hr = device->CreateInputLayout(layout, numElememts, this->vertex_shader_buffer->GetBufferPointer(), this->vertex_shader_buffer->GetBufferSize(), this->inputLayout.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed Create Input Layout" + hr, "Create Input Layout", MB_ICONERROR);
		return false;
	}

	
	return true;
}


ID3D11VertexShader * VertexShader::GetShader()
{
	return this->vertex_shader.Get();
}

ID3D10Blob * VertexShader::GetBuffer()
{
	return this->vertex_shader_buffer.Get();
}

ID3D11InputLayout * VertexShader::GetInputLayout()
{
	return this->inputLayout.Get();
}


////////////////			PixelShader			 ///////////////

////////////////			PixelShader			 ///////////////

PixelShader::PixelShader()
{
	this->pixelShader = nullptr;
	this->pixel_buffer = nullptr;
}

PixelShader::~PixelShader()
{

}



bool  PixelShader::Initialized(Microsoft::WRL::ComPtr<ID3D11Device> & device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElememts)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), this->pixel_buffer.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Load Pixel Shade", "Load Shade", MB_ICONERROR);
		return true;
	}


	hr = device->CreatePixelShader(this->pixel_buffer.Get()->GetBufferPointer(), this->pixel_buffer.Get()->GetBufferSize(), NULL, this->pixelShader.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Create Pixel Shade", "Load Shade", MB_ICONERROR);
		return false;
	}



	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return pixelShader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return pixel_buffer.Get();
}