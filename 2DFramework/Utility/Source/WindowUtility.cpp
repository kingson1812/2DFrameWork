#include <WindowUtility.h>

LRESULT WINAPI ESWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT  lRes = 1;

	switch (msg)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
	{
		ESFRAME *esFrame = (ESFRAME*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

		if (esFrame && esFrame->drawFnc)
			esFrame->drawFnc(esFrame);

		ValidateRect(esFrame->m_eglWindowHandler, NULL);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
	{
		ESFRAME *esFrame = (ESFRAME *)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

		if (esFrame && esFrame->keyFnc)
			esFrame->keyFnc(esFrame, (unsigned char)wparam, true);
	}
	break;

	case WM_KEYUP:
	{
		ESFRAME *esFrame = (ESFRAME*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

		if (esFrame && esFrame->keyFnc)
			esFrame->keyFnc(esFrame, (unsigned char)wparam, false);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		POINTS      point;
		ESFRAME *esFrame = (ESFRAME*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

		point = MAKEPOINTS(lparam);
		if (esFrame && esFrame->mouseDownFnc)
			esFrame->mouseDownFnc(esFrame, (int)point.x, (int)point.y);
	}
	break;

	case WM_MOUSEMOVE:
		if (wparam & MK_LBUTTON)
		{
			POINTS      point;
			ESFRAME *esFrame = (ESFRAME*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

			point = MAKEPOINTS(lparam);
			if (esFrame && esFrame->mouseMoveFnc)
				esFrame->mouseMoveFnc(esFrame, (int)point.x, (int)point.y);
		}
		break;
	case WM_LBUTTONUP:
	{
		POINTS     point;
		ESFRAME *esFrame = (ESFRAME*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

		point = MAKEPOINTS(lparam);

		if (esFrame && esFrame->mouseUpFnc)
			esFrame->mouseUpFnc(esFrame, (int)point.x, (int)point.y);
	}
	break;
	default:
		lRes = DefWindowProc(hwnd, msg, wparam, lparam);
		break;
	}

	return lRes;
}

//Create a window
//@esFrame : Frame to create
//@title : Name of frame
GLboolean _CreateWindow(ESFRAME* esFrame, const char *title)
{
	WNDCLASS	wndclass = { 0 };
	DWORD			wStyle = 0;
	RECT				windowRect;
	HINSTANCE	hInstance = GetModuleHandle(NULL);


	wndclass.style = CS_OWNDC;
	wndclass.lpfnWndProc = (WNDPROC)ESWindowProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = "opengles3.0";

	if (!RegisterClass(&wndclass))
		return FALSE;

	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = esFrame->m_width;
	windowRect.bottom = esFrame->m_height;

	AdjustWindowRect(&windowRect, wStyle, FALSE);

	esFrame->m_eglWindowHandler = CreateWindow(
		"opengles3.0",
		title,
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	// Set the ESContext* to the GWL_USERDATA so that it is available to the 
	// ESWindowProc
	SetWindowLongPtr(esFrame->m_eglWindowHandler, GWL_USERDATA, (LONG)(LONG_PTR)esFrame);

	if (esFrame->m_eglWindowHandler == NULL)
		return GL_FALSE;

	ShowWindow(esFrame->m_eglWindowHandler, TRUE);

	return GL_TRUE;
}

//Window loop
//@esFrame : frame to loop
void _WinLoop(ESFRAME * esFrame)
{
	MSG msg = { 0 };
	int done = 0;
	DWORD lastTime = GetTickCount();

	while (!done)
	{
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		DWORD curTime = GetTickCount();
		float deltaTime = (float)(curTime - lastTime) / 1000.0f;
		lastTime = curTime;

		if (gotMsg)
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
			SendMessage(esFrame->m_eglWindowHandler, WM_PAINT, 0, 0);

		// Update if needed
		if (esFrame->updateFnc != NULL)
			esFrame->updateFnc(esFrame, deltaTime);
	}
}