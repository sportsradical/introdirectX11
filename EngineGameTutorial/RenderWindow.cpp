
#include "WindowContainer.h"



RenderWindow::RenderWindow()
{

}


RenderWindow::~RenderWindow()
{
	// destroy window clear in the memory
	if (this->m_hwnd != NULL)
	{
		UnregisterClass(this->m_ClassName, this->m_hinstance);
		DestroyWindow(m_hwnd);
	}
}

bool RenderWindow::Initialize(WindowContainer* pwindowContainer, HINSTANCE m_hinstance, LPCSTR m_applicationName, LPCSTR m_ClassName, int screenWidth, int screenHeight)
{
	this->m_hinstance = m_hinstance;
	this->m_applicationName = m_applicationName;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->posX = 0;
	this->posY = 0;
	this->m_hwnd = NULL;
	this->m_ClassName = m_ClassName;
	this->result = false;


	RegisteClass();

	// Determine the resolution of the clients desktop screen.
	/*this->screenWidth = GetSystemMetrics(SM_CXSCREEN);
	this->screenHeight = GetSystemMetrics(SM_CYSCREEN);*/

	// Place the window in the middle of the screen.
	this->posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
	this->posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;


	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(NULL, this->m_ClassName, this->m_applicationName,
		WS_OVERLAPPEDWINDOW | WS_POPUP | WS_SYSMENU/* | WS_MAXIMIZE*/,
		this->posX, this->posY, this->screenWidth, this->screenHeight, NULL, NULL, this->m_hinstance, pwindowContainer);


	if (this->m_hwnd == NULL)
	{
		MessageBox(NULL, "Failed Create window", "Error", NULL);
		return true;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(this->m_hwnd, SW_SHOW);
	SetForegroundWindow(this->m_hwnd);
	SetFocus(this->m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);
	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParams, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParams, lParam);
		break;
	}
}




LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParams, LPARAM lParam)
{

	switch (uMsg)
	{
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer * pwindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pwindow == nullptr) // Sanity check
			{
				MessageBox(NULL, "Critical Error:: Pointer to Window container \n is null durring WM_NCCREATE.", "ERROR::", MB_ICONERROR);
				exit(-1);
			}

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pwindow));
			
			//WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
			return pwindow->WindowProc(hwnd, uMsg, wParams, lParam);
			
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParams, lParam);
	}
	
}

bool RenderWindow::RegisteClass()
{

	WNDCLASSEX wc;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->m_ClassName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	return RegisterClassEx(&wc);
}

bool RenderWindow::ProcessMessage()
{
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	//if (PeekMessage(&msg, this->m_hwnd, 0, 0, PM_REMOVE))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

	while(PeekMessage(&msg, this->m_hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->m_hwnd))
		{
			this->m_hwnd = NULL;
			UnregisterClass(this->m_ClassName, this->m_hinstance);
			return false;
		}
	}


	return true;
}

HWND RenderWindow::GetHWND()const
{
	return this->m_hwnd;
}

int RenderWindow::GetWidthWindow()const
{
	return this->screenWidth;
}
int RenderWindow::GetHeightWindow()const
{
	return this->screenHeight;
}