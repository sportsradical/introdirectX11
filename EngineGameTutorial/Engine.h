#pragma once
#include"WindowContainer.h"

class Engine:public WindowContainer
{
public:
	Engine();
	~Engine();


	bool Initialize(HINSTANCE m_hinstance, LPCSTR m_applicationName, LPCSTR	m_ClassName, int screenWidth, int screenHeight);
	bool ProcessMessage();
	void Update();
	void RenderFrame();
	bool ShutdownWindows();
protected:


};

