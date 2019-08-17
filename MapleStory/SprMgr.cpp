#include "pch.h"
#include "SprMgr.h"

SprMgr::SprMgr()
{
	node = nullptr;
}

SprMgr::~SprMgr()
{
	if (node != nullptr)
	{
		delete node;
		node = nullptr;
	}
}

SPRDATA& SprMgr::GetSprData(const char* _sprname, int _cnt)
{
	return m_mSprData[std::stoi(_sprname)][_cnt];
}

SPRDATA& SprMgr::GetSprData(int _sprid, int _cnt)
{
	return m_mSprData[_sprid][_cnt];
}

int SprMgr::GetSprDataCnt(const char* _sprname)
{
	return m_mSprData[std::stoi(_sprname)].size();
}
int SprMgr::GetSprDataCnt(int _sprid)
{
	return m_mSprData[_sprid].size();
}

void SprMgr::SetSprData(SPRDATA& _sprdata)
{
	m_mSprData[std::stoi(_sprdata.sprname)].push_back(_sprdata);
}
