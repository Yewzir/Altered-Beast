/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef HITREGION_H
#define HITREGION_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class HitRegion
{
public:
	// Constructor
	HitRegion();

	// Copy constructor and assignment operator
	HitRegion(const HitRegion&) = delete;
	HitRegion& operator=(const HitRegion&) = delete;

	// Move constructor and assignment operator
	HitRegion(HitRegion&&) = delete;
	HitRegion& operator=(HitRegion&&) = delete;

	// Destructor
	virtual ~HitRegion();

	// Methods
	bool Create(int, int, int, int);
	void Move(int, int);
	bool HitTest(HitRegion*) const;
	void Paint(HDC) const;

private:
	// Accessors
	HRGN GetHandle() const { return m_hRgn; }

	// Datamembers
	HRGN m_hRgn;
	int m_iX, m_iY, m_iWidth, m_iHeight;
};
#endif
