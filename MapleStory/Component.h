#pragma once

class MObject;

class Component
{
public:

	virtual void Init() = 0;
	virtual void Update(MObject* _obj, float _delta) = 0;
	virtual void Release() = 0;
};

