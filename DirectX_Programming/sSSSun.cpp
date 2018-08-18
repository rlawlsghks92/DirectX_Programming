#include "stdafx.h"
#include "sSSSun.h"


sSSSun::sSSSun()
{
}


sSSSun::~sSSSun()
{
	delete[] pVertex;
}

void sSSSun::Init()
{
	D3DXCreateTextureFromFile(g_pDevice, L"../Resources/0.png", &pTexture);

	pVertex = new ST_VTX[6];
	pVertex[0] = ST_VTX(D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
	pVertex[1] = ST_VTX(D3DXVECTOR3(100, 0, 0), D3DXVECTOR2(1, 0));
	pVertex[2] = ST_VTX(D3DXVECTOR3(0, 100, 0), D3DXVECTOR2(0, 1));
	pVertex[3] = ST_VTX(D3DXVECTOR3(0, 100, 0), D3DXVECTOR2(0, 1));
	pVertex[4] = ST_VTX(D3DXVECTOR3(100, 0, 0), D3DXVECTOR2(1, 0));
	pVertex[5] = ST_VTX(D3DXVECTOR3(100, 100, 0), D3DXVECTOR2(1, 1));

	vPos = D3DXVECTOR3(g_Mode.Width/2, g_Mode.Height/2,0);
	vPivot = D3DXVECTOR3(50, 50,0);
	dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
}

void sSSSun::Update()
{
	vRot.z += 0.1f * TIMEMANAGER->GetElapsedTime();

	D3DXMatrixRotationZ(&mtxRot,vRot.z);
	D3DXMatrixTranslation(&mtxPivotTrans, vPivot.x, vPivot.y,0.0f);
	D3DXMatrixTranslation(&mtxTrans, vPos.x, vPos.y, 0.0f);
	D3DXMatrixInverse(&mtxInvPivot, NULL, &mtxPivotTrans);

	mtxRot = mtxInvPivot * mtxRot * mtxPivotTrans;
	UpdateMatrix();
}

void sSSSun::Draw()
{
	DrawStart();
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, pVertex, sizeof(ST_VTX));
	DrawEnd();
}