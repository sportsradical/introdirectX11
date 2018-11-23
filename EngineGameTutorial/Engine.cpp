#include "Engine.h"
#include<string>


Engine::Engine()
{
}


Engine::~Engine()
{
}

bool Engine::Initialize(HINSTANCE m_hinstance, LPCSTR m_applicationName, LPCSTR m_ClassName, int screenWidth, int screenHeight)
{
	if (!this->render_window.Initialize(this, m_hinstance, m_applicationName, m_ClassName, screenWidth, screenHeight))
		return false;
	if (!gfx.Initialized(this->render_window.GetHWND(), this->render_window.GetWidthWindow(), this->render_window.GetHeightWindow()))
		return false;

	return true;
}

bool Engine::ProcessMessage()
{
	return this->render_window.ProcessMessage();
}


void Engine::Update()
{
	// keycode char
	while (!keyEvent.CharBufferIsEmpty())
	{
		unsigned char ch = keyEvent.ReadChar();
		std::string outmsg = "char: ";
		outmsg += ch;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}

	// keycode 
	while (!keyEvent.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyEvent.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		std::string outmsg = "keycode: ";
		outmsg += keycode;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}

	// Mouse Event
	while (!mouseClass.EventBufferIsEmpty())
	{
		MouseEvent e = mouseClass.ReadEvent();
		//std::string outmsg = " X: ";
		//outmsg += std::to_string(e.GetPosX());
		//outmsg += " Y: ";
		//outmsg += std::to_string(e.GetPosY());
		//outmsg += "\n";
		//OutputDebugStringA(outmsg.c_str());

		if (e.GetType() == MouseEvent::EventType::WheelUp)
		{
			OutputDebugStringA("Mouse Wheel Up: \n");
		}
		if (e.GetType() == MouseEvent::EventType::WheelDown)
		{
			OutputDebugStringA("Mouse Wheel Down: \n");
		}

		if (e.GetType() == MouseEvent::EventType::RAW_MOVE)
		{
			std::string outmsgRaw = " Raw X: ";
			outmsgRaw += std::to_string(e.GetPosX());
			outmsgRaw += " Raw Y: ";
			outmsgRaw += std::to_string(e.GetPosY());
			outmsgRaw += "\n";
			OutputDebugStringA(outmsgRaw.c_str());
		}
	}


}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}

bool Engine::ShutdownWindows()
{
	
	return true;
}








