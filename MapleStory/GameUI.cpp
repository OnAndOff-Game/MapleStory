#include "pch.h"
#include "UIBackground.h"
#include "UIGaugeBar.h"
#include "GameUI.h"

void GameUI::Init()
{
	background = new UIBackground();
	gaugeBar = new UIGaugeBar();

	background->Init();
	gaugeBar->Init();
}

void GameUI::Update(float _delta)
{
	background->Update(_delta);
	gaugeBar->Update(_delta);
}

void GameUI::Release()
{
	delete background;
	delete gaugeBar;
}
