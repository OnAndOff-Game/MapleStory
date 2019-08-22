#include "pch.h"
#include "JumpingState.h"
#include "AtkState.h"
#include "ProneState.h"
#include "HitState.h"
#include "DieState.h"
#include "LadderState.h"
#include "RopeState.h"
#include "StandingState.h"
#include "MCharacter.h"
#include "MovingState.h"

MState* MovingState::HandleInput(MObject& _obj, EMAnimType _atype)
{
	if (EMAnimType::eMA_Standing == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Stand();
		return new StandingState();
	}

	else if (EMAnimType::eMA_Attack == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Attack();
		return new AtkState();
	}

	else if (EMAnimType::eMA_Jumping == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Jump();
		return new JumpingState();
	}
	
	else if (EMAnimType::eMA_Ladder == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Ladder();
		return new LadderState();
	}

	else if (EMAnimType::eMA_Rope == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Rope();
		return new RopeState();
	}

	else if (EMAnimType::eMA_Hit == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Hit();
		return new HitState();
	}

	else if (EMAnimType::eMA_Die == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Die();
		return new DieState();
	}

	else
	{

		return nullptr;
	}
}

void MovingState::Update(MObject& _obj)
{
}
