#include"AdapterReader.h"

std:: vector<AdapterData> AdapterReader::adapters;



AdapterData::~AdapterData()
{

}



AdapterReader::AdapterReader()
{
}

AdapterReader::~AdapterReader()
{
}

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	if (adapters.size() > 0)
		return adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory>pFactory;

	HRESULT	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Create DXGIFactory for Enumerating adapters." + hr,  "Failed to Create DXGIFactory", MB_ICONERROR);
		exit(-1);
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;

	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		adapters.push_back(AdapterData(pAdapter));
		index += 1;
	}


	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->description);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed to Get Description for IDXGIAdapter" + hr, "", MB_ICONERROR);
	}
}