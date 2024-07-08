/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "BluePowerSphere.h"

// Constructor
BluePowerSphere::BluePowerSphere(int x, int y):PowerSphere(x, y)
{
	if (!m_pSpriteSheet) {
		m_pSpriteSheet = std::make_unique<Bitmap>(L"assets/bluepowersphere.bmp");

		m_iWidth = m_pSpriteSheet->GetWidth() / ANIMATIONS;
		m_iHeight = m_pSpriteSheet->GetHeight();

		m_pHitRegion = new HitRegion();
		m_pHitRegion->Create(x + m_iWidth / 4, y + m_iHeight / 3, m_iWidth / 2, m_iHeight - m_iHeight / 3);
	}
}

// Destructor
BluePowerSphere::~BluePowerSphere()
{
	delete m_pHitRegion;
}

// Methods
void BluePowerSphere::Tick()
{
	m_iAnimation = (m_iAnimation < ANIMATIONS - 1) ? ++m_iAnimation : 0;
}

void BluePowerSphere::Paint(HDC hdc)
{
	m_pSpriteSheet->Paint(hdc, { m_iAnimation * m_iWidth, 0, m_iAnimation * m_iWidth + m_iWidth, m_iHeight }, m_iX, m_iY);
}

bool BluePowerSphere::HitTest(HitRegion* pHitRegion)
{
	return m_pHitRegion->HitTest(pHitRegion);
}
