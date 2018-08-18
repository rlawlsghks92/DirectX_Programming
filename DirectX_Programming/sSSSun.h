#pragma once
#include "Object.h"

class sSSSun : public Object
{
	struct ST_VTX
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR2 vUV;
		ST_VTX() {};
		ST_VTX(D3DXVECTOR3 pos, D3DXVECTOR2 uv)
		{
			vPos = pos;
			vUV = uv;
		}
	};

	ST_VTX* pVertex;
public:
	sSSSun();
	virtual ~sSSSun();

	void Init();
	void Update();
	void Draw();
};

