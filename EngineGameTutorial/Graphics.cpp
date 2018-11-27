#include"Graphics.h"

Graphics::Graphics()
{
	this->device =				nullptr;
	this->deviceContext =		nullptr;
	this->swapChain =			nullptr;
	this->renderTargetView =	nullptr;
	this->vertexBuffer =		nullptr;
	

}

Graphics::~Graphics()
{
}

bool Graphics::Initialized(HWND hwnd, int widht, int height)
{
	// Initialized DirectX
	if (!InitializedDirectX(hwnd, widht, height)){return false;}

	// Initialized Shaders
	if (!InitializedShaders()){return false;}

	// Initialized Scene
	if (!InitializedScene()){ return false; }

	return true;
}

void Graphics::RenderFrame()
{
	float bgColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgColor);

	this->deviceContext->IASetInputLayout(this->vertexShader.GetInputLayout());
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	this->deviceContext->Draw(3, 0);
	this->swapChain->Present(1, NULL);
}


bool Graphics::InitializedDirectX(HWND hwnd, int widht, int height)
{
	// information drives installes
	std::vector<AdapterData> adapters = AdapterReader::GetAdapters();

	// check if adapters inferior 1

	if (adapters.size() < 1)
	{
		MessageBox(NULL, "No DXGI Adapters found", "No DXGI Adapters", MB_ICONERROR);
		return false;
	}

	// Initialized SwapChain


	DXGI_SWAP_CHAIN_DESC scd;
	scd.BufferDesc.Width = widht;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	HRESULT hr;
 	hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter, D3D_DRIVER_TYPE_UNKNOWN,
		NULL, NULL, NULL, 0, D3D11_SDK_VERSION, &scd, this->swapChain.GetAddressOf(),
		this->device.GetAddressOf(), NULL, this->deviceContext.GetAddressOf());


	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Create device and Swapchain" + hr, "Create device", MB_ICONERROR);
		return false;
	}


	// Create is pointer for return buffer

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backbuffer.GetAddressOf()));

	if (FAILED(hr))
	{
		MessageBox(NULL, "GetBuffer Failed" + hr, "GetBuffer", MB_ICONERROR);
		return false;
	}

	hr = this->device->CreateRenderTargetView(backbuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
	
	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Create Render Targe View" + hr, "Create Render", MB_ICONERROR);
		return false;
	}

	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), NULL);


	// Create Viewports
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0 ;
	viewport.TopLeftY = 0;
	viewport.Height = static_cast<float>(height);
	viewport.Width = static_cast<float>(widht);


	// Set THe Viewport
	this->deviceContext->RSSetViewports(1, &viewport);


	// Rasterized
	D3D11_RASTERIZER_DESC rasterizertStateDesc;
	ZeroMemory(&rasterizertStateDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizertStateDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizertStateDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	hr = this->device->CreateRasterizerState(&rasterizertStateDesc, this->rasterizerState.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed Create RasterizerState", "RasterizerState", NULL);
		return false;
	}

	return true;
}

bool Graphics::InitializedShaders()
{

//	std::wstring shaderfolder = L"";
//#pragma region DetermineShaderPath
//	if (IsDebuggerPresent() == TRUE)
//	{
//#ifdef _DEBUG //Debug Mode
//#ifdef _WIN64 //x64
//		shaderfolder = L"..\\Editor\\shaders\\";
//#else  //x86 (Win32)
//		shaderfolder = L"..\\Editor\\shaders\\";
//#endif
//#else //Release Mode
//#ifdef _WIN64 //x64
//		shaderfolder = L"..\\Editor\\shaders\\";
//#else  //x86 (Win32)
//		shaderfolder = L"..\\Editor\\shaders\\";
//#endif
//#endif
//	}

	//// Create Shader Vvertex
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA}
	};

	UINT numElememts = ARRAYSIZE(layout);

	// Initialized Shaders
	// Open File for Read
	
	/*shaderfolder +*/
	/*shaderfolder + L"VertexShader.cso*/

	std::wstring filePath = L"..\\Editor\\shaders\\";

	if (filePath.c_str())
	{
		MessageBox(NULL, "Load Shader and vertex", "", NULL);

		if (!vertexShader.Initialized(this->device, filePath + L"VertexShader.cso", layout, numElememts))
		{
			return false;
		}


		/*shaderfolder +*/
		if (!pixelShader.Initialized(this->device, filePath + L"PixelShader.cso", layout, numElememts))
		{
			return false;
		}


		return true;
	}

	

	return true;
}

bool Graphics::InitializedScene()
{
	Vertex v[]=
	{
		Vertex(-0.5f, -0.5f),
		Vertex(0.0f, 0.5f),
		Vertex(0.5f, -0.5f),
	};

	// Initialized Vertex Buffer

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;


	// check Error

	HRESULT hr = this->device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, this->vertexBuffer.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed Create Vertex Buffer", "Vertex Buffer", MB_ICONERROR);
		return false;
	}

	return true;
}


