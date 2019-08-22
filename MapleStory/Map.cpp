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
	mapNode = Node(filePath.c_str());


	//pMob = new Mob("Mob/131.img.xml");
}

Map::Map(int mapCode)
{
	char temp[10];
	this->mapCode = mapCode;
	std::string filePath;
	filePath = "Xml/Map1/";
	filePath += _itoa(mapCode,temp,10);
	filePath += ".img.xml";
	mapNode = Node(filePath.c_str());
	world = new World();
	
}

Map::~Map()
{
}

void Map::Init()
{
	Load(100000000);

	//Node BackGround = mapNode["back"];
	//for (auto o = BackGround.begin(); o; o = o++)
	//{
	//	world->BackData(o);
	//}
}

void Map::Load(int mapCode)
{
	char temp[10];
	this->mapCode = mapCode;
	std::string filePath;
	filePath = "Xml/Map1/";
	filePath += _itoa(mapCode, temp, 10);
	filePath += ".img.xml";
	mapNode = Node(filePath.c_str());
	world->Clear();
	ROAD->GetInstance()->Release();

	// 사운드 로드
	Node info = mapNode["info"];
	world->layer[0].info.bgm = info["bgm"].GetValueString();
	std::string soundPath = "Sound/" + world->layer[0].info.bgm + ".mp3";
	SoundManager->LoadSound(soundPath);

	// 크기
	Node miniMap = mapNode["miniMap"];
	world->centerPos.x = miniMap["centerX"].GetValueInt();
	world->centerPos.y = miniMap["centerY"].GetValueInt();
	world->mapSize.x = miniMap["width"].GetValueInt();
	world->mapSize.y = miniMap["height"].GetValueInt();

	for (int i = 0; i < 8; i++)
	{
		Node info = mapNode[i]["info"]["tS"];
		if (!info.IsNull())
		{
			world->layer[i].info.tS = "Tile\\" + info.GetValueString() + ".img";
		}

		Node tile = mapNode[i]["tile"];

		for (auto o = tile.begin(); o; o = o++)
		{
			world->TileData(o, i);
		}
		Node obj = mapNode[i]["obj"];
		for (auto o = obj.begin(); o; o = o++)
		{
			world->ObjData(o, i);
		}
	}

	Node portal = mapNode["portal"];
	for (auto o = portal.begin(); o; o = o++)
	{
		world->PortalData(o);
	}

	Node life = mapNode["life"];
	for (auto o = life.begin(); o; o = o++)
	{
		world->LifeData(o);
	}

	Node ladderRope = mapNode["ladderRope"];
	for (auto o = ladderRope.begin(); o; o = o++)
	{
		world->LadderData(o);
	}


	//Node BackGround = mapNode["back"];
	//for (auto o = BackGround.begin(); o; o = o++)
	//{
	//	world->BackData(o);
	//}

	ROAD->LoadData(&mapNode["foothold"]);
	SoundManager->PlaySound(0);
}

void Map::Update(float delta)
{
	//for (auto t : world->back)
	//{
	//	t->Update(delta);
	//	break;
	//}

	for (int i = 0; i < 8; i++)
	{
		for (auto t : world->layer[i].obj)
		{
			t->Update(delta);
		}
		for (auto t : world->layer[i].tile)
		{
			t->Update(delta);
		}
	}

	for (auto t : world->portal)
	{
		t->Update(delta);
	}

	for (auto t : world->life)
	{
		t->Update(delta);
	}
}

void Map::Release()
{
	for (int i = 0; i < 8; i++)
	{
		for (auto t : world->layer[i].tile)
		{
			t->Release();
			delete t;
		}
		for (auto t : world->layer[i].obj)
		{
			t->Release();
			delete t;
		}
	}
	delete	world;
}

void Map::PlayerInPortal(MCharacter* player)
{
	for (auto t : world->portal)
	{
		if (t->PortalCollision(player->GetPosition()))
		{
			std::string tn = t->PortalData.tn;
			Load(t->PortalData.tm);
			for (auto t : world->portal)
			{
				if (!t->PortalData.pn.compare(tn))
				{
					player->SetPosition(t->PortalData.x, t->PortalData.y - 10);
					//View::viewPort.X = player->GetPosition().X;
					//View::viewPort.Y = player->GetPosition().Y;
				}
			}
			SoundManager->PlaySound(2);
			return;
		}
	}
}
