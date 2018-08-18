#include "stdafx.h"
#include "cTimeManager.h"

//cTimeManager::cTimeManager::m_pInstance = nullptr;
cTimeManager* cTimeManager::m_pInstance = NULL;

cTimeManager::cTimeManager()
{
}

cTimeManager::~cTimeManager()
{
}


void cTimeManager::Init()
{
	m_nElapsedTime = 0;
	m_nPrevTimStamp = GetTickCount();
	m_nFPS = 0;
	m_nFrameCount = 0;
	m_nAccElapsedTime = 0;
	m_nPrevFPS = 0;
	m_nStaticTime = 1;
}

void cTimeManager::Update()
{
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
		if (m_nStaticTime - 1 <= 1)
		{
			m_nStaticTime = 1;
			return;
		}
		m_nStaticTime--;

	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		m_nStaticTime++;

	DWORD dwCurrTimeStamp = GetTickCount();
	m_nElapsedTime = dwCurrTimeStamp - m_nPrevTimStamp;
	m_nPrevTimStamp = dwCurrTimeStamp;
	m_nAccElapsedTime += m_nElapsedTime;
	m_nFrameCount++;


	while (m_nAccElapsedTime >= 1000)
	{
		m_nAccElapsedTime -= 1000;
		m_nFPS = m_nFrameCount;
		m_nFrameCount = 0;
		m_nPrevFPS = m_nFrameCount;
	}
}

void cTimeManager::Destroy()
{
	SAFE_DELETE(m_pInstance);
}
