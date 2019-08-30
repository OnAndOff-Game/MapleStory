#include "pch.h"
#include "UIBackground.h"
#include "UIGaugeBar.h"
#include "GameUI.h"

GameUI::GameUI() : background{ nullptr },
gaugeBar{ nullptr }
{
}

GameUI::~GameUI()
{
}

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
	if (background != nullptr)
	{
		background->Release();
		delete background;
	}

	if (gaugeBar != nullptr)
	{
		gaugeBar->Release();
		delete gaugeBar;
	}
}
