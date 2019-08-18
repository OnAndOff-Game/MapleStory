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


	pMob = new Mob("Mob/131.img.xml");

	pMob->SetPosition(Point(50, 10));
	pMob->Init();

	pMob->Move();
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
			//std::cout << world->layer[i].info.tS << std::endl;
			//SpriteManager->LoadResource(world->layer[i].info.tS.c_str()); -> getasset 시 자동 생성
		}

		Node tile = mapNode[i]["tile"];

		for (auto o = tile.begin(); o; o = o++)
		{
			Maple::TILE temp;
			temp.x = o["x"].GetValueInt();
			temp.y = o["y"].GetValueInt();
			temp.u = o["u"].GetValueString();
			temp.no = o["no"].GetValueString();
			temp.zM = o["zM"].GetValueInt();


			MTile* pTile = new MTile(temp, new Asset(EMRenderType::eMR_Map, world->layer[i].info.tS + '/' + temp.GetTileName(), i));

			world->layer[i].tile.push_back(pTile);
		}
		Node obj = mapNode[i]["obj"];
		for (auto o = obj.begin(); o; o = o++)
		{
			Maple::OBJECT temp;
			temp.l0 = o["l0"].GetValueString();
			temp.l1 = o["l1"].GetValueString();
			temp.l2 = o["l2"].GetValueString();
			temp.oS = o["oS"].GetValueString();
			temp.x = o["x"].GetValueInt();
			temp.y = o["y"].GetValueInt();
			temp.z = o["z"].GetValueInt();
			temp.f = o["f"].GetValueInt();
			temp.zM = o["zM"].GetValueInt();
			std::string path = "Object/" + temp.oS + ".img";
			std::string fileName = temp.l0 + "." + temp.l1 + "." + temp.l2 + ".0" + ".png";

			TempObj* pTempObj = new TempObj(temp, new Asset(EMRenderType::eMR_Map, path + '/' + fileName, i));
			
			//SpriteManager->LoadResource(path.c_str());
			pTempObj->SetPosition(temp.x, temp.y);
			world->layer[i].obj.push_back(pTempObj);
		}
	}


	for (int i = 0; i < 8; i++)
	{
		for (auto& t : world->layer[i].tile)
		{
			if (!t->TileData.u.compare("enV0"))
				t->SetPosition({ t->TileData.x - t->GetAssetSize().X / 2, t->TileData.y + t->GetAssetSize().Y / 2});
			else if (!t->TileData.u.compare("enH0"))
				t->SetPosition({ t->TileData.x + t->GetAssetSize().X / 2, t->TileData.y - t->GetAssetSize().Y / 2});
			else if (!t->TileData.u.compare("edU"))
				t->SetPosition({ t->TileData.x, t->TileData.y - t->GetAssetSize().Y / 2 });
			else if (!t->TileData.u.compare("edD"))
				t->SetPosition({ t->TileData.x, t->TileData.y + t->GetAssetSize().Y / 2 });
			else if (!t->TileData.u.compare("slLU"))
				t->SetPosition({ t->TileData.x - t->GetAssetSize().X / 2, t->TileData.y - t->GetAssetSize().Y / 2 });
			else if (!t->TileData.u.compare("slRU"))
				t->SetPosition({ t->TileData.x + t->GetAssetSize().X / 2, t->TileData.y - t->GetAssetSize().Y / 2 });
			else
				t->SetPosition({ t->TileData.x+ t->GetAssetSize().X / 2,t->TileData.y + t->GetAssetSize().Y / 2 });
		}
	}

	m_pRoad->LoadData(&mapNode["foothold"]);

	Node BackGround = mapNode["back"];
	for (auto o = BackGround.begin(); o; o = o++)
	{
		Maple::BACK temp;
		temp.no = o["no"].GetValueString();
		temp.x = o["x"].GetValueInt();
		temp.y = o["y"].GetValueInt();
		temp.rx = o["rx"].GetValueInt();
		temp.ry = o["ry"].GetValueInt();
		temp.type = o["type"].GetValueInt();
		temp.cx = o["cx"].GetValueInt();
		temp.cy = o["cy"].GetValueInt();
		temp.bS = o["bS"].GetValueString();
		temp.a = o["a"].GetValueInt();
		temp.front = o["front"].GetValueInt();
		temp.ani = o["ani"].GetValueInt();
		temp.f = o["f"].GetValueInt();
		std::string path = "Back\\" + temp.bS + ".img\\" + temp.bS + ".img";
		std::string fileName = "back." + temp.no + ".png";
		
		MBack* pBack;
		if(temp.type == 3)
			pBack = new MBack(temp, new Asset(EMRenderType::eMR_Map, path + '/' + fileName, Gdiplus::Rect(0,0,Constants::SCREEN_SIZE_X, Constants::SCREEN_SIZE_Y),0,true));
		else
			pBack = new MBack(temp, new Asset(EMRenderType::eMR_Map, path + '/' + fileName, 0));
		pBack->SetPosition(pBack->GetSize().Width / 2, pBack->GetSize().Height / 2);

		world->back.push_back(pBack);
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
		break;
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

	//Gdiplus::Point pt = pMob->GetPosition();
	//RoadLine* pLine = m_pRoad->GetLine(pt);
	//if (pLine != nullptr)
	//	pMob->SetPosition(Gdiplus::Point(pt.X, pLine->line1.Y));
	//else
	//	pMob->Offset(0, 0);
	pMob->Update(delta);
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
