#include "pch.h"
#include "MCharacter.h"

void MCharacter::Init()
{
	playerState = EMAnimType::eMA_Standing;
	animState[eMA_Standing] = new MSprite({ EMAnimType::eMA_Standing, "Character/default/0","","alert_",4 }, EMRenderType::eMR_Map);
	animState[eMA_Standing]->Init();
	this->SetPosition(0, 0);
}

void MCharacter::Update(float _delta)
{
	animState[playerState]->Update(this, _delta);
}

void MCharacter::LoadData(const std::string& _filename)
{
}
