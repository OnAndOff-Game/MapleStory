#pragma once

namespace Constants
{
	const int SCREEN_SIZE_X = 1024;
	const int SCREEN_SIZE_Y = 768;

	const unsigned int FPS = 60;

	//const LPCWSTR SPRITE_PATH = L"C:\\Users\\ME\\Desktop\shoot (2)\\x64\\Release\\Asset\\";
}

static inline float Lerp(float value1, float value2, float amount)
{
	return (value1 + (value2 - value1) * amount);
}

#define KEY_DOWN(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)			((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)