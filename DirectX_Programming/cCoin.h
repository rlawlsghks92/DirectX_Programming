#pragma once
#include "cObject2d.h"

class cCoin : public cObject2d
{
	D3DXVECTOR2* pvPlayer;
public:
	cCoin();
	~cCoin();

	void Init(D3DXVECTOR2* vPos);
	virtual bool Update();
	virtual void Draw();
};

