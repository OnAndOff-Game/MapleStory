#pragma once

class MState;
class MObject;

class RopeState : public MState
{
public:

	RopeState() {}
	~RopeState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};

