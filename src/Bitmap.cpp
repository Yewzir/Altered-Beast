/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "Bitmap.h"

// Constructor
Bitmap::Bitmap():m_hBitmap(nullptr), m_iWidth(0), m_iHeight(0), m_dwAlpha()
{

}

Bitmap::Bitmap(int iID, DWORD dwAlpha):m_dwAlpha(dwAlpha)
{
	BITMAP bm;
	memset(&bm, 0, sizeof(bm));

	m_hBitmap = LoadBitmap(GetModuleHandle(nullptr), MAKEINTRESOURCE(iID));

	GetObject(m_hBitmap, sizeof(bm), &bm);

	m_iWidth = bm.bmWidth;
	m_iHeight = bm.bmHeight;
}

Bitmap::Bitmap(LPCWSTR szFile, DWORD dwAlpha):m_dwAlpha(dwAlpha)
{
	BITMAP bm;
	memset(&bm, 0, sizeof(bm));

	m_hBitmap = HBITMAP(LoadImage(GetModuleHandle(nullptr), szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	GetObject(m_hBitmap, sizeof(bm), &bm);

	m_iWidth = bm.bmWidth;
	m_iHeight = bm.bmHeight;
}

// Destructor
Bitmap::~Bitmap()
{
	DeleteObject(m_hBitmap);
}

// Methods
bool Bitmap::Exists() const
{
	return m_hBitmap != nullptr;
}

void Bitmap::Paint(HDC hDC, int x, int y) const
{
	HDC hMemory = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = HBITMAP(SelectObject(hMemory, m_hBitmap));

	TransparentBlt(hDC, x, y, m_iWidth, m_iHeight, hMemory, 0, 0, m_iWidth, m_iHeight, m_dwAlpha);

	SelectObject(hMemory, hBitmap);
	DeleteObject(hMemory);
}

void Bitmap::Paint(HDC hDC, RECT rc, int x, int y) const
{
	HDC hMemory = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = HBITMAP(SelectObject(hMemory, m_hBitmap));

	TransparentBlt(hDC, x, y, rc.right - rc.left, rc.bottom - rc.top, hMemory, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, m_dwAlpha);

	SelectObject(hMemory, hBitmap);
	DeleteObject(hMemory);
}
