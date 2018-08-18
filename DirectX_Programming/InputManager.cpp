#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}


InputManager::~InputManager()
{

}

void InputManager::Update()
{
	memcpy_s(keyOldState, sizeof(keyOldState), keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	// 1 : 한번 눌러진 상태
	// 0 : 다시 누르면 0
	// 128 : 0 상태일 때 해당키가 눌러져있음
	// 129 : 1 상태일때 해당 키가 눌러져있음
	GetKeyboardState(keyState);

	for (int i = 0; i < MAXKEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		// 한번 눌린 상태
		if (oldState == 0 && state == 1)		keyMap[i] = KEY_DOWN;
		else if (oldState == i && state == 0)	keyMap[i] = KEY_UP;
		else if (oldState == 1 && state == 1)	keyMap[i] = KEY_PRESS;
		else									keyMap[i] = KEY_NONE;
	}
}