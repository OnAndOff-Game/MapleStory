#include "pch.h"
#include "MSprite.h"
#include "MSpriteComponent.h"
#include "MPhysics.h"
#include "FlashJumpSkill.h"
#include "ISkill.h"
#include "StandingState.h"
#include "MDamageFont.h"
#include "MCharacter.h"

MCharacter::MCharacter() :physics(nullptr), skillCnt(0), attackCnt(0),
bFalling(true), m_bCollision(true), m_bHit(false), bFlag(false)
{
	m_eObjType = EMObjType::eMObjType_Player;
}

MCharacter::MCharacter(const std::string& _filename) : m_strName(_filename), physics(nullptr),
skillCnt(0), attackCnt(0), bFalling(true), m_bCollision(true), m_bHit(false)
{
	m_eObjType = EMObjType::eMObjType_Player;
	LoadData(_filename);
}

MCharacter::~MCharacter()
{
}

void MCharacter::Init()
{
	m_pSprites->Init();

	m_pSprites->SetLooping(true);

	physics = new MPhysics;
	physics->Init();

	m_pState = new StandingState();

	m_nHp = m_nMaxHp= 2500;
	m_nMp = m_nMaxMp =3000;

	//skills.push_back(new FlashJumpSkill());
	m_pDF = new MDamageFont();
}

void MCharacter::Release()
{
	if (m_pState != nullptr)
	{
		delete m_pState;
	}

	if (m_pDF != nullptr)
	{
		m_pDF->Release();
		delete m_pDF;
	}

	if (physics != nullptr)
	{
		physics->Release();
		delete physics;
		physics = nullptr;
	}

	if (m_pSprites != nullptr)
	{
		m_pSprites->Release();
		delete m_pSprites;
		m_pSprites = nullptr;
	}

	for (auto it : component)
	{
		it->Release();
		delete it;
	}

	component.clear();
}

void MCharacter::Update(float _delta)
{
	physics->SetImgData(m_pSprites->GetCurrentImgData());

	if (physics->IsJumping())
		physics->SetVelocityX(Lerp(physics->GetVelocityX(), 0, _delta * 0.01));

	if (GetAsyncKeyState(VK_LCONTROL))
	{
		if (physics->IsJumping())
		{
			HandleInput(EMAnimType::eMAnimType_Jumping);
			physics->SetVelocityY(-1.2);
			physics->SetJumping(true);
			SoundManager->PlaySound(SoundType::Sound_Jump);
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		HandleInput(EMAnimType::eMAnimType_Prone);
		m_pSprites->SetFlip(false);
		if (physics->IsFloor())
		{
			if (KEY_DOWN(VK_LCONTROL))
			{
				physics->SetVelocityY(1);
			}
		}
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		if (physics->IsJumping())
		{
			HandleInput(EMAnimType::eMAnimType_Moving);
			physics->SetVelocityX(1);
		}
		m_pSprites->SetFlip(true);
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (physics->IsJumping())
		{
			HandleInput(EMAnimType::eMAnimType_Moving);
			physics->SetVelocityX(-1);
		}
		m_pSprites->SetFlip(false);
	}
	else if (GetAsyncKeyState('W'))
	{
		Skill();
		//HandleInput(EMAnimType::eMAnimType_Skill);
	}
	else
	{
		HandleInput(EMAnimType::eMAnimType_Standing);
	}

	for (auto it : component)
	{
		it->Update(this, _delta);
	}

	/*for (auto s : skills)
	{
		s->Update(this, _delta);
	}
*/
	m_dwHitTick += _delta;

	if (m_bCollision == false)
	{
		int temp = m_dwHitTick / 100;

		if (temp % 2 == 0)
		{
			m_pSprites->SetRed(10.0f);
		}
		else
		{
			m_pSprites->SetRed(1.0f);
		}
	}
	else
	{
		m_pSprites->SetRed(1.0f);
	}

	if (m_dwHitTick > 2000)
	{
		m_bCollision = true;
		m_bHit = false;
		m_dwHitTick = 0;
	}

	physics->Update(this, _delta);
	m_pSprites->Update(this, _delta);
	m_pDF->Update(_delta);
}

void MCharacter::GetLadderRope(std::list<Maple::LADDER_ROPE>& _ladderrope)
{
	m_pLdRope = &_ladderrope;
}

Gdiplus::Rect const& MCharacter::GetCollisionRect()
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	IMG_DATA const* imgdata = &m_pSprites->GetCurrentImgData();

	if (imgdata->leftTop.X == 0 && imgdata->leftTop.Y == 0)
	{
		if (imgdata->imgsize.X == imgdata->origin.X && imgdata->imgsize.Y == imgdata->origin.Y)
		{
			collisionRect.X = Transform.Translation.X;
			collisionRect.Y = Transform.Translation.Y;
			collisionRect.Width = imgdata->origin.X * 2;
			collisionRect.Height = imgdata->origin.Y * 2;
		}
	}
	else
	{
		collisionRect.X = Transform.Translation.X + imgdata->leftTop.X;
		collisionRect.Y = Transform.Translation.Y + imgdata->leftTop.Y;
		collisionRect.Width = imgdata->rightBottom.X + imgdata->origin.X;
		collisionRect.Height = imgdata->rightBottom.Y + imgdata->origin.Y;
	}

	return collisionRect;
}

