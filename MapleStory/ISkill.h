#pragma once
#include "Mob.h"

class ISkill : public MObject
{
public:
	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	virtual void Update(MCharacter* player,float _delta);

private:

};