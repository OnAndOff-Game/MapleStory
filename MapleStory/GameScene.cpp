#include "pch.h"
#include "Asset.h"
#include "MPortal.h"
#include "MCharacter.h"
#include "Mob.h"
#include "Map.h"
#include "GameScene.h"

void GameScene::Init()
{
	map = new Map(100000000);
	map->Init();


	player = new MCharacter("Mob/131.img.xml");
	player->Init();
	player->Move();
	player->SetPosition(112, 216);
	
	OBJMGR->SetObject(player->m_ProxyID.GetProxyID(), player);
}

void GameScene::Update(float Delta)
{
	//player->Update(Delta);
	//pMob->Update(Delta);
	//pMob2->Update(Delta);
	OBJMGR->Update(Delta);
	map->Update(Delta);

	// Æ÷Å» ÀÌµ¿
	if (GetAsyncKeyState('A'))
		map->PlayerInPortal(player);

	View::Target = player->GetPosition();
	int left =  View::Target.X - Constants::SCREEN_SIZE_X / 2 + map->world->centerPos.x - 40;
	int right = left - map->world->mapSize.x + Constants::SCREEN_SIZE_X + 71;
	int bottom = View::Target.Y - Constants::SCREEN_SIZE_Y - map->world->centerPos.y;
	if (left <= -20)
	{
		View::Target.X -= left;
	}
	else if (right >= 0)
	{
		View::Target.X -= right;
	}
	View::CameraFollow(5 * Delta);
}


void GameScene::Render(Gdiplus::Graphics* _memG)
{
}

void GameScene::Release()
{
	if (map != nullptr)
	{
		map->Release();
		delete map;
	}

}
