#pragma once

class UIBackground;
class UIGaugeBar;

class GameUI
{
public:
	void Init();
	void Update(float _delta);
	void Render(Gdiplus::Graphics* _memG);
	void Release();
private:
	UIBackground* background;
	UIGaugeBar* gaugeBar;
};