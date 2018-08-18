#include "stdafx.h"
#include "cCoin.h"


cCoin::cCoin()
{
}


cCoin::~cCoin()
{
}

void cCoin::Init(D3DXVECTOR2* vPos)
{
	pvPlayer = vPos;
	isView = true;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	m_pVertex = new ST_VTX_2D[4];
	int n = rand() %50; 
	n -= 25;
	m_vPos = D3DXVECTOR2(g_Mode.Width - 30, 300.0f + n);
	m_pVertex[0].vPos = D3DXVECTOR2(m_vPos.x - 10, m_vPos.y - 10);
	m_pVertex[0].dxCol = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);

	m_pVertex[1].vPos = D3DXVECTOR2(m_vPos.x + 10, m_vPos.y - 5);
	m_pVertex[1].dxCol = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);

	m_pVertex[2].vPos = D3DXVECTOR2(m_vPos.x - 10, m_vPos.y + 10);
	m_pVertex[2].dxCol = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);

	m_pVertex[3].vPos = D3DXVECTOR2(m_vPos.x + 10, m_vPos.y + 10);
	m_pVertex[3].dxCol = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);

}

bool cCoin::Update()
{
	if (!isView)	return true;
	m_vPos.x-= 10.0f;

	if (m_vPos.x < -1280)
	{
		m_vPos = D3DXVECTOR2(0.0f, 0.0f);
		isView = false;
	}
	D3DXMatrixTranslation(&TransMtx, m_vPos.x, m_vPos.y, 0.0f);
	drawMtx = TransMtx;
	return true;
}

void cCoin::Draw()
{
	if (!isView) return;
	g_pDevice->SetFVF(m_dwFVF);
	g_pDevice->SetTransform(D3DTS_WORLD, &drawMtx);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_pVertex, sizeof(ST_VTX_2D));
}