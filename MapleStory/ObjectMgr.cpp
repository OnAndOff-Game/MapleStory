#include "pch.h"
#include "MCharacter.h"
#include "Mob.h"
#include "ObjectMgr.h"

bool AABBIntersectionSize(Gdiplus::Rect const& _a_rc, Gdiplus::Rect const& _b_rc)
{

	bool check = (_a_rc.X + _a_rc.Width < _b_rc.X) || (_b_rc.X + _b_rc.Width < _a_rc.X) ||
		(_a_rc.Y + _a_rc.Height < _b_rc.Y) || (_b_rc.Y + _b_rc.Height < _a_rc.Y);
	
		//if (_a_rc.X + _a_rc.Width < _b_rc.X || _a_rc.X > _b_rc.X + _b_rc.Width)
	//	return 0;

	//if (_a_rc.Y + _a_rc.Height < _b_rc.Y || _a_rc.Y > _b_rc.Y + _b_rc.Height)
	//	return 0;

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
		if (it.second->m_eObjType == EMObjType::eMO_Player)
		{
			MCharacter* pPlayer = static_cast<MCharacter*>(it.second);
		
			if (!pPlayer->IsCollision())
			{
				it.second->Update(_delta);
				continue;
			}
		
			Gdiplus::Rect const* prc = &pPlayer->GetColRc();

			for (auto& t : m_mObject)
			{
				if (t.second->m_eObjType == EMObjType::eMO_Mob)
				{
					Mob* pMob = static_cast<Mob*>(t.second);
									   
					Gdiplus::Rect const* mrc = &pMob->GetColRc();

					if (AABBIntersectionSize(*prc, *mrc) == true)
					{
						std::cout << pPlayer->GetPosition().X << "   " << pPlayer->GetPosition().Y << std::endl;

						pPlayer->HitDamage(pMob->GetPushed());

						break;	
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

	if (pCh != nullptr)
		m_mObject.insert(std::make_pair(pCh->m_ProxyID.GetProxyID(), pCh));
}
