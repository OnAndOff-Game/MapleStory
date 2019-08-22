#pragma once


class MState;
class MObject;

class DieState : public MState
{
public:
	DieState() {}
	~DieState() {}

	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};

