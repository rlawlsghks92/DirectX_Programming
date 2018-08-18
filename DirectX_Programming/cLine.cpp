#include "stdafx.h"
#include "cLine.h"


cLine::cLine()
{
}


cLine::~cLine()
{
}

void cLine::Init(D3DXVECTOR2 _vPos, D3DXVECTOR2 _vSize, D3DXCOLOR _dxCol, bool bCenter)
{
	m_vPos = _vPos;

	if (m_pVertex == nullptr)
		m_pVertex = new ST_VTX_2D[2];

	
	m_pVertex[0].vPos = D3DXVECTOR2(_vPos.x, _vPos.y);
	m_pVertex[0].dxCol = _dxCol;
	
	m_pVertex[1].vPos = D3DXVECTOR2(_vPos.x + _vSize.x, _vPos.y + _vSize.y);
	m_pVertex[1].dxCol = _dxCol;

	m_dwFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

}

bool cLine::Update()
{
	return false;
}

void cLine::Draw()
{
	g_pDevice->SetFVF(m_dwFVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, m_pVertex, sizeof(ST_VTX_2D));
}
