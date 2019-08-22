#include "pch.h"
#include "MSprite.h"
#include "MSpriteComponent.h"
#include "MPhysics.h"
#include "ISkill.h"
#include "MState.h"
#include "Mob.h"

Mob::Mob() : m_pPhysics(nullptr), m_pState(nullptr),
m_nSkillCnt(0), m_nAtkCnt(0), bFalling(true)
{
}

Mob::Mob(const std::string& _filename) : m_strName(_filename), m_pPhysics(nullptr),
m_pState(nullptr), m_nSkillCnt(0), m_nAtkCnt(0), bFalling(true)
{
	LoadData(_filename);
}

Mob::~Mob()
{
}

void Mob::Init()
{
	//LoadData(m_strName);
	m_pSprites->Init();

	m_pSprites->SetLooping(true);

	m_pPhysics = new MPhysics(m_MobInfo.fs, m_MobInfo.speed);

	m_pPhysics->Init();

}

void Mob::Release()
{
	if (m_pPhysics != nullptr)
	{
		m_pPhysics->Release();
		delete m_pPhysics;
		m_pPhysics = nullptr;
	}

	if (m_pSprites != nullptr)
	{
		m_pSprites->Release();
		delete m_pSprites;
		m_pSprites = nullptr;
	}

	for (auto it : m_vComponent)
	{
		it->Release();
		delete it;
	}

	m_vComponent.clear();
}

void Mob::Update(float _delta)
{
	m_pPhysics->SetImgData(m_pSprites->GetCurrentImgData());
	m_pPhysics->SetVelocityX(0);

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_pSprites->SetFlip(true);
		m_pPhysics->SetVelocityX(1);
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_pSprites->SetFlip(false);
		m_pPhysics->SetVelocityX(-1);
	}

	if (GetAsyncKeyState(VK_LCONTROL))
	{
		if (m_pPhysics->IsJump())
		{
			m_pPhysics->SetVelocityY(-1.5);
			m_pPhysics->SetJump(true);
		}
	}

	if (m_pState != nullptr)
	{
		m_pState->Update(*this);
	}


	for (auto it : m_vComponent)
	{
		it->Update(this, _delta);
	}

	m_pPhysics->Update(this, _delta);

	m_pSprites->Update(this, _delta);
}

void Mob::HandleInput(EMAnimType _atype)
{
	MState* state = m_pState->HandleInput(*this, _atype);
}

void Mob::SetComponent(Component* _pComp)
{
	if(_pComp != nullptr)
		m_vComponent.push_back(_pComp);
}

void Mob::Move()
{
	//spr->anim("move")
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Moving);
}

void Mob::Jump()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Jumping);
}

void Mob::Stand()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Standing);
}

void Mob::Dead()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Die);
}

void Mob::Skill(int _Cnt)
{
	if (m_nSkillCnt < _Cnt)
		return;

	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Skill, _Cnt);
}

void Mob::Attack(int _Cnt)
{
	if (m_nAtkCnt < _Cnt)
		return;

	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Skill, _Cnt);
}

