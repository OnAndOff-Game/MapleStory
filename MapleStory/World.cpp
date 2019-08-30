#include "pch.h"
#include "MLadRop.h"
#include "Asset.h"
#include "World.h"

void Maple::World::PortalData(Node node)
{
	PORTAL pot;

	pot.pn = node["pn"].GetValueString();
	pot.pt = node["pt"].GetValueInt();
	pot.x = node["x"].GetValueInt();
	pot.y = node["y"].GetValueInt();
	pot.tm = node["tm"].GetValueInt();
	pot.tn = node["tn"].GetValueString();

	if (pot.tm == 999999999)
		return;

	MPortal* pPortal = new MPortal(pot);
	pPortal->SetPosition(pot.x, pot.y);
	portal.push_back(pPortal);
}

void Maple::World::BackData(Node node)
{
	BACKGROUND temp;
	temp.no = node["no"].GetValueString();
	temp.x = node["x"].GetValueInt();
	temp.y = node["y"].GetValueInt();
	temp.rx = node["rx"].GetValueInt();
	temp.ry = node["ry"].GetValueInt();
	temp.type = node["type"].GetValueInt();
	temp.cx = node["cx"].GetValueInt();
	temp.cy = node["cy"].GetValueInt();
	temp.bS = node["bS"].GetValueString();
	temp.a = node["a"].GetValueInt();
	temp.front = node["front"].GetValueInt();
	temp.ani = node["ani"].GetValueInt();
	temp.f = node["f"].GetValueInt();
	std::string path = "Back\\" + temp.bS + ".img\\" + temp.bS + ".img";
	std::string fileName = "back." + temp.no + ".png";

	MBackground* pBack;
	if (temp.type == 4)
		pBack = new MBackground(temp, new Asset(EMRenderType::eMRenderType_Map, path + '/' + fileName, Gdiplus::Rect(0, 0, Constants::SCREEN_SIZE_X, Constants::SCREEN_SIZE_Y), 0, true));
	else
		pBack = new MBackground(temp, new Asset(EMRenderType::eMRenderType_Map, path + '/' + fileName, 0));
	pBack->SetPosition(pBack->GetSize().Width / 2, pBack->GetSize().Height / 2);

	background.push_back(pBack);
}

void Maple::World::ObjData(Node node, int index)
{
	OBJECT temp;
	temp.l0 = node["l0"].GetValueString();
	temp.l1 = node["l1"].GetValueString();
	temp.l2 = node["l2"].GetValueString();
	temp.oS = node["oS"].GetValueString();
	temp.x = node["x"].GetValueInt();
	temp.y = node["y"].GetValueInt();
	temp.z = node["z"].GetValueInt();
	temp.f = node["f"].GetValueInt();
	temp.zM = node["zM"].GetValueInt();
	std::string path = "Object/" + temp.oS + ".img";
	std::string fileName = temp.l0 + "." + temp.l1 + "." + temp.l2 + ".0" + ".png";

	TempObj* pTempObj = new TempObj(temp, new Asset(EMRenderType::eMRenderType_Map, path + '/' + fileName, index));
	//SpriteManager->LoadResource(path.c_str());
	pTempObj->SetPosition(temp.x, temp.y);
	layer[index].obj.push_back(pTempObj);
}

