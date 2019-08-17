#pragma once


//std::vector<

class ProxyID
{
	friend class ProxyArray;

public:

	ProxyID();
	~ProxyID();

	int GetProxyID();


private:

	void InitProxy();

	int ID;
};
