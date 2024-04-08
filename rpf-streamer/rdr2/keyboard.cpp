/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019

	Improved by cvs0:
	- Added many more functions
	- Fixed GetTickCount buffer overflow by using a 64-bit variable.
*/

#include "keyboard.h"

const int KEYS_SIZE = 255;

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount64();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

const int NOW_PERIOD = 100, MAX_DOWN = 5000, MAX_DOWN_LONG = 30000; // ms

bool IsKeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount64() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool IsKeyDownLong(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount64() < keyStates[key].time + MAX_DOWN_LONG) && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount64() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}

DWORD GetKeyTimePressed(DWORD key)
{
	return (key < KEYS_SIZE) ? (GetTickCount64() - keyStates[key].time) : 0;
}

bool IsKeyHeldDown(DWORD key, DWORD duration)
{
	return (key < KEYS_SIZE) ? (GetKeyTimePressed(key) >= duration) : false;
}

bool IsKeyHeldWithAlt(DWORD key)
{
	return (key < KEYS_SIZE) ? keyStates[key].isWithAlt : false;
}

bool IsKeyHeldDownLong(DWORD key)
{
	return IsKeyHeldDown(key, MAX_DOWN_LONG);
}

bool IsKeyReleased(DWORD key)
{
	return (key < KEYS_SIZE) ? (keyStates[key].wasDownBefore && keyStates[key].isUpNow) : false;
}

bool IsKeyHeldDownWithShift(DWORD key)
{
	return (key < KEYS_SIZE) ? (IsKeyDown(key) && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) : false;
}

bool IsKeyJustDown(DWORD key)
{
	return (key < KEYS_SIZE) ? (!keyStates[key].wasDownBefore && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustPressed(DWORD key)
{
	return IsKeyJustDown(key) && IsKeyReleased(key);
}

bool IsKeyToggled(DWORD key)
{
	return (key < KEYS_SIZE) ? (keyStates[key].wasDownBefore && !keyStates[key].isUpNow) : false;
}
