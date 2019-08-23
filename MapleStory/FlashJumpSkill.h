#pragma once
#include "ISkill.h"

class FlashJumpSkill : public ISkill
{
public:
	FlashJumpSkill();
	~FlashJumpSkill();

	void Init();
	void Update(MCharacter* player, float _delta);

private:
	bool m_Used;
	int m_KeyDelay;
};