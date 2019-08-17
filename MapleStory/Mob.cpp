#include "pch.h"
#include "MSprite.h"
#include "Mob.h"

Mob::Mob()
{
}

Mob::Mob(const std::string& _filename) : m_strName(_filename),
m_pPaser(nullptr)
{
	LoadData(_filename);
}

Mob::~Mob()
{
}

void Mob::Init()
{
	//LoadData(m_strName);
}

void Mob::Release()
{
	for (auto it : m_vComponent)
	{
		delete it;
	}

	m_vComponent.clear();
}

void Mob::Update(float _delta)
{
}

void Mob::Move()
{
	//spr->anim("move")
}

void Mob::Jump()
{
}

void Mob::Stand()
{
}

void Mob::Dead()
{
}

void Mob::Skill()
{
}

void Mob::Attack()
{
}

void Mob::LoadData(const std::string& _filename)
{
	if (m_pPaser == nullptr)
		m_pPaser = new Node(_filename.c_str());
	
	std::string sprname = m_pPaser[0].GetName(); // ÀÌ¸§
	int ane = stoi(sprname);

	if(SPRMGR->GetSprDataCnt(ane) == 0)
	for (auto o = m_pPaser[0].begin(); o; o = o++) //anim name
	{
		if (strcmp(o.GetName(), "info"))
		{
			SPRDATA sprdata;
			int nCnt = 0;

			sprdata.name = o.GetName();
			
			for (auto t = m_pPaser[0][o.GetName()].begin(); t; t = t++) // num
			{
				o.GetName();
				std::string file;

				IMG_DATA imgdata;

				file = _filename + '/' + sprdata.name + '.' + t.GetName() + ".png";

				file.replace(file.find(".xml"), 4, "");

				imgdata.filename = file;
				imgdata.id = atoi(t.GetName());
				imgdata.imgsize = t.GetValuePoint();

				for (auto f = m_pPaser[0][o.GetName()][t.GetName()].begin(); f; f = f++) // element
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

					if (!t["a1"].IsNull())
						imgdata.a1 = t["a1"].GetValueInt();

					//std::cout << node[0][o.GetName()][t.GetName()][f.GetName()].GetValueString() << std::endl;
				}

				ASSETMGR->SetAssetData(imgdata);
				nCnt++;
			}

			sprdata.cnt = nCnt;

			SPRMGR->SetSprData(sprdata);
		}
	}

	//m_pPaser->Release();

	if (m_pPaser != nullptr)
	{
		delete m_pPaser;
		m_pPaser = nullptr;
	}
}
