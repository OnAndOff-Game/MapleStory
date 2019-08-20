#include "pch.h"
#include "World.h"

void Maple::World::PortalData(Node o)
{
	//PORTAL temp;
	//temp.x = o["x"].GetValueInt();
	//temp.y = o["y"].GetValueInt();
	//if (o["tm"].GetValueInt() == 999999999 ||
	//	o["tm"].GetValueInt() == 100000000)
	//	return;
	//MPortal * pt = new MPortal(temp, new Asset(EMRenderType::eMR_Map, "Portal/pv.0.png", 1));
	//pt->SetPosition(temp.x, temp.y - pt->GetAssetSize().Y / 2 + 10);
	//portal.push_back(pt);
	static int a = 0;
	PORTAL pot;

	pot.pn = o["pn"].GetValueString();
	pot.pt = o["pt"].GetValueInt();
	pot.x = o["x"].GetValueInt();
	pot.y = o["y"].GetValueInt();
	pot.tm = o["tm"].GetValueInt();
	pot.tn = o["tn"].GetValueString();

	MPortal* pPortal = new MPortal(pot);
	pPortal->SetPosition(pot.x, pot.y - 80);
	portal.push_back(pPortal);
}

void Maple::World::BackData(Node o)
{
	BACK temp;
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
	if (temp.type == 3)
		pBack = new MBack(temp, new Asset(EMRenderType::eMR_Map, path + '/' + fileName, Gdiplus::Rect(0, 0, Constants::SCREEN_SIZE_X, Constants::SCREEN_SIZE_Y), 0, true));
	else
		pBack = new MBack(temp, new Asset(EMRenderType::eMR_Map, path + '/' + fileName, 0));
	pBack->SetPosition(pBack->GetSize().Width / 2, pBack->GetSize().Height / 2);

	back.push_back(pBack);
}

void Maple::World::ObjData(Node o, int i)
{
	OBJECT temp;
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
	layer[i].obj.push_back(pTempObj);
}

void Maple::World::TileData(Node o, int i)
{
	TILE temp;
	temp.x = o["x"].GetValueInt();
	temp.y = o["y"].GetValueInt();
	temp.u = o["u"].GetValueString();
	temp.no = o["no"].GetValueString();
	temp.zM = o["zM"].GetValueInt();


	MTile* pTile = new MTile(temp, new Asset(EMRenderType::eMR_Map, layer[i].info.tS + '/' + temp.GetTileName(), i));

	if (!pTile->TileData.u.compare("enV0"))
		pTile->SetPosition({ pTile->TileData.x - pTile->GetAssetSize().X / 2, pTile->TileData.y + pTile->GetAssetSize().Y / 2 });
	else if (!pTile->TileData.u.compare("enH0"))
		pTile->SetPosition({ pTile->TileData.x + pTile->GetAssetSize().X / 2, pTile->TileData.y - pTile->GetAssetSize().Y / 2 });
	else if (!pTile->TileData.u.compare("edU"))
		pTile->SetPosition({ pTile->TileData.x, pTile->TileData.y - pTile->GetAssetSize().Y / 2 });
	else if (!pTile->TileData.u.compare("edD"))
		pTile->SetPosition({ pTile->TileData.x, pTile->TileData.y + pTile->GetAssetSize().Y / 2 });
	else if (!pTile->TileData.u.compare("slLU"))
		pTile->SetPosition({ pTile->TileData.x - pTile->GetAssetSize().X / 2, pTile->TileData.y - pTile->GetAssetSize().Y / 2 });
	else if (!pTile->TileData.u.compare("slRU"))
		pTile->SetPosition({ pTile->TileData.x + pTile->GetAssetSize().X / 2, pTile->TileData.y - pTile->GetAssetSize().Y / 2 });
	else
		pTile->SetPosition({ pTile->TileData.x + pTile->GetAssetSize().X / 2,pTile->TileData.y + pTile->GetAssetSize().Y / 2 });

	layer[i].tile.push_back(pTile);
}