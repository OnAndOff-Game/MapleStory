#pragma once

class MState;
class MObject;

class JumpingState : public MState
{
public:
	~JumpingState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);

};

