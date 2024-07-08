/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef POWERLIST_H
#define POWERLIST_H

#include <array>
#include <memory>

#include "PowerSphere.h"

class PowerList
{
public:
	// Constructor
	PowerList() = default;

	// Copy constructor and assignment operator
	PowerList(const PowerList&) = delete;
	PowerList& operator=(const PowerList&) = delete;

	// Move constructor and assignment operator
	PowerList(PowerList&&) = delete;
	PowerList& operator=(PowerList&&) = delete;

	// Destructor
	virtual ~PowerList() = default;

	// Methods
	bool Add(std::unique_ptr<PowerSphere>);
	bool Remove(std::unique_ptr<PowerSphere>) const;
	int GetSize();
	void Tick();
	void Paint(HDC);
	std::unique_ptr<PowerSphere> HitTest(HitRegion*);

	// Constants
	static const int MAX = 5;

private:
	// Datamembers
	std::array<std::unique_ptr<PowerSphere>, MAX> m_apSpheres;
};
#endif
