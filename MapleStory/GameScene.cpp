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

	pMob = new Mob("Mob/5130101.img.xml");
	pMob->Init();
	pMob->Move();

	pMob->SetPosition(112, 216);

	pMob2 = new Mob("Mob/2220100.img.xml");
	pMob2->Init();
	pMob2->Move();

	pMob2->SetPosition(112, 216);
	
}

void GameScene::Update(float Delta)
{
	player->Update(Delta);
	pMob->Update(Delta);
	pMob2->Update(Delta);
	map->Update(Delta);

	if (GetAsyncKeyState('A'))
		map->PlayerInPortal(player);

	View::Target = player->GetPosition();

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
