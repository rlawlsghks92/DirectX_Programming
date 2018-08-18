#include "stdafx.h"
#include "cMainGame.h"
#include "sSolarSystem.h"


cMainGame::cMainGame() : pSolarSystem(nullptr)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(pSolarSystem);
}

bool cMainGame::Init()
{
	srand(unsigned(time(NULL)));


	sState = eState::E_MAIN;
	cButton::pushButton(&vecBtn, D3DXVECTOR3(g_Mode.Width * 0.1f, g_Mode.Height* 0.1f, 0.0f),D3DXVECTOR2(200,100), eButtonType::E_BUTTON_SOLAR_SYSTEM, "SOLAR_SYSTEM",true);
	D3DXMATRIX mtxPrj;
	D3DXMatrixOrthoOffCenterLH(	&mtxPrj, 0, g_Mode.Width, g_Mode.Height, 0,-1, 1);

	g_pDevice->SetTransform(D3DTS_PROJECTION, &mtxPrj);
	fUpdateTime = 0.0f;
	fTick = 0.01f;
	return true;
}

bool cMainGame::Update()
{
	KEYBOARD->Update();
	TIMEMANAGER->Update();
	fUpdateTime += TIMEMANAGER->GetElapsedTime();

	while (fUpdateTime >= fTick)
	{
		switch (sState)
		{
		case cMainGame::E_MAIN:
			for (auto& item : vecBtn)
			{
				item->Update();
				if (item->getisClick())
				{
					if (item->GetType() == eButtonType::E_BUTTON_SOLAR_SYSTEM)
					{
						pSolarSystem = new sSolarSystem();
						pSolarSystem->Init();
						sState = E_SOLAR_SYSTEM;
						item->UnClick();
					}
				}
			}

			break;
		case cMainGame::E_SOLAR_SYSTEM:
			if (pSolarSystem)
			{
				if (pSolarSystem->Update())
				{
					SAFE_DELETE(pSolarSystem);
					sState = E_MAIN;
				}
			}
			break;
		}
		fUpdateTime -= fTick;
	}
	
	return true;
}

void cMainGame::Draw()
{
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff555555, 1.0f, 0);
	g_pDevice->BeginScene();	// 장면 시작

	switch (sState)
	{
	case cMainGame::E_MAIN:
		for (auto item : vecBtn)
			item->Draw();
		break;
	case cMainGame::E_SOLAR_SYSTEM:
		if (pSolarSystem) pSolarSystem->Draw();
		break;
	}
	
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	D3DXVECTOR2 vPos;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return TRUE;
}