#include "pch.h"
#include "Asset.h"
#include "MTile.h"
#include "MBack.h"
#include "TempObj.h"
#include "MRoad.h"
#include "Mob.h"
#include "Map.h"

Map::Map()
{
}

Map::Map(const char* fileName)
{
	mapCode = fileName;
	world = new World();
	m_pRoad = new MRoad();
	mapNode = Node(mapCode.c_str());
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
			world->TileData(o,i);
		}
		Node obj = mapNode[i]["obj"];
		for (auto o = obj.begin(); o; o = o++)
		{
			world->ObjData(o,i);
		}
	}

	m_pRoad->LoadData(&mapNode["foothold"]);

	Node BackGround = mapNode["back"];
	for (auto o = BackGround.begin(); o; o = o++)
	{
		world->BackData(o);
	}
	
	Node Portal = mapNode["portal"];
	for (auto o = Portal.begin(); o; o = o++)
	{
		world->PortalData(o);
	}

}

void Map::Load(const char* fileName)
{

}

void Map::Update(float delta)
{
	for (auto t : world->back)
	{
		t->Update(delta);
	}

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
	delete m_pRoad;
}
