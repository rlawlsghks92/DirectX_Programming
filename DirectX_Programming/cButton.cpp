#include "stdafx.h"
#include "cButton.h"


cButton::cButton() 
{
	m_bView = false;
	m_bClick = false;

	m_eType = eButtonType::E_BUTTON_NONTYPE;
	m_eState = eButtonState::NORMAL;

}


cButton::~cButton()
{
	delete[] pVertex;
}

void cButton::Init(D3DXVECTOR3 vPos, eButtonType _Type, const char* _Text, D3DXVECTOR2 vSize, bool _UnLock)
{
	m_eType = _Type;
	D3DXCreateFont(g_pDevice, 12, strlen(m_szText), 2, 0, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)"±¼¸²", &myFont);
	strcpy_s(m_szText, _Text);


	pVertex = new ST_VTX_BTN[6];

	pVertex[0].vPos = D3DXVECTOR3(vPos.x,			 vPos.y, 0);
	pVertex[1].vPos = D3DXVECTOR3(vPos.x + vSize.x, vPos.y, 0);
	pVertex[2].vPos = D3DXVECTOR3(vPos.x,			 vPos.y + vSize.y, 0);
	pVertex[3].vPos = pVertex[2].vPos;
	pVertex[4].vPos = pVertex[1].vPos;
	pVertex[5].vPos = D3DXVECTOR3(vPos.x + vSize.x, vPos.y + vSize.y, 0);

	rcSize.left = vPos.x;
	rcSize.top = vPos.y;
	rcSize.right = vPos.x + vSize.x;
	rcSize.bottom = vPos.y + vSize.y;
	m_bView = true;

	
	if (_UnLock == false)
	{
		m_eState = eButtonState::LOCK;
	}
}

void cButton::Update()
{
	if (m_bView == false)return;
	if (m_eState == eButtonState::LOCK) return;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rcSize, pt))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eState == HIGHLIGHT)
			{
				m_eState = CLICK_DOWN;
			}
		}
		else
		{
			if (m_eState == CLICK_DOWN)
			{
				m_bClick = true;
			}
			m_eState = HIGHLIGHT;
		}
	}
	else
	{
		m_eState = NORMAL;
	}
}

void cButton::Draw()
{
	if (m_bView == false) return;

	g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	switch (m_eState)
	{
	case LOCK:
		for (int i = 0; i < 6; i++)
		{
			pVertex[i].dxCol = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
		break;
	case NORMAL:
		for (int i = 0; i < 6; i++)
		{
			pVertex[i].dxCol = D3DXCOLOR(0.7f,0.7f,0.7f, 1.0f);
		}
		break;
	case HIGHLIGHT:
		for (int i = 0; i < 6; i++)
		{
			pVertex[i].dxCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case CLICK_DOWN:
		for (int i = 0; i < 6; i++)
		{
			pVertex[i].dxCol = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		}
		break;
	case CLICK_UP:
		for (int i = 0; i < 6; i++)
		{
			pVertex[i].dxCol = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
		}
		break;
	}
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, pVertex, sizeof(ST_VTX_BTN));

	float x = rcSize.left + ((rcSize.right - rcSize.left) * 0.1f);
	float y = rcSize.top + ((rcSize.bottom - rcSize.top) / 2);

	myFont->DrawTextA(NULL, m_szText, strlen(m_szText), &rcSize, DT_VCENTER, D3DXCOLOR(1, 1, 1, 1.0f));
}


void cButton::pushButton(vector<cButton*>* pVec, D3DXVECTOR3 vPos,D3DXVECTOR2 vSize, eButtonType _type, const char * _text, bool _UnLock)
{
	cButton* pBtn = new cButton;
	pBtn->Init(vPos, _type, _text, vSize,_UnLock);

	pVec->push_back(pBtn);
}
//
//void cButton::Draw(Graphics * g)
//{
//	if (m_bView == false) return;
//
//	Color cr;
//	switch (m_eState)
//	{
//	case LOCK:
//		cr.SetFromCOLORREF(RGB(75, 75, 75));
//		break;
//	case NORMAL:
//		cr.SetFromCOLORREF(RGB(255, 255, 255));
//		break;
//	case HIGHLIGHT:
//		cr.SetFromCOLORREF(RGB(125, 125, 125));
//		break;
//	case CLICK_DOWN:
//		cr.SetFromCOLORREF(RGB(75, 75, 75));
//		break;
//	case CLICK_UP:
//		cr.SetFromCOLORREF(RGB(200, 200, 200));
//		break;
//	}
//	Rect rc(rcSize.left, rcSize.top, rcSize.right - rcSize.left, rcSize.bottom - rcSize.top);
//	g->FillRectangle(&SolidBrush(cr), rc);
//	//g->DrawRectangle(&Pen(&SolidBrush(cr), 50), rc);
//
//	float x = rcSize.left + ((rcSize.right - rcSize.left) * 0.1f);
//	float y = rcSize.top + ((rcSize.bottom - rcSize.top) / 2);
//	// Create string to draw.
//
//	// Draw string to screen.
//	HDC dc = g->GetHDC();
//	TextOutA(dc, x, y, m_szText, strlen(m_szText));
//	g->ReleaseHDC(dc);
//}