void MCharacter::HitDamage(int _damage)
{
	m_bHit = true;
	m_bCollision = false;
	m_dwHitTick = 0;

	IMG_DATA const& localImgData = m_pSprites->GetCurrentImgData();
	//damage font(_demage)
	Gdiplus::Point pt = GetPosition();

	pt.X -= localImgData.imgsize.X / 2;
	pt.Y -= localImgData.imgsize.Y + 20;

	m_pDF->SetDamage(_damage, pt);

	m_nHp -= _damage;
}

void MCharacter::SetLevitation()
{
	physics->SetLevitation();
}

bool MCharacter::IsCollision()
{
	return m_bCollision;
}

void MCharacter::HandleInput(EMAnimType _atype)
{
	MState* pState = m_pState->HandleInput(*this, _atype);

	if (pState != nullptr)
	{
		delete m_pState;
		m_pState = pState;
	}
}

void MCharacter::SetComponent(Component* _pComp)
{
	if (_pComp != nullptr)
		component.push_back(_pComp);
}

void MCharacter::Revision()
{
	physics->SetJumping(true);
}

bool MCharacter::IsJump()
{
	return physics->IsJumping();
}

void MCharacter::Move()
{
	//spr->anim("move")
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Moving);
	m_pSprites->SetLooping(true);
}

void MCharacter::Jump()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Jumping);
}

bool MCharacter::Stand()
{
	if (physics->IsJumping())
	{
		m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Standing);
		m_pSprites->SetLooping(true);
		return true;
	}
	else
		return false;
}

void MCharacter::Hit()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Hit);
}

void MCharacter::Die()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Die);
}

void MCharacter::Skill()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Skill);
}

void MCharacter::Attack()
{
}

void MCharacter::Prone()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Prone);
}

void MCharacter::Ladder()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Ladder);
}

void MCharacter::Rope()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMAnimType_Rope);
}

void MCharacter::LoadData(const std::string& _filename)
{
	m_Paser = new Node(_filename.c_str());

	std::string sprname = _filename; // 이름
	sprname.replace(sprname.find(".xml"), 4, "");

	int sprid = std::stoi(m_Paser->GetName());

	if (SPRMGR->GetSpriteDataCnt(sprid) == 0)
	{
		for (auto o = m_Paser->begin(); o; o = o++) //anim name
		{
			if (strcmp(o.GetName(), "info"))
			{
				SPRDATA sprdata;
				int nCnt = 0;

				sprdata.path = sprname;
				sprdata.name = o.GetName();
				//int a = sprdata.name.find("skill");
				//sprdata.name.compare("Attack");
				int n = 0;
				for (auto t = m_Paser[0][o.GetName()].begin(); t; t = t++) // num
				{
					n++;
					o.GetName();
					std::string file;

					IMG_DATA imgdata;

					file = sprname + '/' + sprdata.name + '.' + t.GetName() + ".png";

					imgdata.filename = file;
					imgdata.id = atoi(t.GetName());
					imgdata.imgsize = t.GetValuePoint();

					//if(t.GetValuePoint() ==

					//t.GetValueInt();
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
					}

					if (!t["origin"].IsNull())
						imgdata.origin = t["origin"].GetValuePoint();
					else
					{
						imgdata.origin.X = imgdata.imgsize.X / 2;
						imgdata.origin.Y = imgdata.imgsize.Y;
					}

					if (!t["lt"].IsNull())
						imgdata.leftTop = t["lt"].GetValuePoint();

					if (!t["rb"].IsNull())
						imgdata.rightBottom = t["rb"].GetValuePoint();

					if (!t["head"].IsNull())
						imgdata.head = t["head"].GetValuePoint();

					if (!t["delay"].IsNull())
						imgdata.delay = t["delay"].GetValueInt();

					if (!t["a0"].IsNull())
						imgdata.beginAlpha = t["a0"].GetValueInt();
					else
						imgdata.beginAlpha = 0;

					if (!t["a1"].IsNull())
						imgdata.endAlpha = t["a1"].GetValueInt();
					else
						imgdata.endAlpha = 0;

					if (!t["z"].IsNull())
						imgdata.z = t["z"].GetValueInt();
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
					skillCnt++;
				}

				else if (!sprdata.name.find("jump"))
				{
					sprdata.type = EMAnimType::eMAnimType_Jumping;
				}

				else if (!sprdata.name.find("attack"))
				{
					sprdata.type = EMAnimType::eMAnimType_Attack;
					attackCnt++;
				}

				else if (!sprdata.name.find("prone"))
				{
					sprdata.type = EMAnimType::eMAnimType_Prone;
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

		m_pSprites = new MSpriteComponent(sprid, EMRenderType::eMRenderType_Object);
	}

	m_Paser->Release();
	delete m_Paser;
	//m_vComponent.push_back(pSC);
}
