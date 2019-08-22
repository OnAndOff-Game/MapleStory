#pragma once

class MState;
class MObject;

class MovingState : public MState
{
public:
	MovingState() {}
	~MovingState() {}

	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};

