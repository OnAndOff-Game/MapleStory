#include "pch.h"
#include "ProxyID.h"



class ProxyArray
{
	friend class ProxyID;

	std::queue<int>		  FreeProxy;
	std::vector<ProxyID*> Proxies;

	//	lock?

public:

	ProxyArray() : Max(0)
	{
		Proxies.resize(500);
	}


	~ProxyArray()
	{
		FreeProxy.size();
		Proxies.clear();
	}
	
	static ProxyArray& Get()
	{
		static ProxyArray Singleton;	
		return Singleton;
	}

	void Add(ProxyID* _proxy)
	{
		if (FreeProxy.size() != 0)
		{
			_proxy->ID = FreeProxy.back();
			Proxies[_proxy->ID] = _proxy;
		}

		else
		{
			_proxy->ID = Max;
			Proxies[_proxy->ID] = _proxy;
			Max++;
		}
	}

	void Remove(int _id)
	{
		Proxies[_id] = nullptr;
	
		if (_id != Max - 1)
			FreeProxy.push(_id);
		else
			Max--;
	}

	ProxyID* GetProxyID(int _index) 
	{
		if (_index >= 0 && _index < Proxies.max_size())
		{
			return Proxies[_index];
		}

		else
		{
			return nullptr;
		}
	}

	int		 GetProxyCount() { return Max - FreeProxy.size();}

	int Max;
};

ProxyID::ProxyID()
{
	InitProxy();
}

ProxyID::~ProxyID()
{
	ProxyArray::Get().Remove(ID);
}

int ProxyID::GetProxyID()
{
	return ID;
}

void ProxyID::InitProxy()
{
	ProxyArray::Get().Add(this);
}