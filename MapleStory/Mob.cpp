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
	m_eObjType = EMObjType::eMO_Mob;
}

Mob::Mob(const std::string& _filename) : m_strName(_filename), m_pPhysics(nullptr),
m_pState(nullptr), m_nSkillCnt(0), m_nAtkCnt(0), bFalling(true)
{
	m_eObjType = EMObjType::eMO_Mob;
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
	m_MoveTime = 1000;
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

	m_MoveTime += _delta;
	if (m_MoveTime > 1000)
	{
		m_Direction = rand() % 3 - 1;
		m_MoveTime = 0;
	}
	m_pPhysics->SetVelocityX(m_Direction);
	if (m_Direction == 1)
		m_pSprites->SetFlip(true);
	else if (m_Direction == -1)
		m_pSprites->SetFlip(false);

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
	if (_pComp != nullptr)
		m_vComponent.push_back(_pComp);
}

int Mob::GetPushed()
{
	return m_MobInfo.pushed;
}

int Mob::GetPAtk()
{
	return m_MobInfo.PADamge;
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

Gdiplus::Rect const& Mob::GetColRc()
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	IMG_DATA const* imgdata = &m_pSprites->GetCurrentImgData();

	if (imgdata->lt.X == 0 && imgdata->lt.Y == 0)
	{
		if (imgdata->imgsize.X == imgdata->origin.X && imgdata->imgsize.Y == imgdata->origin.Y)
		{
			m_rcCollision.X = Transform.Translation.X;
			m_rcCollision.Y = Transform.Translation.Y;
			m_rcCollision.Width = imgdata->origin.X * 2;
			m_rcCollision.Height = imgdata->origin.Y * 2;
		}
	}

	else
	{
		m_rcCollision.X = Transform.Translation.X + imgdata->lt.X + imgdata->origin.X;
		m_rcCollision.Y = Transform.Translation.Y + imgdata->lt.Y + imgdata->origin.Y;
		m_rcCollision.Width = imgdata->rb.X + imgdata->origin.X;
		m_rcCollision.Height = imgdata->rb.Y + imgdata->origin.Y;
	}

	return m_rcCollision;
}

void Mob::LoadData(const std::string& _filename)
{
	m_Paser = Node(_filename.c_str());

	std::string sprname = _filename; // 이름
	sprname.replace(sprname.find(".xml"), 4, "");

	int sprid = std::stoi(m_Paser.GetName());

	if (SPRMGR->GetSprDataCnt(sprid) == 0)
	{
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
	}

	else
	{
		for (auto o = m_Paser.begin(); o; o = o++) //anim name
		{
			if (!strcmp(o.GetName(), "info"))
			{
				LoadInfo(o);
				break;
			}
		}
	}

	m_pSprites = new MSpriteComponent(sprid, EMRenderType::eMR_Obj);

	//m_vComponent.push_back(pSC);
}

void Mob::SetDirection(int dir)
{
	m_Direction = dir;
}

void Mob::LoadInfo(Node _node)
{
	m_MobInfo.level = _node["level"].GetValueInt();
	m_MobInfo.bodyAttack = _node["bodyAttack"].GetValueInt();
	m_MobInfo.maxHp = _node["maxHP"].GetValueInt();
	m_MobInfo.maxMp = _node["maxMP"].GetValueInt();
	m_MobInfo.speed = _node["speed"].GetValueInt();
	m_MobInfo.PADamge = _node["PADamage"].GetValueInt();
	m_MobInfo.PDDamge = _node["PDDamage"].GetValueInt();
	m_MobInfo.PDRate = _node["PDRate"].GetValueInt();
	m_MobInfo.MADamge = _node["MADamage"].GetValueInt();
	m_MobInfo.MDDamge = _node["MDDamage"].GetValueInt();
	m_MobInfo.MDRate = _node["MDRate"].GetValueInt();
	m_MobInfo.acc = _node["acc"].GetValueInt();
	m_MobInfo.eva = _node["eva"].GetValueInt();
	m_MobInfo.pushed = _node["pushed"].GetValueInt();
	m_MobInfo.fs = _node["fs"].GetValueInt();
	m_MobInfo.exp = _node["exp"].GetValueInt();
	m_MobInfo.category = _node["category"].GetValueInt();
}
