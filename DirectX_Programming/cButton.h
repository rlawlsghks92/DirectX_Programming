#pragma once

#include "eButton.h"
class cButton
{
private:

	struct ST_VTX_BTN
	{
		D3DXVECTOR3 vPos;
		D3DXCOLOR dxCol;
	};
	enum eButtonState
	{
		LOCK,
		NORMAL,
		HIGHLIGHT,
		CLICK_DOWN,
		CLICK_UP,
	};
	bool m_bView;
	bool m_bClick;
	
	LPD3DXFONT myFont;
	char m_szText[32];

	RECT rcSize;
	ST_VTX_BTN* pVertex;

	eButtonType m_eType;
	eButtonState m_eState;

public:
	cButton();
	~cButton();

	void Init(D3DXVECTOR3 vPos, eButtonType _Type, const char* _Text, D3DXVECTOR2 vSize = D3DXVECTOR2(200, 100), bool _UnLock = false);
	void Update();
	void Draw();

	bool getisClick() { return m_bClick; }
	void UnClick() { m_bClick = false; }
	eButtonType GetType() { return m_eType; }

	void UnView() { m_bView = false; }
	void View() { m_bView = true; }

	void Reset(bool _isView,bool _isClick = false) { m_bClick = _isClick; m_bView = _isView; }

	int getSizeWidth() { return rcSize.right - rcSize.left; }
	int getSizeHeight() { return rcSize.bottom - rcSize.top; }
	int getPosX() { return rcSize.left; }
	int getPosY() { return rcSize.top; }
	static void pushButton(vector<cButton*>* pVec, D3DXVECTOR3 vPos,D3DXVECTOR2 vSize, eButtonType _type, const char * _text, bool _UnLock = false);
};