#pragma once

class SprMgr : public Singleton<SprMgr>
{
public:

	SprMgr();
	~SprMgr();

	void LoadData(const char* _filename);
	
	//SPRDATA& GetSprData(const char* _sprname, int _cnt);
	SPRDATA& GetSprData(int _sprid, int _cnt);


	int GetSprDataCnt(const char* _sprname);
	int GetSprDataCnt(int _sprid);
	
	void SetSprData(int _sprid, SPRDATA& _sprdata);
	
private:

	std::map<int, std::vector<SPRDATA>> m_mSprData;

	Node* node;
};

#define SPRMGR SprMgr::GetInstance()
