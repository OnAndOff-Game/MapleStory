#include "pch.h"
#include "MovingState.h"
#include "AtkState.h"
#include "ProneState.h"
#include "DieState.h"
#include "StandingState.h"
#include "MCharacter.h"
#include "HitState.h"

MState* HitState::HandleInput(MObject& _obj, EMAnimType _atype)
{
	return nullptr;
}

void HitState::Update(MObject& _obj)
{
}
