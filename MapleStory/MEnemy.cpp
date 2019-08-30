#include "pch.h"
#include <iostream>
#include "MEnemy.h"

MEnemy::MEnemy(const ENEMY& _lifedata)
{
	m_eObjType = EMObjType::eMObjType_Mob;
	enemyData = _lifedata;
	std::string filePath = "Mob/";
	filePath += enemyData.id + ".img.xml";
	std::cout << filePath << std::endl;
	LoadData(filePath);
}

void MEnemy::Init()
{
	Mob::Init();
	SetPosition(enemyData.x, enemyData.y);
}

void MEnemy::Update(float delta)
{
	Mob::Update(delta);
	if (GetPosition().X <= enemyData.movementLeft)
		SetDirection(DIRECTION_RIGHT);
	else if (GetPosition().X >= enemyData.movementRight)
		SetDirection(DIRECTION_LEFT);
}
