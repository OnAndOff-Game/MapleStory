#pragma once
#include "Mob.h"


struct LIFE
{
	std::string type;
	std::string id;
	int x;
	int y;
	int mobTime;
	int f;
	int hide;
	int fh;
	int cy;
	int rx0;
	int rx1;
};

class MLife : public Mob
{
public:
	MLife(const LIFE& _lifedata);

	void Init();
	void Update(float delta);

	LIFE lifeData;
};