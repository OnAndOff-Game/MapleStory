#pragma once


class MObject;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:

	ObjectMgr();
	~ObjectMgr();

	void Update(float _delta);
	void Release();
	
	void SetObject(int _pryid, MObject* _obj);

	void Reset();

	//LPIMG_DATA GetAssetData(const std::string& _assetname)

private:
	
	std::map<int, MObject*> m_mObject;

};

#define OBJMGR ObjectMgr::GetInstance()
