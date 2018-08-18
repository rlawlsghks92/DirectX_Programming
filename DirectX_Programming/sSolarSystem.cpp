#include "stdafx.h"
#include "sSolarSystem.h"

#include "sSSSun.h"
#include "sSSEarth.h"
#include "sSSMoon.h"

sSolarSystem::sSolarSystem()
{
	pSun = nullptr;
	pEarth = nullptr;
	pMoon = nullptr;
}


sSolarSystem::~sSolarSystem()
{
	SAFE_DELETE(pSun);
	SAFE_DELETE(pEarth);
	SAFE_DELETE(pMoon);
}

void sSolarSystem::Init()
{
	pSun = new sSSSun;
	pSun->Init();

	pEarth = new sSSEarth;
	pEarth->Init();

	pMoon = new sSSMoon;
	pMoon->Init();
}

bool sSolarSystem::Update()
{
	if (KEYBOARD->KeyDown(VK_ESCAPE)) 
		return true;

	pSun->Update();
	pEarth->setParentMtx(&pSun->GetWorldMatrix());
	pEarth->Update();
	pMoon->setParentMtx(&pEarth->GetWorldMatrix());
	pMoon->Update();
	return false;
}

void sSolarSystem::Draw()
{
	pSun->Draw();
	pEarth->Draw();
	pMoon->Draw();
}
