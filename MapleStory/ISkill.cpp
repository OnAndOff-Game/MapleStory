#include "pch.h"
#include "MObject.h"
#include "ISkill.h"

void ISkill::Init()
{
	this->player = player;
}

void ISkill::LoadData(const std::string& _filename)
{
}

void ISkill::Update(MCharacter* player, float _delta)
{
}
