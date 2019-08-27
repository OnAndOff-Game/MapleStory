#include "pch.h"
#include "MovingState.h"
#include "HitState.h"
#include "DieState.h"
#include "LadderState.h"
#include "RopeState.h"
#include "StandingState.h"
#include "AtkState.h"
#include "JumpingState.h"
#include "MCharacter.h"
#include "ProneState.h"

MState* ProneState::HandleInput(MObject& _obj, EMAnimType _atype)
{
	if (EMAnimType::eMAnimType_Standing == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Stand();
		return new StandingState();
	}

	else if (EMAnimType::eMAnimType_Jumping == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Jump();
		return new JumpingState();
	}

	else if (EMAnimType::eMAnimType_Attack == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Attack();
		return new AtkState();
	}

	else if (EMAnimType::eMAnimType_Ladder == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Ladder();
		return new LadderState();
	}

	else if (EMAnimType::eMAnimType_Rope == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Rope();
		return new RopeState();
	}

	else if (EMAnimType::eMAnimType_Hit == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Hit();
		return new HitState();
	}

	else if (EMAnimType::eMAnimType_Die == _atype)
	{
		static_cast<MCharacter*>(&_obj)->Die();
		return new DieState();
	}
	
	else
	{
		return nullptr;
	}
}

void ProneState::Update(MObject& _obj)
{
}
