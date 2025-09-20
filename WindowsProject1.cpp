#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM IParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX WndClass;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

HDC hdc;
PAINTSTRUCT ps;
static int x, y, len = 1, fx, fy;
static int oldx[100], oldy[100];
static bool flag = false;
static RECT rectview;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg)
	{
	case WM_CREATE:
		oldx[0] = 20, oldy[0] = 20;
		SetTimer(hwnd, 5, 1, NULL);
		x = 60, y = 20;
		fx = 300, fy = 300;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < len; i++) {
			Ellipse(hdc, oldx[i] - 20, oldy[i] - 20, oldx[i] + 20, oldy[i] + 20);
		}
		Ellipse(hdc, fx - 15, fy - 15, fx + 15, fy + 15);

		SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);

		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_HOME)
		{
			for (int i = 1; i <= 4; i++)
				KillTimer(hwnd, i);
			flag = false;
			x = 20, y = 20;
			InvalidateRgn(hwnd, NULL, TRUE);
		}

		if (wParam == VK_RETURN)
		{
			for (int i = 1; i <= 4; i++)
				KillTimer(hwnd, i);
			flag = !flag;
		}

		if(flag)
		{
			if (wParam == VK_RIGHT)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				SetTimer(hwnd, 1, 70, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}

			else if (wParam == VK_LEFT)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				SetTimer(hwnd, 2, 70, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else if (wParam == VK_DOWN)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				SetTimer(hwnd, 3, 70, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}

			else if (wParam == VK_UP)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				SetTimer(hwnd, 4, 70, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			for (int i = 0; i < len; i++)
			{
				oldx[i] = x;
				oldy[i] = y;
				for (int j = 1; j <= i; j++)
				{
					oldx[j] = oldx[i - 1];
					oldy[j] = oldy[i - 1];
				}
			}

			x += 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 2:
			for (int i = 0; i < len; i++)
			{
				oldx[i] = x;
				oldy[i] = y;
				for (int j = 1; j <= i; j++)
				{
					oldx[j] = oldx[i - 1];
					oldy[j] = oldy[i - 1];
				}
			}

			x -= 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 3:
			for (int i = 0; i < len; i++)
			{
				oldx[i] = x;
				oldy[i] = y;
				for (int j = 1; j <= i; j++)
				{
					oldx[j] = oldx[i - 1];
					oldy[j] = oldy[i - 1];
				}
			}

			y += 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 4:
			for (int i = 0; i < len; i++)
			{
				oldx[0] = x;
				oldy[0] = y;
				for (int j = 1; j <= i; j++)
				{
					oldx[j] = oldx[i - 1];
					oldy[j] = oldy[i - 1];
				}
			}

			y -= 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 5:
			if (x == fx && y == fy)
			{
				len += 1;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
			break;
		}
		break;
	case WM_DESTROY:
		for (int i = 1; i <= 5; i++)
			KillTimer(hwnd, i);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
