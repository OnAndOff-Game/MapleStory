#pragma once

class MObject;

class Component
{
public:

	virtual void Init() = 0;
	virtual void Update(MObject* _obj, float _elapsedTime) = 0;
};

