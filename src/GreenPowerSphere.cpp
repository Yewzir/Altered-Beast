/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "GreenPowerSphere.h"

// Constructor
GreenPowerSphere::GreenPowerSphere(int x, int y):PowerSphere(x, y)
{
	if (!m_pSpriteSheet) {
		m_pSpriteSheet = std::make_unique<Bitmap>(L"assets/greenpowersphere.bmp");

		m_iWidth = m_pSpriteSheet->GetWidth() / ANIMATIONS;
		m_iHeight = m_pSpriteSheet->GetHeight();

		m_pHitRegion = new HitRegion();
		m_pHitRegion->Create(x + m_iWidth / 4, y + m_iHeight / 3, m_iWidth / 2, m_iHeight - m_iHeight / 3);
	}
}

// Destructor
GreenPowerSphere::~GreenPowerSphere()
{
	delete m_pHitRegion;
}

// Methods
void GreenPowerSphere::Tick()
{
	m_iAnimation = (m_iAnimation < ANIMATIONS - 2) ? m_iAnimation + 2 : 0;
}

void GreenPowerSphere::Paint(HDC hdc)
{
	m_pSpriteSheet->Paint(hdc, { m_iAnimation * m_iWidth, 0, m_iAnimation * m_iWidth + m_iWidth, m_iHeight }, m_iX, m_iY);
}

bool GreenPowerSphere::HitTest(HitRegion* regionPtr)
{
	return m_pHitRegion->HitTest(regionPtr);
}
