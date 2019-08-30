#include "pch.h"
#include "Asset.h"
#include "MTile.h"
#include "MBack.h"
#include "TempObj.h"
#include "MRoad.h"
#include "Mob.h"
#include "MCharacter.h"
#include "MPhysics.h"
#include "Map.h"

Map::Map()
{
}

Map::Map(const char* fileName)
{
	std::string filePath = fileName;
	world = new World();
	mapNode = new Node(filePath.c_str());


	//pMob = new Mob("Mob/131.img.xml");
}

Map::Map(int mapCode)
{
	world = new World();
}

Map::~Map()
{
}

void Map::Init()
{
	// 100000000는 헤네시스 맵코드.
	Load(100000000);
}

void Map::Load(int InMapCode)
{
	char temp[10];
	this->mapCode = InMapCode;
	std::string filePath;
	filePath = "Xml/Map1/";
	filePath += _itoa(InMapCode, temp, 10);
	filePath += ".img.xml";

	// 해제
	world->Clear();	
	if(mapNode !=nullptr)
		mapNode->Release();
	mapNode = new Node(filePath.c_str());
	OBJMGR->Reset();
	ROAD->GetInstance()->Release();

	// 사운드 로드
	Node info = mapNode[0]["info"];
	world->layer[0].info.bgm = info["bgm"].GetValueString();
	std::string soundPath = "Sound/" + world->layer[0].info.bgm + ".mp3";
	SoundManager->LoadBackGroundSound(soundPath);

	////// 맵의 사이즈
	Node miniMap = mapNode[0]["miniMap"];
	world->centerPos.x = miniMap["centerX"].GetValueInt();
	world->centerPos.y = miniMap["centerY"].GetValueInt();
	world->mapSize.x = miniMap["width"].GetValueInt();
	world->mapSize.y = miniMap["height"].GetValueInt();

	for (int i = 0; i < LAYER_SIZE; i++)
	{
		Node info = mapNode[0][i]["info"]["tS"];
		if (!info.IsNull())
		{
			world->layer[i].info.tS = "Tile\\" + info.GetValueString() + ".img";
		}

		Node tile = mapNode[0][i]["tile"];
		for (auto Itr = tile.begin(); Itr; Itr++)
		{
			world->TileData(Itr, i);
		}
		Node obj = mapNode[0][i]["obj"];
		for (auto Itr = obj.begin(); Itr; Itr++)
		{
			world->ObjData(Itr, i);
		}
	}

	Node portal = mapNode[0]["portal"];
	for (auto Itr = portal.begin(); Itr; Itr++)
	{
		world->PortalData(Itr);
	}

	Node life = mapNode[0]["life"];
	for (auto Itr = life.begin(); Itr; Itr++)
	{
		std::string w = Itr["type"].GetValueString();
		if(!Itr["type"].GetValueString().compare("m"))
			world->EnemyData(Itr);
	}

	Node ladderRope = mapNode[0]["ladderRope"];
	for (auto Itr = ladderRope.begin(); Itr; Itr++)
	{
		world->LadderData(Itr);
	}

	Node BackGround = mapNode[0]["back"];
	for (auto o = BackGround.begin(); o; o = o++)
	{
		world->BackData(o);
	}

	ROAD->LoadData(&mapNode[0]["foothold"]);
	SoundManager->PlaySound(Sound_BackGround);
}

void Map::Update(float delta)
{
	for (auto t : world->background)
	{
		t->Update(delta);
		if (t->BackData.type == 4)
			break;;
	}

	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (auto Itr : world->layer[i].obj)
		{
			Itr->Update(delta);
		}
		for (auto Itr : world->layer[i].tile)
		{
			Itr->Update(delta);
		}
	}

	for (auto Itr : world->portal)
	{
		Itr->Update(delta);
	}

	for (auto Itr : world->enemy)
	{
		Itr->Update(delta);
	}
}

void Map::Release()
{
	mapNode->Release();
	
	world->Clear();
	delete	world;
}

void Map::PlayerInPortal(MCharacter* player)
{
	for (auto Itr : world->portal)
	{
		if (Itr->PortalCollision(player->GetPosition()))
		{
			std::string tn = Itr->PortalData.tn;
			if(Itr->PortalData.tm != mapCode)
				Load(Itr->PortalData.tm);
			for (auto Itr2 : world->portal)
			{
				if (!Itr2->PortalData.pn.compare(tn))
				{
					player->SetPosition(Itr2->PortalData.x, Itr2->PortalData.y - 10);
					player->Revision();
					
					if (Itr->PortalData.tm != Itr2->PortalData.tm)
					{
						View::viewPort.X = player->GetPosition().X;
						View::viewPort.Y = player->GetPosition().Y;
					}
				}
			}
			SoundManager->PlaySound(SoundType::Sound_Portal);
			return;
		}
	}
}
