#include "pch.h"
#include "MCharacter.h"
#include "Mob.h"
#include "ObjectMgr.h"

bool AABBIntersectionSize(Gdiplus::Rect const& _a_rc, Gdiplus::Rect const& _b_rc)
{

	bool check = (_a_rc.X + _a_rc.Width < _b_rc.X) || (_b_rc.X + _b_rc.Width < _a_rc.X) ||
		(_a_rc.Y + _a_rc.Height < _b_rc.Y) || (_b_rc.Y + _b_rc.Height < _a_rc.Y);
	
	return !check;
}

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
		if (it.second->m_eObjType == EMObjType::eMObjType_Player)
		{
			MCharacter* pPlayer = static_cast<MCharacter*>(it.second);
		
			if (!pPlayer->IsCollision())
			{
				it.second->Update(_delta);
				continue;
			}
		
			Gdiplus::Rect const& PlayerCollisionRect = pPlayer->GetCollisionRect();

			for (auto& t : m_mObject)
			{
				if (t.second->m_eObjType == EMObjType::eMObjType_Mob)
				{
					Mob* pMob = static_cast<Mob*>(t.second);
									   
					Gdiplus::Rect const* mrc = &pMob->GetColRc();

					if (AABBIntersectionSize(PlayerCollisionRect, *mrc) == true)
					{
						pPlayer->HitDamage(pMob->GetPushed());

						break;	
					}
				}
				
				else if (t.second->m_eObjType == EMObjType::eMObjType_MobSkill)
				{

				}

				else if (t.second->m_eObjType == EMObjType::eMObjType_LadderRope)
				{

				}
			}
		}

		else if (it.second->m_eObjType == EMObjType::eMObjType_PlayerSkill)
		{
			Mob* mob = nullptr;

			for (auto& t : m_mObject)
			{
				if (t.second->m_eObjType == EMObjType::eMObjType_Mob)
				{
					
				}
			}
		}
		
		it.second->Update(_delta);
	}
}

void ObjectMgr::Release()
{
	m_mObject.clear();
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
		if (it.second->m_eObjType == EMObjType::eMObjType_Player)
			pCh = static_cast<MCharacter*>(it.second);

	/*else if (it.second->m_eObjType == EMObjType::eMObjType_Mob)
		{
			Mob* pMob = static_cast<Mob*>(it.second);
			
			pMob->Release();
		
			delete it.second;
		}*/
	}

	m_mObject.clear();

	if (pCh != nullptr)
		m_mObject.insert(std::make_pair(pCh->objectId.GetObjectId(), pCh));
}
