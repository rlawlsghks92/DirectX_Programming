#pragma once
class Object
{
protected:

	D3DXMATRIX mtxRot;
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxScale;
	D3DXMATRIX mtxInvPivot;
	D3DXMATRIX mtxPivotTrans;
	D3DXMATRIX* pMtxParent;
	GET(D3DXMATRIX, mtxWorld, WorldMatrix);

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vScale;
	D3DXVECTOR3 vPivot;

	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPDIRECT3DVERTEXBUFFER9 pIB;

	LPDIRECT3DTEXTURE9 pTexture;
	DWORD dwFVF;
	bool isLighting;
public:
	Object();
	virtual ~Object();

	virtual void UpdateMatrix();
	virtual void DrawStart();
	virtual void DrawEnd();

	void setParentMtx(D3DXMATRIX* mtx) { pMtxParent = mtx; }
};

