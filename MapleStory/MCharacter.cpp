#include "pch.h"
#include "MSprite.h"
#include "MSpriteComponent.h"
#include "MPhysics.h"
#include "ISkill.h"
#include "StandingState.h"
#include "MCharacter.h"

MCharacter::MCharacter() :m_pPhysics(nullptr),
m_nSkillCnt(0), m_nAtkCnt(0), bFalling(true)
{
}

MCharacter::MCharacter(const std::string& _filename) : m_strName(_filename), m_pPhysics(nullptr),
m_nSkillCnt(0), m_nAtkCnt(0), bFalling(true)
{
	LoadData(_filename);
}

MCharacter::~MCharacter()
{
}

void MCharacter::Init()
{
	//LoadData(m_strName);
	m_pSprites->Init();

	m_pSprites->SetLooping(true);

	m_pPhysics = new MPhysics;
	m_pPhysics->Init();

	m_pState = new StandingState();
}

void MCharacter::Release()
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

void MCharacter::Update(float _delta)
{
	m_pPhysics->SetImgData(m_pSprites->GetCurrentImgData());
	m_pPhysics->SetVelocityX(0);

	if (GetAsyncKeyState(VK_DOWN))
	{
		HandleInput(EMAnimType::eMA_Prone);
		m_pSprites->SetFlip(false);
	}	
	else if (KEY_DOWN(VK_RIGHT))
	{
		if (m_pPhysics->IsJump())
		{
			HandleInput(EMAnimType::eMA_Moving);
		}

		m_pSprites->SetFlip(true);
		m_pPhysics->SetVelocityX(1);
	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_pPhysics->IsJump())
		{
			HandleInput(EMAnimType::eMA_Moving);
		}
		m_pSprites->SetFlip(false);
		m_pPhysics->SetVelocityX(-1);
	}


	else if (GetAsyncKeyState(VK_LCONTROL))
	{
		if (m_pPhysics->IsJump())
		{
			HandleInput(EMAnimType::eMA_Jumping);
			m_pPhysics->SetVelocityY(-1.5);
			m_pPhysics->SetJump(true);
			SoundManager->PlaySound(1);
		}
	}

	else
	{
		HandleInput(EMAnimType::eMA_Standing);
	}
	
	for (auto it : m_vComponent)
	{
		it->Update(this, _delta);
	}

	m_pPhysics->Update(this, _delta);
	m_pSprites->Update(this, _delta);
}

void MCharacter::HandleInput(EMAnimType _atype)
{
	MState* pState = m_pState->HandleInput(*this, _atype);

	if (pState != nullptr)
	{
		std::cout << "���� : " << _atype << std::endl;
		delete m_pState;
		m_pState = pState;
	}
}

void MCharacter::SetComponent(Component* _pComp)
{
	if (_pComp != nullptr)
		m_vComponent.push_back(_pComp);
}

void MCharacter::Move()
{
	//spr->anim("move")
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Moving);
	m_pSprites->SetLooping(true);
}

void MCharacter::Jump()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Jumping);
}

bool MCharacter::Stand()
{
	if (m_pPhysics->IsJump())
	{
		m_pSprites->SetCurrentAnim(EMAnimType::eMA_Standing);
		m_pSprites->SetLooping(true);
		return true;
	}

	else
		return false;
}

void MCharacter::Hit()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Hit);
}

void MCharacter::Die()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Die);
}

void MCharacter::Skill()
{
}

void MCharacter::Attack()
{
}

void MCharacter::Prone()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Prone);
}

void MCharacter::Ladder()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Ladder);
}

void MCharacter::Rope()
{
	m_pSprites->SetCurrentAnim(EMAnimType::eMA_Rope);
}

void MCharacter::LoadData(const std::string& _filename)
{
	m_Paser = Node(_filename.c_str());

	std::string sprname = _filename; // �̸�
	sprname.replace(sprname.find(".xml"), 4, "");

	int sprid = std::stoi(m_Paser.GetName());

	if (SPRMGR->GetSprDataCnt(sprid) == 0)
		for (auto o = m_Paser.begin(); o; o = o++) //anim name
		{
			if (strcmp(o.GetName(), "info"))
			{
				SPRDATA sprdata;
				int nCnt = 0;

				sprdata.path = sprname;
				sprdata.name = o.GetName();
				//int a = sprdata.name.find("skill");
				//sprdata.name.compare("Attack");

				for (auto t = m_Paser[o.GetName()].begin(); t; t = t++) // num
				{
					o.GetName();
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

				else if (!sprdata.name.find("prone"))
				{
					sprdata.type = EMAnimType::eMA_Prone;
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
