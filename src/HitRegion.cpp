/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "HitRegion.h"

// Constructor
HitRegion::HitRegion():m_hRgn(NULL), m_iX(0), m_iY(0), m_iWidth(0), m_iHeight(0)
{

}

// Destructor
HitRegion::~HitRegion()
{
	DeleteObject(m_hRgn);
}

// Methods
bool HitRegion::Create(int x, int y, int width, int height)
{
	if (!(m_hRgn = CreateRectRgn(x, y, x + width, y + height))) return false;

	m_iX = x;
	m_iY = y;
	m_iWidth = width;
	m_iHeight = height;

	return true;
}

void HitRegion::Move(int x, int y)
{
	OffsetRgn(m_hRgn, x, y);

	m_iX += x;
	m_iY += y;
}

bool HitRegion::HitTest(HitRegion* regionPtr) const
{
	RECT rcSrc1, rcSrc2;

	GetRgnBox(m_hRgn, &rcSrc1);
	GetRgnBox(regionPtr->GetHandle(), &rcSrc2);

	return IntersectRect(&rcSrc1, &rcSrc1, &rcSrc2);
}

void HitRegion::Paint(HDC hdc) const
{
	HPEN hPen = CreatePen(PS_SOLID, 1, BLACK_PEN),
		hOldPen = static_cast<HPEN>(SelectObject(hdc, hPen));

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, m_iX, m_iY, m_iX + m_iWidth, m_iY + m_iHeight);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}
