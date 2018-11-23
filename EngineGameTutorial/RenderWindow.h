#pragma once
#include<Windows.h>
#include<iostream>




class WindowContainer;

class RenderWindow
{
public:
	RenderWindow();
	virtual ~RenderWindow();

	bool Initialize(WindowContainer* pwindowContainer, HINSTANCE m_hinstance, LPCSTR m_applicationName, LPCSTR	m_ClassName, int screenWidth, int screenHeight);
	bool ProcessMessage();
	HWND GetHWND()const;
	int GetWidthWindow()const;
	int GetHeightWindow()const;
private:
	bool RegisteClass();
	

private:
	LPCSTR		m_applicationName;
	LPCSTR		m_ClassName;
	HINSTANCE	m_hinstance;
	HWND		m_hwnd;

	int			posX;
	int			posY;
	int			screenWidth;
	int			screenHeight;
	bool		result;

};

