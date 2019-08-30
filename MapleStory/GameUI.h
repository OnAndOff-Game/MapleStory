#pragma once

class UIBackground;
class UIGaugeBar;

class GameUI
{
public:

	GameUI();
	~GameUI();

	void Init();
	void Update(float _delta);
	void Render(Gdiplus::Graphics* _memG);
	void Release();

	void GetPlayerInfo(MCharacter* player);

private:
	UIBackground* background;
	UIGaugeBar* gaugeBar;

	int playerHP;
	int playerMaxHP;
	int playerMP;
	int playerMaxMP;
};