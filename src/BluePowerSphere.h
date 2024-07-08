/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef BLUEPOWERSPHERE_H
#define BLUEPOWERSPHERE_H

#include <memory>

#include "Bitmap.h"
#include "PowerSphere.h"

class BluePowerSphere : public PowerSphere
{
public:
	// Constructor
	BluePowerSphere(int, int);

	// Copy constructor and assignment operator
	BluePowerSphere(const BluePowerSphere&) = delete;
	BluePowerSphere& operator=(const BluePowerSphere&) = delete;

	// Move constructor and assignment operator
	BluePowerSphere(BluePowerSphere&&) = delete;
	BluePowerSphere& operator=(BluePowerSphere&&) = delete;

	// Destructor
	virtual ~BluePowerSphere();

	// Methods
	void Tick();
	void Paint(HDC);
	bool HitTest(HitRegion*);

private:
	// Datamembers
	std::unique_ptr<Bitmap> m_pSpriteSheet;
};
#endif
