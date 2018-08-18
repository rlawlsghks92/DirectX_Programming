#pragma once

class sSolarSystem;

class cMainGame
{
private:
	vector<LPD3DXFONT*> vecFont;
	enum eState
	{
		E_MAIN,
		E_SOLAR_SYSTEM,
	};
	vector<cButton*> vecBtn;
	sSolarSystem* pSolarSystem;
	eState sState;

	float fUpdateTime;
	float fTick;
public:
	cMainGame();
	~cMainGame();

	bool Init();
	bool Update();
	void Draw();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};