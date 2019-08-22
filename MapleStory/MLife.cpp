#include "pch.h"
#include <iostream>
#include "MLife.h"

MLife::MLife(const LIFE& _lifedata)
{
	lifeData = _lifedata;
	std::string filePath = "Mob/";
	filePath += lifeData.id + ".img.xml";
	std::cout << filePath << std::endl;
	LoadData(filePath);
}

void MLife::Init()
{
	Mob::Init();
	SetPosition(lifeData.x, lifeData.y);
}

void MLife::Update(float delta)
{
	Mob::Update(delta);
	if (GetPosition().X <= lifeData.rx0)
		SetDirection(1);
	else if (GetPosition().X >= lifeData.rx1)
		SetDirection(-1);
}
