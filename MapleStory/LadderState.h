#pragma once


class MState;
class MObject;

class LadderState : public MState
{
public:

	LadderState() {}
	~LadderState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};
