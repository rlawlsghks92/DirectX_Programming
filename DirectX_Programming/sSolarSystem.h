#pragma once

class sSSSun;
class sSSEarth;
class sSSMoon;

class sSolarSystem
{
	sSSSun* pSun;
	sSSEarth* pEarth;
	sSSMoon* pMoon;
public:
	sSolarSystem();
	~sSolarSystem();

	void Init();
	bool Update() ;
	void Draw() ;
};

