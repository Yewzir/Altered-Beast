/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "PowerList.h"

// Methods
bool PowerList::Add(std::unique_ptr<PowerSphere> pSphere)
{
	if (GetSize() == MAX)
		return false;

	m_apSpheres.at(GetSize()) = std::move(pSphere);

	return true;
}

bool PowerList::Remove(std::unique_ptr<PowerSphere> pSphere) const
{
	for (const auto& it : m_apSpheres)
		if (it == pSphere) {
			delete it.get();
			return true;
		}

	return false;
}

int PowerList::GetSize()
{
	int iSize = 0;

	for (const auto& it : m_apSpheres)
		if (it)
			++iSize;

	return iSize;
}

void PowerList::Tick()
{
	for (const auto& it : m_apSpheres)
		if (it)
			it->Tick();
}

void PowerList::Paint(HDC hDC)
{
	for (const auto& it : m_apSpheres)
		if (it)
			it->Paint(hDC);
}

std::unique_ptr<PowerSphere> PowerList::HitTest(HitRegion* pHitRegion)
{
	for (auto& it : m_apSpheres)
		if (it && it->HitTest(pHitRegion))
			return std::move(it);

	return nullptr;
}
