/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "AlteredBeast.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int iCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	RECT rcClient, rcWindow;
	static int iTicksTrigger;
	MSG msg;
	
	memset(&wc, 0, sizeof(wc));

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = L"AlteredBeast";

	if (!RegisterClass(&wc) || !(hWnd = CreateWindow(L"AlteredBeast", L"Altered Beast", WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX, 0, 0, 640, 448, nullptr, nullptr, hInstance, nullptr)))
		return 0;

	GetWindowRect(hWnd, &rcWindow);
	GetClientRect(hWnd, &rcClient);

	int iWidth = rcWindow.right * 2 - rcClient.right,
		iHeight = rcWindow.bottom * 2 - rcClient.bottom,
		iTicks = 0;

	SetWindowPos(hWnd, nullptr, (GetSystemMetrics(SM_CXSCREEN) - iWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - iHeight) / 2, iWidth, iHeight, SWP_NOZORDER);
	
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (true)
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			iTicks = int(GetTickCount64());

			if (iTicks > iTicksTrigger) {
				InvalidateRect(hWnd, nullptr, false);
				iTicksTrigger = iTicks + 1000 / 15;
			}
		}

	return int(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDevice, hMemory;
	PAINTSTRUCT ps;
	HBITMAP hBitmap, hPrevBitmap;
	RECT rc;

	static std::unique_ptr<AlteredBeast> ptr;

	switch (msg) {
	case WM_CREATE:
		ptr = std::make_unique<AlteredBeast>();
		ptr->Create();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		// WM_PAINT implements double buffered drawing to prevent both flickering
		// and window regions not redrawing themselves when the window is dragged
		// around the screen, mostly quickly and/or beyond the display boundaries.

		hDevice = BeginPaint(hWnd, &ps);
		hMemory = CreateCompatibleDC(hDevice);

		GetClientRect(hWnd, &rc);

		hBitmap = CreateCompatibleBitmap(hDevice, rc.right, rc.bottom),
		hPrevBitmap = HBITMAP(SelectObject(hMemory, hBitmap));

		ptr->Paint(hMemory);
		BitBlt(hDevice, rc.left, rc.top, rc.right, rc.bottom, hMemory, 0, 0, SRCCOPY);

		SelectObject(hMemory, hPrevBitmap);
		DeleteObject(hBitmap);

		DeleteDC(hMemory);
		EndPaint(hWnd, &ps);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
