#include "pch.h"
#include "MCharacter.h"
#include "Mob.h"
#include "ObjectMgr.h"

//void AssetMgr::SetAssetData(IMG_DATA& _data)
//{
//	std::hash<std::string> hash_key;
//
//	m_mAssetData.insert(std::make_pair(hash_key(_data.filename), _data));
//}
//
//const IMG_DATA& AssetMgr::operator[](const std::string& _key)
//{
//	std::hash<std::string> hashkey;
//	LPIMG_DATA pImgData;
//
//	auto it = m_mAssetData.find(hashkey(_key));
//
//	if (it == m_mAssetData.end())
//		throw "error";
//	else
//		pImgData = &it->second;
//
//	return *pImgData;
//}
//
//LPIMG_DATA AssetMgr::GetAssetData(const std::string& _assetname)
//{
//	std::hash<std::string> hash_key;
//
//	LPIMG_DATA pImgData = nullptr;
//
//	auto it = m_mAssetData.find(hash_key(_assetname));
//
//	if (it == m_mAssetData.end())
//		return pImgData;
//	else
//		pImgData = &it->second;
//
//	return pImgData;
//}

ObjectMgr::ObjectMgr()
{
	m_mObject.clear();
}

ObjectMgr::~ObjectMgr()
{
}

void ObjectMgr::Update(float _delta)
{
	for (auto& it : m_mObject)
	{
		if (it.second->m_eObjType == EMObjType::eMO_Player)
		{
			MCharacter* pPlayer = static_cast<MCharacter*>(it.second);
			Gdiplus::Rect const* prc = &pPlayer->GetColRc();

			for (auto& t : m_mObject)
			{
				if (t.second->m_eObjType == EMObjType::eMO_Mob)
				{
					Mob* pMob = static_cast<Mob*>(t.second);
									   
					Gdiplus::Rect const* mrc = &pMob->GetColRc();

					if (AABBIntersectionSize(*prc, *mrc))
					{
						//player->hitdamage
						std::cout << "¸÷ÇÑÅ× ¸ÂÀ½ : " << mrc->X << "   " << mrc->Y<< std::endl;
						//continue;
					}
				}
				
				else if (t.second->m_eObjType == EMObjType::eMO_MSkill)
				{

				}

				else if (t.second->m_eObjType == EMObjType::eMO_LbRp)
				{

				}
			}
		}

		else if (it.second->m_eObjType == EMObjType::eMO_PSkill)
		{
			for (auto& t : m_mObject)
			{
				if (t.second->m_eObjType == EMObjType::eMO_Mob)
				{

				}
			}
		}

		//std::cout << "y : "<< it.second->GetPosition().Y <<  std::endl;

		it.second->Update(_delta);
	}
}

void ObjectMgr::SetObject(int _pryid, MObject* _obj)
{
	m_mObject.insert(std::make_pair(_pryid, _obj));
}

void ObjectMgr::Reset()
{
	MCharacter* pCh = nullptr;
	for (auto& it : m_mObject)
	{
		if (it.second->m_eObjType == EMObjType::eMO_Player)
			pCh = static_cast<MCharacter*>(it.second);

		else if (it.second->m_eObjType == EMObjType::eMO_Mob)
		{
			Mob* pMob = static_cast<Mob*>(it.second);
			
			pMob->Release();
		
			delete it.second;
		}
	}

	m_mObject.clear();

	m_mObject.insert(std::make_pair(pCh->m_ProxyID.GetProxyID(), pCh));
}
