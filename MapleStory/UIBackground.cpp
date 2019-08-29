#include "pch.h"
#include "MObject.h"
#include "Asset.h"
#include "UIBackground.h"

UIBackground::UIBackground()
{
}

void UIBackground::Init()
{
	baseBackgroundSprite[0] = new Asset(EMRenderType::eMR_UI,"UI/base.backgrnd.png",
		Gdiplus::Rect(0,0,Constants::SCREEN_SIZE_X,120),10,true);
	baseBackgroundSprite[1] = new Asset(EMRenderType::eMR_UI, "UI/base.StatusBackground.png", 
		Gdiplus::Rect(0, 0, 800, 70), 10, true);

	baseBackgroundSprite[0]->SetOffset(Point(0, 18));
	baseBackgroundSprite[1]->SetOffset(Point(-110, 46));

	SetPosition(Point(Constants::SCREEN_SIZE_X / 2, Constants::SCREEN_SIZE_Y - 140));
}

void UIBackground::LoadData(const std::string& _filename)
{
}

void UIBackground::Update(float _delta)
{
	for (int i = 0; i < backgroundSize; i++)
	{
		baseBackgroundSprite[i]->Update(this,_delta);
	}
}
