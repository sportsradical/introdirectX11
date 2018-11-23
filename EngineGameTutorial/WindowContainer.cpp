#include "WindowContainer.h"



WindowContainer::WindowContainer()
{
	static bool raw_input_initialized = false;
	if (raw_input_initialized == true)
	{
		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = 0;

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid) == false))
		{
			MessageBox(NULL, "Failed to Register Raw Inputs Devices", "Raw Inputs Devices ", MB_ICONERROR);
			exit(-1);
		}

	}
}


WindowContainer::~WindowContainer()
{
}

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParams, LPARAM lParam)
{


	switch (uMsg)
	{
		// Mouse Events

	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnMouseMove(x, y);
		return 0;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnLeftPressed(x, y);

		return 0;
	}
	break;

	case WM_RBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnRightPressed(x, y);
		return 0;
	}
	break;
	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnLeftRelease(x, y);
		return 0;
	}
	break;

	case WM_RBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnRightRelease(x, y);
		return 0;
	}
	break;

	case WM_MBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnMiddletPressed(x, y);
		return 0;
	}
	break;

	case WM_MBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		mouseClass.OnMiddleRelease(x, y);
		return 0;
	}
	break;


	case WM_MOUSEWHEEL:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		if (GET_WHEEL_DELTA_WPARAM(wParams) > 0)
		{
			mouseClass.OnWheelDown(x, y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParams) < 0)
		{
			mouseClass.OnWheelUp(x, y);
		}
		return 0;
	}
	break;


		// KeyBoard Events
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParams);
		if (keyEvent.IsKeysAutoRepeat())
		{
			keyEvent.OnKeyPress(keycode);
		}
		else
		{
			/*const bool wasPressed = lParam & 0x40000000;*/
			const bool wasPressed = false;
			if (!wasPressed)
			{
				keyEvent.OnKeyPress(keycode);
			}
		}
		
		return 0;
	}
	break;
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParams);
		keyEvent.OnKeyRelease(keycode);
		return 0;
	}
	break;
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParams);
		if (keyEvent.IsCharsAutoRepeat())
		{
			keyEvent.OnChar(ch);
		}
		else
		{
			/*const bool wasPressed = lParam & 0x40000000;*/
			const bool wasPressed = false;
			if (!wasPressed)
			{
				keyEvent.OnChar(ch);
			}
		}
		return 0;
	}
		break;

	// Mouse Raw and input 
	case WM_INPUT:
	{
		UINT dataSize;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

		if (dataSize > 0)
		{
			std::unique_ptr< BYTE[]> rawData = std::make_unique< BYTE[]>(dataSize);

			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawData.get(), &dataSize, sizeof(RAWINPUTHEADER) == dataSize))
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawData.get());

				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					mouseClass.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}


		return DefWindowProc(hwnd, uMsg, wParams, lParam);
	}
	break;
	default:

		/*DebugString("WINDOW PROC FROM WINDOW CONTAINER\n");*/
		return DefWindowProc(hwnd, uMsg, wParams, lParam);
		break;
	}
	
	
}

void WindowContainer::DebugString(LPCSTR m_string)
{
	OutputDebugStringA(m_string);
}
