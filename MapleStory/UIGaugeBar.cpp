#include "pch.h"
#include "MObject.h"
#include "Asset.h"
#include "UIGaugeBar.h"

UIGaugeBar::UIGaugeBar() : gaugeBarSprite{ nullptr }, 
gaugeBarGraduationSprite{ nullptr }
{
}

void UIGaugeBar::Init()
{
	gaugeBarSprite = new Asset(EMRenderType::eMRenderType_UI, "UI/gauge.bar.png", Gdiplus::Rect(0, 0, 470, 50), 10, true);
	gaugeBarSprite->SetOffset(Point(Constants::SCREEN_SIZE_X / 2 + 30, Constants::SCREEN_SIZE_Y / 2 + 290));
	
	gaugeBarGraduationSprite = new Asset(EMRenderType::eMRenderType_UI, "UI/gauge.graduation.png", Gdiplus::Rect(0, 0, 470, 50), 10, true);
	gaugeBarGraduationSprite->SetOffset(Point(Constants::SCREEN_SIZE_X / 2 + 30, Constants::SCREEN_SIZE_Y / 2 + 290));
}

void UIGaugeBar::LoadData(const std::string& _filename)
{
}

void UIGaugeBar::Update(float _delta)
{
	gaugeBarSprite->Update(this, _delta);
	gaugeBarGraduationSprite->Update(this, _delta);
}

void UIGaugeBar::Release()
{
	if (gaugeBarSprite != nullptr)
	{
		gaugeBarSprite->Release();
		delete gaugeBarSprite;
	}

	if (gaugeBarGraduationSprite != nullptr)
	{
		gaugeBarGraduationSprite->Release();
		delete gaugeBarGraduationSprite;
	}
}
