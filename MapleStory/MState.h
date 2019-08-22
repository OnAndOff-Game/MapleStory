#pragma once

class MObject;

class MState
{
public:

	virtual ~MState() {}
	virtual MState* HandleInput(MObject& _obj, EMAnimType _atype) = 0;
	virtual void Update(MObject& _obj) = 0;
};

