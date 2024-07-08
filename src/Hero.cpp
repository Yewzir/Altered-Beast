/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "Hero.h"

std::unique_ptr<Bitmap> Hero::m_pHumanSpriteSheet, Hero::m_pDragonSpriteSheet;

// Constructor
Hero::Hero():m_iX(0), m_iY(0), m_iSpeed(0), m_iAnimation(0), m_iForm(0), m_bTransforming(false), m_bPaintFullscreen(false), m_pHitRegion(nullptr)
{
	if (!m_pHumanSpriteSheet && !m_pDragonSpriteSheet) {
		m_pHumanSpriteSheet = std::make_unique<Bitmap>(L"assets/human.bmp");
		m_pDragonSpriteSheet = std::make_unique<Bitmap>(L"assets/dragon.bmp");
	}
}

// Destructor
Hero::~Hero()
{
	delete m_pHitRegion;
}

// Methods
bool Hero::Create(int x, int y)
{
	if (!m_pHumanSpriteSheet->Exists() || !m_pDragonSpriteSheet->Exists()) return false;

	m_iX = x;
	m_iY = y;
	m_pHitRegion = new HitRegion();
	m_pHitRegion->Create(x, y, GetDimension().right / 3, GetDimension().bottom);

	return true;
}

void Hero::Tick()
{
	if (!m_bTransforming) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (m_iForm < 3)
				m_iAnimation = (m_iAnimation < 4) ? ++m_iAnimation : 1;

			m_iSpeed = 18;

			Move(m_iSpeed, 0);
		} else {
			if (m_iForm < 3)
				m_iAnimation = 0;

			m_iSpeed = 0;
		}
		if (m_iForm == 3)
			m_iAnimation = (m_iAnimation < 4) ? ++m_iAnimation : 0;
	} else {
		if (m_iAnimation < 7) ++m_iAnimation; else {
			++m_iForm;
			m_iAnimation = m_bTransforming = m_bPaintFullscreen = false;
		}
	}
}

void Hero::Paint(HDC hDC) const
{
	RECT rc;
	SetRectEmpty(&rc);

	if (m_iForm != 3) {
		if (m_bPaintFullscreen) {
			HBRUSH hBrush = CreateSolidBrush(m_iAnimation % 2 ? RGB(99, 198, 115) : RGB(0, 66, 12)),
				hOldBrush = HBRUSH(SelectObject(hDC, hBrush));

			SelectObject(hDC, GetStockObject(NULL_PEN));
			Rectangle(hDC, 0, 0, 641, 449);

			SelectObject(hDC, hOldBrush);
			DeleteObject(hBrush);
		} else {
			rc.left = m_iAnimation * HUMANWIDTH;
			rc.top = m_iForm * HUMANHEIGHT * 2;

			if (m_bTransforming) {
				rc.top += HUMANHEIGHT;
				if (m_iAnimation > 2)
					rc.left = HUMANWIDTH * 3;
			}

			m_pHumanSpriteSheet->Paint(hDC, { rc.left, rc.top, rc.left + HUMANWIDTH, rc.top + HUMANHEIGHT }, m_iX, m_iY);
		}
	} else {
		rc.left = m_iAnimation * DRAGONWIDTH;

		m_pDragonSpriteSheet->Paint(hDC, { rc.left, 0, rc.left + DRAGONWIDTH, DRAGONHEIGHT }, m_iX - HUMANWIDTH / 2, m_iY);
	}
}

void Hero::Move(int x, int y)
{
	m_iX += x;
	m_iY += y;
	m_pHitRegion->Move(x, y);
}

void Hero::Transform()
{
	m_iAnimation = 0;
	m_bTransforming = true;
	m_bPaintFullscreen = m_iForm == 2;
}

RECT Hero::GetDimension()
{
	return { m_iX, m_iY, m_iForm < 3 ? HUMANWIDTH : DRAGONWIDTH, m_iForm < 3 ? HUMANHEIGHT : DRAGONHEIGHT };
}
