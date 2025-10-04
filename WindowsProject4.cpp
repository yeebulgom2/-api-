#include <windows.h>
#include <TCHAR.H>
#include <random>
#include <time.h>

int weight, height;


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

	weight = 800;
	height = 800;

	RegisterClassEx(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		weight,
		height,
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

int x, y, len = 1, fx, fy, speed;
int oldx[1000], oldy[1000];
bool flag_move = false, flag_dead = false;
bool left = false, right = false, up = false, down = false;
RECT rect;
HDC hdc;
PAINTSTRUCT ps;




LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg)
	{
	case WM_CREATE:
		speed = 70;
		oldx[0] = 20, oldy[0] = 20;
		x = 60, y = 20;
		fx = 300, fy = 300;
		SetTimer(hwnd, 5, speed, NULL);
		GetClientRect(hwnd, &rect);
		break;
	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		Rectangle(hdc, 0, 0, 760, 760);

		if (flag_dead)
		{
			up = false;
			down = false;
			right = false;
			left = false;
			for (int i = 1; i <= 4; i++)
				KillTimer(hwnd, i);
			DrawText(hdc, _T("GAME OVER\npress home to retry"), 29, &rect, DT_CENTER | DT_VCENTER);
			flag_dead = false;
		}

		for (int i = 0; i < len; i++) {
			Ellipse(hdc, oldx[i] - 20, oldy[i] - 20, oldx[i] + 20, oldy[i] + 20);
		}



		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, fx - 15, fy - 15, fx + 15, fy + 15);

		SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);

		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_HOME)
		{
			up = false;
			down = false;
			right = false;
			left = false;
			for (int i = 1; i <= 4; i++)
				KillTimer(hwnd, i);
			flag_dead = false;
			flag_move = false;

			x = 60, y = 20;
			fx = 300, fy = 300;
			oldx[0] = 20, oldy[0] = 20;
			for (int i = 0; i < len; i++)
			{
				oldx[i + 1] = NULL;
				oldy[i + 1] = NULL;
			}
			len = 1;
			InvalidateRgn(hwnd, NULL, TRUE);
		}

		if (wParam == VK_RETURN)
		{
			for (int i = 1; i <= 4; i++)
				KillTimer(hwnd, i);
			flag_move = !flag_move;
		}

		if (flag_move)
		{
			if (wParam == VK_RIGHT && !left)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				up = false;
				down = false;
				right = true;
				left = false;
				SetTimer(hwnd, 1, speed, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}

			else if (wParam == VK_LEFT && !right)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				up = false;
				down = false;
				right = false;
				left = true;
				SetTimer(hwnd, 2, speed, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}

			else if (wParam == VK_DOWN && !up)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				up = false;
				down = true;
				right = false;
				left = false;
				SetTimer(hwnd, 3, speed, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}

			else if (wParam == VK_UP && !down)
			{
				for (int i = 1; i <= 4; i++)
					KillTimer(hwnd, i);
				up = true;
				down = false;
				right = false;
				left = false;
				SetTimer(hwnd, 4, speed, NULL);
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			for (int i = len; i > 0; i--)
			{
				oldx[i] = oldx[i - 1];
				oldy[i] = oldy[i - 1];

			}
			oldx[0] = x;
			oldy[0] = y;

			x += 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 2:
			for (int i = len; i > 0; i--)
			{
				oldx[i] = oldx[i - 1];
				oldy[i] = oldy[i - 1];

			}
			oldx[0] = x;
			oldy[0] = y;

			x -= 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 3:
			for (int i = len; i > 0; i--)
			{
				oldx[i] = oldx[i - 1];
				oldy[i] = oldy[i - 1];

			}
			oldx[0] = x;
			oldy[0] = y;

			y += 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 4:
			for (int i = len; i > 0; i--)
			{
				oldx[i] = oldx[i - 1];
				oldy[i] = oldy[i - 1];

			}
			oldx[0] = x;
			oldy[0] = y;

			y -= 40;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 5:

			for (int i = 0; i < len; i++) {
				if (oldx[i] == x && oldy[i] == y)
				{
					flag_move = false;
					flag_dead = true;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}

			if (x + 20 > rect.right || x - 20 < rect.left || y - 20 < rect.top || y + 20 > rect.bottom) {
				flag_move = false;
				flag_dead = true;
			}

			if (x == fx && y == fy)
			{
				len += 1;

				int clientWidth = rect.right - rect.left;
				int clientHeight = rect.bottom - rect.top;

				srand(time(NULL));
				fx = ((rand() % (clientWidth / 40)) * 40) + 20;
				fy = ((rand() % (clientHeight / 40)) * 40) + 20;

				InvalidateRect(hwnd, NULL, TRUE);
				UpdateWindow(hwnd);
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