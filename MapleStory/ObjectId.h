#pragma once

class ObjectId
{
	friend class ObjectIdArray;

public:

	ObjectId();
	~ObjectId();

	int GetObjectId();


private:

	void InitObjectId();

	int id;
};
