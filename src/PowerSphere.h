/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef POWERSPHERE_H
#define POWERSPHERE_H

#include "HitRegion.h"

class PowerSphere
{
public:
	// Constructor
	PowerSphere(int, int);

	// Destructor
	virtual ~PowerSphere();

	// Pure virtual methods
	virtual void Tick() = 0;
	virtual void Paint(HDC) = 0;
	virtual bool HitTest(HitRegion*) = 0;

	// Constants
	static const int ANIMATIONS = 16;

protected:
	// Datamembers
	int m_iX, m_iY, m_iWidth, m_iHeight, m_iAnimation;
	HitRegion* m_pHitRegion;
};
#endif