void Mob::LoadData(const std::string& _filename)
{
	m_Paser = Node(_filename.c_str());
	
	std::string sprname = _filename; // ÀÌ¸§
	sprname.replace(sprname.find(".xml"), 4, "");

	int sprid = std::stoi(m_Paser.GetName());
	
	if(SPRMGR->GetSprDataCnt(sprid) == 0)
	for (auto o = m_Paser.begin(); o; o = o++) //anim name
	{
		if (!strcmp(o.GetName(), "info"))
		{
			LoadInfo(o);
		}
		
		else
		{
			SPRDATA sprdata;
			int nCnt = 0;

			sprdata.path = sprname;
			sprdata.name = o.GetName();
			//int a = sprdata.name.find("skill");
			//sprdata.name.compare("Attack");

			for (auto t = m_Paser[o.GetName()].begin(); t; t = t++) // num
			{
				std::string file;

				IMG_DATA imgdata;
							
				file = sprname + '/' + sprdata.name + '.' + t.GetName() + ".png";

				imgdata.filename = file;
				imgdata.id = atoi(t.GetName());
				imgdata.imgsize = t.GetValuePoint();

				//if(t.GetValuePoint() ==
				
				//t.GetValueInt();
			
				for (auto f = m_Paser[o.GetName()][t.GetName()].begin(); f; f = f++) // element
				{
					if (imgdata.imgsize.X * imgdata.imgsize.Y == 1)
					{
						std::string templink;
						if (!t["_inlink"].IsNull())
						{
							char from = '/';
							char to = '.';

							templink = t["_inlink"].GetValueString();
														
							std::replace(templink.begin(), templink.end(), from, to);

							imgdata.link = sprname + '/' + sprdata.name + '.' + templink + ".png";
						}

						//if (!t["_outlink"].IsNull())
						//	imgdata.origin = t["origin"].GetValuePoint();
					}

					if (!t["origin"].IsNull())
						imgdata.origin = t["origin"].GetValuePoint();
					else
					{
						imgdata.origin.X = imgdata.imgsize.X / 2;
						imgdata.origin.Y = imgdata.imgsize.Y / 2;
					}
					
					if (!t["lt"].IsNull())
						imgdata.lt = t["lt"].GetValuePoint();

					if (!t["rb"].IsNull())
						imgdata.rb = t["rb"].GetValuePoint();

					if (!t["head"].IsNull())
						imgdata.head = t["head"].GetValuePoint();

					if (!t["delay"].IsNull())
						imgdata.delay = t["delay"].GetValueInt();

					if (!t["a0"].IsNull())
						imgdata.a0 = t["a0"].GetValueInt();
					else
						imgdata.a0 = 0;

					if (!t["a1"].IsNull())
						imgdata.a1 = t["a1"].GetValueInt();
					else
						imgdata.a1 = 0;

					if (!t["z"].IsNull())
						imgdata.z = t["z"].GetValueInt();
					else
						imgdata.z = 2;
				}

				ASSETMGR->SetAssetData(imgdata);
				nCnt++;
			}

			sprdata.cnt = nCnt;

			if (!sprdata.name.find("move") || !sprdata.name.find("walk"))
			{
				sprdata.type = EMAnimType::eMA_Moving;
			}

			else if (!sprdata.name.find("stand"))
			{
				sprdata.type = EMAnimType::eMA_Standing;
			}

			else if (!sprdata.name.find("skill"))
			{
				sprdata.type = EMAnimType::eMA_Skill;
				m_nSkillCnt++;
			}

			else if (!sprdata.name.find("jump"))
			{
				sprdata.type = EMAnimType::eMA_Jumping;
			}

			else if (!sprdata.name.find("attack"))
			{
				sprdata.type = EMAnimType::eMA_Attack;
				m_nAtkCnt++;
			}

			else if (!sprdata.name.find("hit"))
			{
				sprdata.type = EMAnimType::eMA_Hit;
			}

			else if (!sprdata.name.find("die"))
			{
				sprdata.type = EMAnimType::eMA_Die;
			}

			else if (!sprdata.name.find("chase"))
			{
				sprdata.type = EMAnimType::eMA_Chase;
			}
			
			else
			{
				char* p = nullptr;
				p = "a";
			}

			SPRMGR->SetSprData(sprid, sprdata);
		}
	}

	m_pSprites = new MSpriteComponent(sprid, EMRenderType::eMR_Obj);
	
	//m_vComponent.push_back(pSC);
}

void Mob::LoadInfo(Node _node)
{
	m_MobInfo.level			= _node["level"].GetValueInt();
	m_MobInfo.bodyAttack	= _node["bodyAttack"].GetValueInt();
	m_MobInfo.maxHp			= _node["maxHP"].GetValueInt();
	m_MobInfo.maxMp			= _node["maxMP"].GetValueInt();
	m_MobInfo.speed			= _node["speed"].GetValueInt();
	m_MobInfo.PADamge		= _node["PADamage"].GetValueInt();
	m_MobInfo.PDDamge		= _node["PDDamage"].GetValueInt();
	m_MobInfo.PDRate		= _node["PDRate"].GetValueInt();
	m_MobInfo.MADamge		= _node["MADamage"].GetValueInt();
	m_MobInfo.MDDamge		= _node["MDDamage"].GetValueInt();
	m_MobInfo.MDRate		= _node["MDRate"].GetValueInt();
	m_MobInfo.acc			= _node["acc"].GetValueInt();
	m_MobInfo.eva			= _node["eva"].GetValueInt();
	m_MobInfo.pushed		= _node["pushed"].GetValueInt();
	m_MobInfo.fs			= _node["fs"].GetValueInt();
	m_MobInfo.exp			= _node["exp"].GetValueInt();
	m_MobInfo.category		= _node["category"].GetValueInt();
}
