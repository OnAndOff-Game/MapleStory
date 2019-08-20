#include "pch.h"
#include "Asset.h"
#include "MTile.h"
#include "MBack.h"
#include "TempObj.h"
#include "MRoad.h"
#include "Mob.h"
#include "MPhysics.h"
#include "Map.h"

Map::Map()
{
}

Map::Map(const char* fileName)
{
	mapCode = fileName;
	world = new World();
	mapNode = Node(mapCode.c_str());


	//pMob = new Mob("Mob/131.img.xml");
}

Map::Map(int mapCode)
{
	char temp[10];
	this->mapCode = "Xml/Map1/";
	this->mapCode += _itoa(mapCode,temp,10);
	this->mapCode += ".img.xml";
	mapNode = Node(this->mapCode.c_str());
	world = new World();
	
}

Map::~Map()
{
}

void Map::Init()
{
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
	

	ROAD->LoadData(&mapNode["foothold"]);

	//Node BackGround = mapNode["back"];
	//for (auto o = BackGround.begin(); o; o = o++)
	//{
	//	world->BackData(o);
	//}

}

void Map::Load(int mapCode)
{
	char temp[10];
	this->mapCode = "Xml/Map1/";
	this->mapCode += _itoa(mapCode, temp, 10);
	this->mapCode += ".img.xml";
	mapNode = Node(this->mapCode.c_str());
	world->Clear();

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


	ROAD->LoadData(&mapNode["foothold"]);
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
