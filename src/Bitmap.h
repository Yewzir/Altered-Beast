/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef BITMAP_H
#define BITMAP_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma comment(lib, "msimg32")

class Bitmap
{
public:
	// Constructor
	Bitmap();
	Bitmap(int, DWORD = MAGENTA);
	Bitmap(LPCWSTR, DWORD = MAGENTA);

	// Copy constructor and assignment operator
	Bitmap(const Bitmap&) = delete;
	Bitmap& operator=(const Bitmap&) = delete;

	// Move constructor and assignment operator
	Bitmap(Bitmap&&) = delete;
	Bitmap& operator=(Bitmap&&) = delete;

	// Destructor
	virtual ~Bitmap();

	// Methods
	bool Exists() const;
	void Paint(HDC, int, int) const;
	void Paint(HDC, RECT, int, int) const;

	// Mutators
	void SetAlphaSource(DWORD dwAlpha) { m_dwAlpha = dwAlpha; }

	// Accessors
	int GetWidth() const { return m_iWidth; }
	int GetHeight() const { return m_iHeight; }

	static const COLORREF MAGENTA = RGB(255, 0, 255);

private:
	// Datamembers
	HBITMAP m_hBitmap;
	int m_iWidth, m_iHeight;
	DWORD m_dwAlpha;
};
#endif
