/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef ALTEREDBEAST_H
#define ALTEREDBEAST_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mmsystem.h>

#include "PowerList.h"
#include "Hero.h"

#pragma comment(lib, "winmm")

class AlteredBeast
{
public:
	// Meyers' Singleton
	static AlteredBeast& Singleton()
	{
		static AlteredBeast alteredBeast;
		return alteredBeast;
	}

	// Copy constructor and assignment operator
	AlteredBeast(const AlteredBeast&) = delete;
	AlteredBeast& operator=(const AlteredBeast&) = delete;

	// Move constructor and assignment operator
	AlteredBeast(AlteredBeast&&) = delete;
	AlteredBeast& operator=(AlteredBeast&&) = delete;

	// Methods
	void Create();
	void Paint(HDC);

private:
	// Constuctor
	AlteredBeast();

	// Destructor
	virtual ~AlteredBeast();

	// Datamembers
	std::unique_ptr<Bitmap> m_pBackground, m_pGrass;
	std::unique_ptr<PowerList> m_pPowerList;
	std::unique_ptr<Hero> m_pHero;
};
#endif
