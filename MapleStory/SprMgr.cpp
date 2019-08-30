#include "pch.h"
#include "SprMgr.h"

SprMgr::SprMgr()
{
	node = nullptr;
}

SprMgr::~SprMgr()
{
}

void SprMgr::Release()
{
	for (auto &it : m_mSprData)
	{
		it.second.clear();
	}

	m_mSprData.clear();

	if (node != nullptr)
	{
		node->Release();
		delete node;
		node = nullptr;
	}
}

//SPRDATA& SprMgr::GetSpriteData(const char* _sprname, int _cnt)
//{
//	return m_mSprData[std::stoi(_sprname)][_cnt];
//}

SPRDATA& SprMgr::GetSpriteData(int _sprid, int _cnt)
{
	return m_mSprData[_sprid][_cnt];
}

int SprMgr::GetSpriteDataCnt(const char* _sprname)
{
	return m_mSprData[std::stoi(_sprname)].size();
}

int SprMgr::GetSpriteDataCnt(int _sprid)
{
	return m_mSprData[_sprid].size();
}

void SprMgr::SetSpriteData(int _sprid, SPRDATA& _sprdata)
{
	m_mSprData[_sprid].push_back(_sprdata);
}
