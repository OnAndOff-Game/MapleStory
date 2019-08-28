#include "pch.h"
#include "ObjectId.h"



class ObjectIdArray
{
	friend class ObjectId;

	std::queue<int>		  FreeObjectId;
	std::vector<ObjectId*> Objects;

	//	lock?

public:

	ObjectIdArray() : Max(0)
	{
		Objects.resize(500);
	}


	~ObjectIdArray()
	{
		FreeObjectId.size();
		Objects.clear();
	}
	
	static ObjectIdArray& Get()
	{
		static ObjectIdArray Singleton;	
		return Singleton;
	}

	void Add(ObjectId* _ObjectId)
	{
		if (FreeObjectId.size() != 0)
		{
			_ObjectId->id = FreeObjectId.back();
			Objects[_ObjectId->id] = _ObjectId;
		}

		else
		{
			_ObjectId->id = Max;
			Objects[_ObjectId->id] = _ObjectId;
			Max++;
		}
	}

	void Remove(int _id)
	{
		Objects[_id] = nullptr;
	
		if (_id != Max - 1)
			FreeObjectId.push(_id);
		else
			Max--;
	}

	ObjectId* GetObjectIdID(int _index) 
	{
		if (_index >= 0 && _index < Objects.max_size())
		{
			return Objects[_index];
		}

		else
		{
			return nullptr;
		}
	}

	int		 GetObjectIdCount() { return Max - FreeObjectId.size();}

	int Max;
};

ObjectId::ObjectId()
{
	InitObjectId();
}

ObjectId::~ObjectId()
{
	ObjectIdArray::Get().Remove(id);
}

int ObjectId::GetObjectId()
{
	return id;
}

void ObjectId::InitObjectId()
{
	ObjectIdArray::Get().Add(this);
}