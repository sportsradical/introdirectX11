#pragma once
#include<d3d11.h>
#include<wrl/client.h>
#include<vector>


#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"DXGI.lib")



class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter);
	~AdapterData();

	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC description;

private:

};




class AdapterReader
{
public:
	AdapterReader();
	~AdapterReader();
	static std::vector<AdapterData> GetAdapters();

private:
	static std::vector<AdapterData> adapters;
};

