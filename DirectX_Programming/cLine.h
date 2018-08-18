#pragma once
#include "cObject2d.h"

class cLine : public cObject2d
{
private:

	ST_VTX_2D * Vertex;
public:
	cLine();
	~cLine();

	void Init(D3DXVECTOR2 _vPos, D3DXVECTOR2 _vSize, D3DXCOLOR _dxCol, bool bCenter);
	virtual bool Update() override;
	virtual void Draw() override;
};

