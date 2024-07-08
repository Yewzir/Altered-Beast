/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef HERO_H
#define HERO_H

#include <memory>

#include "Bitmap.h"
#include "HitRegion.h"

class Hero
{
public:
	// Constructor
	Hero();

	// Copy constructor and assignment operator
	Hero(const Hero&) = delete;
	Hero& operator=(const Hero&) = delete;

	// Move constructor and assignment operator
	Hero(Hero&&) = delete;
	Hero& operator=(Hero&&) = delete;

	// Destructor
	virtual ~Hero();

	// Methods
	bool Create(int, int);
	void Tick();
	void Paint(HDC) const;
	void Move(int, int);
	void Transform();
	RECT GetDimension();

	// Accessors
	bool PaintingFullscreen() const { return m_bPaintFullscreen; }
	HitRegion* GetHitRegion() { return m_pHitRegion; }

	// Constants
	static const int HUMANWIDTH = 100, HUMANHEIGHT = 144, DRAGONWIDTH = 180, DRAGONHEIGHT = 108;

private:
	// Datamembers
	static std::unique_ptr<Bitmap> m_pHumanSpriteSheet, m_pDragonSpriteSheet;
	int m_iX, m_iY, m_iSpeed, m_iAnimation, m_iForm;
	bool m_bTransforming, m_bPaintFullscreen;
	HitRegion* m_pHitRegion;
};
#endif
