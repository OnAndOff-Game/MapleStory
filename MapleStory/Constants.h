#pragma once

namespace Constants
{
	const int SCREEN_SIZE_X = 1024;
	const int SCREEN_SIZE_Y = 768;

	const unsigned int FPS = 60;

	const int LAYER_SIZE = 8;
	const int DIRECTION_RIGHT = 1;
	const int DIRECTION_LEFT = -1;

	const int MOB_MOVE_TIME = 2000;
	const int MOB_MOVE_TIME_MIN = 1000;

	const float PERCENT_MAX = 1.0f;
	const float PERCENT_MIN = 0.0f;
}

static inline float Lerp(float value1, float value2, float amount)
{
	return (value1 + (value2 - value1) * amount);
}


#define KEY_DOWN(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)			((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)