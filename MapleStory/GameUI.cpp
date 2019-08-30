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

void GameUI::Render(Gdiplus::Graphics* _memG)
{
	// 플레이어의 정보를 나타냅니다.
	Gdiplus::Font font(L"Palatino Linotype Bold", 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	SolidBrush Brush(Color(255, 255, 255));
	_memG->DrawString(L"58", -1, &font, Gdiplus::PointF(50.0f, 665.0f), &Brush);
	_memG->DrawString(L"마법사", -1, &font, Gdiplus::PointF(120.0f, 650.0f), &Brush);
	_memG->DrawString(L"Pinkbean", -1, &font, Gdiplus::PointF(120.0f,670.0f), &Brush);
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