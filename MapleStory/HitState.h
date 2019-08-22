#pragma once

class MState;
class MObject;

class HitState : public MState
{
public:

	HitState() {}
	~HitState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};
