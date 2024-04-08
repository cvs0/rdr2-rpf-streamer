/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019

	Improved by cvs0:
	- Added many more functions
	- Fixed GetTickCount buffer overflow by using a 64-bit variable.
*/


#pragma once

#include <windows.h>

const DWORD VK_A = 0x41;
const DWORD VK_B = 0x42;
const DWORD VK_C = 0x43;
const DWORD VK_D = 0x44;
const DWORD VK_E = 0x45;
const DWORD VK_F = 0x46;
const DWORD VK_G = 0x47;
const DWORD VK_H = 0x48;
const DWORD VK_I = 0x49;
const DWORD VK_J = 0x4A;
const DWORD VK_K = 0x4B;
const DWORD VK_L = 0x4C;
const DWORD VK_M = 0x4D;
const DWORD VK_N = 0x4E;
const DWORD VK_O = 0x4F;
const DWORD VK_P = 0x50;
const DWORD VK_Q = 0x51;
const DWORD VK_R = 0x52;
const DWORD VK_S = 0x53;
const DWORD VK_T = 0x54;
const DWORD VK_U = 0x55;
const DWORD VK_V = 0x56;
const DWORD VK_W = 0x57;
const DWORD VK_X = 0x58;
const DWORD VK_Y = 0x59;
const DWORD VK_Z = 0x5A;


void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);

bool IsKeyDown(DWORD key);
bool IsKeyDownLong(DWORD key);
bool IsKeyJustUp(DWORD key, bool exclusive = true);
void ResetKeyState(DWORD key);

DWORD GetKeyTimePressed(DWORD key);
bool IsKeyHeldDown(DWORD key, DWORD duration);
bool IsKeyHeldWithAlt(DWORD key);
bool IsKeyHeldDownLong(DWORD key);
bool IsKeyReleased(DWORD key);
bool IsKeyHeldDownWithShift(DWORD key);
bool IsKeyJustDown(DWORD key);
bool IsKeyJustPressed(DWORD key);
bool IsKeyToggled(DWORD key);