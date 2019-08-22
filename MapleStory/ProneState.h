#pragma once
 
class MState;
class MObject;

class ProneState : public MState
{
public:

	ProneState() {}
	~ProneState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype);
	virtual void Update(MObject& _obj);
};

