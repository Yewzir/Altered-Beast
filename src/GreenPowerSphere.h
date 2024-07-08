/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef GREENPOWERSPHERE_H
#define GREENPOWERSPHERE_H

#include <memory>

#include "Bitmap.h"
#include "PowerSphere.h"

class GreenPowerSphere : public PowerSphere
{
public:
	// Constructor
	GreenPowerSphere(int, int);

	// Copy constructor and assignment operator
	GreenPowerSphere(const GreenPowerSphere&) = delete;
	GreenPowerSphere& operator=(const GreenPowerSphere&) = delete;

	// Move constructor and assignment operator
	GreenPowerSphere(GreenPowerSphere&&) = delete;
	GreenPowerSphere& operator=(GreenPowerSphere&&) = delete;

	// Destructor
	virtual ~GreenPowerSphere();

	// Methods
	void Tick();
	void Paint(HDC);
	bool HitTest(HitRegion*);

private:
	// Datamembers
	std::unique_ptr<Bitmap> m_pSpriteSheet;
};
#endif
