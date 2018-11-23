#pragma once

#include"RenderWindow.h"
#include"KeyboardClass.h"
#include"MouseClass.h"
#include"Graphics.h"




class WindowContainer
{
public:
	WindowContainer();
	~WindowContainer();

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParams, LPARAM lParam);
	void DebugString(LPCSTR m_string);

protected:
	RenderWindow render_window;
	CKeyboardClass keyEvent;
	MouseClass mouseClass;

	Graphics gfx;
};

