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
	m_eObjType = EMObjType::eMObjType_Mob;
}

Mob::Mob(const std::string& _filename) : m_strName(_filename), m_pPhysics(nullptr),
m_pState(nullptr), m_nSkillCnt(0), m_nAtkCnt(0), bFalling(true)
{
	m_eObjType = EMObjType::eMObjType_Mob;
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

	m_pPhysics = new MPhysics(0, 120);

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
	return 0;//m_MobInfo.pushed;
}

int Mob::GetPAtk()
{
	return 0;//m_MobInfo.PADamge;
}

void Mob::Move()
{
	//spr->anim("move")
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Moving);
}

void Mob::Jump()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Jumping);
}

void Mob::Stand()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Standing);
}

void Mob::Dead()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Die);
}

void Mob::Skill(int _Cnt)
{
	if (m_nSkillCnt < _Cnt)
		return;

	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Skill, _Cnt);
}

void Mob::Attack(int _Cnt)
{
	if (m_nAtkCnt < _Cnt)
		return;

	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Skill, _Cnt);
}

Gdiplus::Rect const& Mob::GetColRc()
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	IMG_DATA const* imgdata = &m_pSprites->GetCurrentImgData();

	if (imgdata->leftTop.X == 0 && imgdata->leftTop.Y == 0)
	{
		if (imgdata->imgsize.X == imgdata->origin.X && imgdata->imgsize.Y == imgdata->origin.Y)
		{
			m_rcCollision.X = Transform.Translation.X;
			m_rcCollision.Y = Transform.Translation.Y;
			m_rcCollision.Width = imgdata->origin.X * 2;
			m_rcCollision.Height = imgdata->origin.Y * 2;
		}

		else
		{
			std::cout << "있다";
		}
	}

	else
	{
		m_rcCollision.X = Transform.Translation.X + imgdata->leftTop.X;
		m_rcCollision.Y = Transform.Translation.Y + imgdata->leftTop.Y;
		m_rcCollision.Width = imgdata->rightBottom.X + imgdata->origin.X;
		m_rcCollision.Height = imgdata->rightBottom.Y + imgdata->origin.Y;
	}

	return m_rcCollision;
}

void Mob::LoadData(const std::string& _filename)
{
	m_Paser = Node(_filename.c_str());

	std::string sprname = _filename; // 이름
	sprname.replace(sprname.find(".xml"), 4, "");

	int sprid = std::stoi(m_Paser.GetName());

	if (SPRMGR->GetSpriteDataCnt(sprid) == 0)
	{
		for (auto anim = m_Paser.begin(); anim; anim = anim++) //anim name
		{
			if (!strcmp(anim.GetName(), "info"))
			{
				//m_MobInfo = LoadInfo(anim);
			}

			else
			{
				SPRDATA sprdata;
				int nCnt = 0;

				sprdata.path = sprname;
				sprdata.name = anim.GetName();


				for (auto num = m_Paser[anim.GetName()].begin(); num; num = num++) // num
				{
					std::string file;

					IMG_DATA imgdata;

					file = sprname + '/' + sprdata.name + '.' + num.GetName() + ".png";

					imgdata.filename = file;
					imgdata.id = atoi(num.GetName());
					imgdata.imgsize = num.GetValuePoint();
										
					if (imgdata.imgsize.X * imgdata.imgsize.Y == 1)
					{
						std::string templink;
						if (!num["_inlink"].IsNull())
						{
							char from = '/';
							char to = '.';

							templink = num["_inlink"].GetValueString();

							std::replace(templink.begin(), templink.end(), from, to);

							imgdata.link = sprname + '/' + sprdata.name + '.' + templink + ".png";
						}						
						//if (!t["_outlink"].IsNull())
						//	imgdata.origin = t["origin"].GetValuePoint();
					}

					if (!num["origin"].IsNull())
						imgdata.origin = num["origin"].GetValuePoint();
					else
					{
						imgdata.origin.X = imgdata.imgsize.X / 2;
						imgdata.origin.Y = imgdata.imgsize.Y / 2;
					}

					if (!num["lt"].IsNull())
						imgdata.leftTop = num["lt"].GetValuePoint();

					if (!num["rb"].IsNull())
						imgdata.rightBottom = num["rb"].GetValuePoint();

					if (!num["head"].IsNull())
						imgdata.head = num["head"].GetValuePoint();

					if (!num["delay"].IsNull())
						imgdata.delay = num["delay"].GetValueInt();

					if (!num["a0"].IsNull())
						imgdata.beginAlpha = num["a0"].GetValueInt();
					else
						imgdata.beginAlpha = 0;

					if (!num["a1"].IsNull())
						imgdata.endAlpha = num["a1"].GetValueInt();
					else
						imgdata.endAlpha = 0;

					if (!num["z"].IsNull())
						imgdata.z = num["z"].GetValueInt();
					else
						imgdata.z = 2;


					ASSETMGR->SetAssetData(imgdata);
					nCnt++;
				}

				sprdata.cnt = nCnt;

				if (!sprdata.name.find("move") || !sprdata.name.find("walk"))
				{
					sprdata.type = EMAnimType::eMAnimType_Moving;
				}

				else if (!sprdata.name.find("stand"))
				{
					sprdata.type = EMAnimType::eMAnimType_Standing;
				}

				else if (!sprdata.name.find("skill"))
				{
					sprdata.type = EMAnimType::eMAnimType_Skill;
					m_nSkillCnt++;
				}

				else if (!sprdata.name.find("jump"))
				{
					sprdata.type = EMAnimType::eMAnimType_Jumping;
				}

				else if (!sprdata.name.find("attack"))
				{
					sprdata.type = EMAnimType::eMAnimType_Attack;
					m_nAtkCnt++;
				}

				else if (!sprdata.name.find("hit"))
				{
					sprdata.type = EMAnimType::eMAnimType_Hit;
				}

				else if (!sprdata.name.find("die"))
				{
					sprdata.type = EMAnimType::eMAnimType_Die;
				}

				else if (!sprdata.name.find("chase"))
				{
					sprdata.type = EMAnimType::eMAnimType_Chase;
				}

				else
				{
					char* p = nullptr;
					p = "a";
				}

				SPRMGR->SetSpriteData(sprid, sprdata);
			}
		}
	}

	else
	{
		for (auto o = m_Paser.begin(); o; o = o++) //anim name
		{
			if (!strcmp(o.GetName(), "info"))
			{
				//m_MobInfo = LoadInfo(o);
				break;
			}
		}
	}

	m_pSprites = new MSpriteComponent(sprid, EMRenderType::eMRenderType_Object);

	//m_vComponent.push_back(pSC);
}

void Mob::SetDirection(int dir)
{
	m_Direction = dir;
}