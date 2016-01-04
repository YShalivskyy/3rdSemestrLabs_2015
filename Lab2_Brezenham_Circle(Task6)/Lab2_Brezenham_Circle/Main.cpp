// Referecnce: http://www.slideshare.net/tahersb/bresenham-circle

#include <Windows.h>

const unsigned int windowWidth = 640, windowHeight = 480;

void drawPixel(HDC hdc, int xc, int yc, int x1, int y1, COLORREF color) {
	SetPixel(hdc, xc + x1, yc + y1, color);
	SetPixel(hdc, xc - x1, yc + y1, color);
	SetPixel(hdc, xc + x1, yc - y1, color);
	SetPixel(hdc, xc - x1, yc - y1, color);
	SetPixel(hdc, xc + y1, yc + x1, color);
	SetPixel(hdc, xc - y1, yc + x1, color);
	SetPixel(hdc, xc + y1, yc - x1, color);
	SetPixel(hdc, xc - y1, yc - x1, color);
}

// about the algorithm which is implemented below you can read in the reference 
// Referecnce: http://www.slideshare.net/tahersb/bresenham-circle
// xc and yc - coordinates of the centre of the circle
void Ellipse(HDC hdc, int xc, int yc, int radius, COLORREF color)
{
	int x1, y1, d;

	x1 = 0;
	y1 = radius;
	d = 3 - 2 * radius; // decision parametr

	while (x1 < y1) {
		Sleep(10);
		drawPixel(hdc, xc, yc, x1, y1, color);

		x1 = x1 + 1;
		if (d < 0) {
			d = d + 4 * x1 + 6;
		}
		else {
			y1 = y1 - 1;
			d = d + 4 * (x1 - y1) + 10;
		}
		Sleep(10);
		drawPixel(hdc, xc, yc, x1, y1, color);
	}
}

DWORD __stdcall RenderThreadMain(void* args)
{
	HWND hWnd = HWND(args);


	HDC hdc = GetDC(hWnd);

	// calling the function which draws ellipse
	Ellipse(hdc, windowWidth / 2, windowHeight / 2, 150, RGB(0, 0, 0));
	//Ellipse(hdc, 150, 150, 100, RGB(255, 255, 255)); // making circle white 

	ReleaseDC(hWnd, hdc);

	return 0;
}

LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE, char*, int)
{
	const wchar_t windowClassName[] = L"WndCLassName";

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = windowClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	RegisterClassEx(&wcex);

	// creating window
	HWND hWnd = CreateWindowEx(0, windowClassName, L"BrezenhemCircle",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	DWORD threadId = 0;

	// create Thread, thus allowing to manipulate image
	HANDLE hThread = CreateThread(nullptr, 0, RenderThreadMain, (void*)hWnd, 0, &threadId);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}