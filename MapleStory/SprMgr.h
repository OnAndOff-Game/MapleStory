#pragma once

class SprMgr : public Singleton<SprMgr>
{
public:

	SprMgr();
	~SprMgr();

	void Release();

	void LoadData(const char* _filename);
	
	//SPRDATA& GetSpriteData(const char* _sprname, int _cnt);
	SPRDATA& GetSpriteData(int _sprid, int _cnt);


	int GetSpriteDataCnt(const char* _sprname);
	int GetSpriteDataCnt(int _sprid);
	
	void SetSpriteData(int _sprid, SPRDATA& _sprdata);
	
private:

	std::map<int, std::vector<SPRDATA>> m_mSprData;

	Node* node;
};

#define SPRMGR SprMgr::GetInstance()