void Maple::World::TileData(Node node, int index)
{
	TILE temp;

	temp.x = node["x"].GetValueInt();
	temp.y = node["y"].GetValueInt();
	temp.u = node["u"].GetValueString();
	temp.no = node["no"].GetValueString();
	temp.zM = node["zM"].GetValueInt();


	MTile* pTile = new MTile(temp, new Asset(EMRenderType::eMRenderType_Map, layer[index].info.tS + '/' + temp.GetTileName(), index));

	if (!pTile->TileData.u.compare("enV0"))
		pTile->SetPosition(Point(pTile->TileData.x - pTile->GetAssetSize().X / 2, 
			pTile->TileData.y + pTile->GetAssetSize().Y / 2));
	else if (!pTile->TileData.u.compare("enH0"))
		pTile->SetPosition(Point(pTile->TileData.x + pTile->GetAssetSize().X / 2,
			pTile->TileData.y - pTile->GetAssetSize().Y / 2 ));
	else if (!pTile->TileData.u.compare("edU"))
		pTile->SetPosition(Point(pTile->TileData.x, 
			pTile->TileData.y - pTile->GetAssetSize().Y / 2));
	else if (!pTile->TileData.u.compare("edD"))
		pTile->SetPosition(Point(pTile->TileData.x, 
			pTile->TileData.y + pTile->GetAssetSize().Y / 2));
	else if (!pTile->TileData.u.compare("slLU"))
		pTile->SetPosition(Point(pTile->TileData.x - pTile->GetAssetSize().X / 2, 
			pTile->TileData.y - pTile->GetAssetSize().Y / 2));
	else if (!pTile->TileData.u.compare("slRU"))
		pTile->SetPosition(Point(pTile->TileData.x + pTile->GetAssetSize().X / 2, 
			pTile->TileData.y - pTile->GetAssetSize().Y / 2));
	else
		pTile->SetPosition(Point(pTile->TileData.x + pTile->GetAssetSize().X / 2,
			pTile->TileData.y + pTile->GetAssetSize().Y / 2));

	layer[index].tile.push_back(pTile);
}

void Maple::World::LadderData(Node node)
{
	LADDER_ROPE temp;
	temp.l = node["l"].GetValueInt();
	temp.uf = node["uf"].GetValueInt();
	temp.x = node["x"].GetValueInt();
	temp.y1 = node["y1"].GetValueInt();
	temp.y2 = node["y2"].GetValueInt();
	temp.page = node["page"].GetValueInt();

	MLadRop* pLR = new MLadRop(temp);
	ladderRope.push_back(pLR);
}

void Maple::World::EnemyData(Node node)
{
	ENEMY temp;
	temp.type = node["type"].GetValueString();
	//if (!temp.type.compare("n")) return;
	temp.id = "3230100";
	//temp.x = node["x"].GetValueInt();
	//temp.y = node["y"].GetValueInt();

	////TODO : 지금은 사용하지 않습니다///////////////
	////temp.id = o["id"].GetValueInt();
	////temp.mobTime = o["mobTime"].GetValueInt();
	////temp.f = o["f"].GetValueInt();
	////temp.hide = o["hide"].GetValueInt();
	////temp.fh = o["fh"].GetValueInt();
	////temp.cy = o["cy"].GetValueInt();
	//////////////////////////////////////////////

	//temp.movementLeft = node["rx0"].GetValueInt();
	//temp.movementRight = node["rx1"].GetValueInt();

	MEnemy* pEnemy = new MEnemy(temp);
	pEnemy->Init();
	pEnemy->Move();
	enemy.push_back(pEnemy);
	OBJMGR->SetObject(pEnemy->objectId.GetObjectId(), pEnemy);
}

void Maple::World::Clear()
{
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		layer[i].info = INFO();

		for (auto it : layer[i].tile)
		{
			if (it != nullptr)
			{
				it->Release();
				delete it;
			}
		}
		layer[i].tile.clear();

		for (auto it : layer[i].obj)
		{
			if (it != nullptr)
			{
				it->Release();
				delete it;
			}
		}		
		layer[i].obj.clear();
	}

	for (auto it : background)
	{
		if (it != nullptr)
		{
			it->Release();
			delete it;
		}
	}
	background.clear();

	footHold.clear();
	
	for (auto it : portal)
	{
		if (it != nullptr)
		{
			it->Release();
			delete it;
		}
	}
	portal.clear();

	for (auto it : enemy)
	{
		if (it != nullptr)
		{
			it->Release();
			delete it;
		}
	}
	enemy.clear();

	for (auto it : ladderRope)
	{
		if (it != nullptr)
		{
			//it->Release();
			delete it;
		}
	}	
	ladderRope.clear();

}