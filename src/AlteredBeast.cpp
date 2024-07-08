/*
 * * * * * * * * * * * * * * * * * * * * * *
 *     Copyright (c) 2024 Hicham Omari     *
 *                                         *
 * https://github.com/Yewzir/Altered-Beast *
 * * * * * * * * * * * * * * * * * * * * * *
 */

#include "AlteredBeast.h"
#include "BluePowerSphere.h"
#include "GreenPowerSphere.h"
#include "RedPowerSphere.h"

// Constructor
AlteredBeast::AlteredBeast()
{
	
}

// Destructor
AlteredBeast::~AlteredBeast()
{

}

// Methods
void AlteredBeast::Create()
{
	m_pBackground = std::make_unique<Bitmap>(L"assets/background.bmp");
	m_pGrass = std::make_unique<Bitmap>(L"assets/grass.bmp");

	m_pPowerList = std::make_unique<PowerList>();
	m_pHero = std::make_unique<Hero>();

	if (m_pHero->Create(0, 230)) {
		m_pPowerList->Add(std::make_unique<RedPowerSphere>(150, 280));
		m_pPowerList->Add(std::make_unique<GreenPowerSphere>(300, 280));
		m_pPowerList->Add(std::make_unique<BluePowerSphere>(450, 280));
	}

	// Playback of a MIDI audio file from begin to end, without additional
	// features like pausing, rewinding, fast-forwarding, stopping, volume
	// control by the application and so on, is actually not worth a class
	// definition for now so until then this constructor will do just fine.

	MCI_OPEN_PARMS mciOpenParms;
	MCI_PLAY_PARMS mciPlayParms;

	memset(&mciOpenParms, 0, sizeof(mciOpenParms));
	memset(&mciPlayParms, 0, sizeof(mciPlayParms));

	mciOpenParms.lpstrDeviceType = L"sequencer";
	mciOpenParms.lpstrElementName = L"assets/alteredbeast.mid";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, DWORD_PTR(&mciOpenParms));
	mciSendCommand(mciOpenParms.wDeviceID, MCI_PLAY, NULL, DWORD_PTR(&mciPlayParms));
}

void AlteredBeast::Paint(HDC hDC)
{
	m_pBackground->Paint(hDC, 0, 0);

	m_pPowerList->Paint(hDC);
	m_pPowerList->Tick();

	m_pHero->Paint(hDC);
	m_pHero->Tick();

	if (!m_pHero->PaintingFullscreen())
		m_pGrass->Paint(hDC, 1, 320);

	std::unique_ptr<PowerSphere> pSphere = m_pPowerList->HitTest(m_pHero->GetHitRegion());

	if (pSphere) {
		m_pPowerList->Remove(std::move(pSphere));
		m_pHero->Transform();
	}

	if (m_pHero->GetDimension().left > 790)
		PostQuitMessage(0);
}
