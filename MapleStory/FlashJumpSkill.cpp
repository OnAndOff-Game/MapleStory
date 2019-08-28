#include "pch.h"
#include "MPhysics.h"
#include "MCharacter.h"
#include "FlashJumpSkill.h"


FlashJumpSkill::FlashJumpSkill()
{
}


FlashJumpSkill::~FlashJumpSkill()
{
}

void FlashJumpSkill::Init()
{
	m_Used = false;
	m_KeyDelay = 0;
}

void FlashJumpSkill::Update(MCharacter* player, float _delta)
{
	if (!player->IsJump() && !m_Used)
	{
		m_KeyDelay += _delta;

		if (m_KeyDelay > 50)
		{
			if (GetAsyncKeyState(VK_LCONTROL))
			{
				player->physics->SetVelocityX(player->physics->GetVelocityX() * 4);
				player->physics->SetVelocityY(-1.5);
				SoundManager->PlaySound(3);
				m_Used = true;
			}
		}
	}
	else if (player->IsJump())
	{
		m_Used = false;
		m_KeyDelay = 0;
	}
}
