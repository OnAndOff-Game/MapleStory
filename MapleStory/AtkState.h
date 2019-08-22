#pragma once

class MState;
class MObject;

class AtkState : public MState
{
public:

	AtkState() {}
	~AtkState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};

