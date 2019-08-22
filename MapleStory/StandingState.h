#pragma once

class MState;
class MObject;

class StandingState : public MState
{
public:

	StandingState() {}
	~StandingState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};

