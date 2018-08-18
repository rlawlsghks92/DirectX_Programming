#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScale);
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixIdentity(&mtxInvPivot);
	D3DXMatrixIdentity(&mtxPivotTrans);

	vPos = D3DXVECTOR3(0,0,0);
	vRot = D3DXVECTOR3(0, 0, 0);
	vDir = D3DXVECTOR3(0, 0, 0);
	vScale = D3DXVECTOR3(1, 1, 1);
	vPivot = D3DXVECTOR3(0,0,0);

	pVB = nullptr;
	pIB = nullptr;
	pTexture = nullptr;
	pMtxParent = nullptr;

	dwFVF = 0x00000000;
	isLighting = false;
}


Object::~Object()
{
	pTexture->Release();
}

void Object::UpdateMatrix()
{
	//D3DXMatrixScaling(&mtxScale, vScale.x, vScale.y, vScale.z);
	//D3DXMATRIX Rx, Ry, Rz;

	//D3DXMatrixRotationX(&Rx, vRot.x);
	//D3DXMatrixRotationX(&Ry, vRot.y);
	//D3DXMatrixRotationX(&Rz, vRot.z);
	//mtxRot = Rx * Ry* Rz;

	//D3DXMatrixTranslation(&mtxTrans, vPos.x, vPos.y, vPos.z);

	mtxWorld = mtxScale * mtxRot* mtxTrans;

	if (pMtxParent != nullptr)
	{
		mtxWorld = mtxWorld * (*pMtxParent) ;
	}
}

void Object::DrawStart()
{
	g_pDevice->SetFVF(dwFVF);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, isLighting);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// ¾ËÆÄ¿¬»êÀ» ÇÏ´Âµ¥ µ¡¼ÀÀ¸·Î ¿¬»ê
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	// µÞ ¹è°æ »ö¿¡´Ù°¡ »Ñ¸± »ö±òÀÇ ¿ª¼ö¸¦ °ö
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// »Ñ¸± »ö±ò¿¡´Ù°¡ ÀÚ±âÀÚ½ÅÀÇ ¾ËÆÄ°ªÀ» °ö
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	if (pTexture != nullptr)		g_pDevice->SetTexture(0, pTexture);
	g_pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

}

void Object::DrawEnd()
{
	D3DXMATRIX iden;
	D3DXMatrixIdentity(&iden);
	g_pDevice->SetTransform(D3DTS_WORLD, &iden); 
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
}
