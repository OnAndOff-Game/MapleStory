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

static inline bool AABBIntersectionSize(Gdiplus::Rect const& _a_rc, Gdiplus::Rect const& _b_rc)
{
	if ((_a_rc.X + _a_rc.Width < _b_rc.X) || (_a_rc.X > _b_rc.X + _b_rc.Width))
		return 0;
	
	if ((_a_rc.Y + _a_rc.Height < _b_rc.Y) || (_a_rc.Y > _b_rc.Y + _b_rc.Height))
		return 0;

	return 1;
}

#define KEY_DOWN(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)			((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)