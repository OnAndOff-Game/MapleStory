#pragma once
#include "Mob.h"


struct ENEMY
{
	std::string type;
	std::string id;
	int x;
	int y;
	int mobTime;
	int f;
	int hide;
	int roadLine;
	int cy;
	int movementLeft;
	int movementRight;
};

class MEnemy : public Mob
{
public:
	MEnemy(const ENEMY& _lifedata);

	void Init();
	void Update(float delta);

	ENEMY enemyData;
};