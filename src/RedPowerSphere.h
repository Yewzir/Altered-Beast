/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef REDPOWERSPHERE_H
#define REDPOWERSPHERE_H

#include <memory>

#include "Bitmap.h"
#include "PowerSphere.h"

class RedPowerSphere : public PowerSphere
{
public:
	// Constructor
	RedPowerSphere(int, int);

	// Copy constructor and assignment operator
	RedPowerSphere(const RedPowerSphere&) = delete;
	RedPowerSphere& operator=(const RedPowerSphere&) = delete;

	// Move constructor and assignment operator
	RedPowerSphere(RedPowerSphere&&) = delete;
	RedPowerSphere& operator=(RedPowerSphere&&) = delete;

	// Destructor
	virtual ~RedPowerSphere();

	// Methods
	void Tick();
	void Paint(HDC);
	bool HitTest(HitRegion*);

private:
	// Datamembers
	std::unique_ptr<Bitmap> m_pSpriteSheet;
};
#endif
