#include "pch.h"
#include "Asset.h"
#include "MPortal.h"
#include "MCharacter.h"
#include "Mob.h"
#include "Map.h"
#include "GameScene.h"

void GameScene::Init()
{
	map = new Map(106010101);
	map->Init();


	player = new MCharacter("Mob/131.img.xml");
	player->Init();
	player->Move();
	player->SetPosition(112, 206);
}

void GameScene::Update(float Delta)
{
	player->Update(Delta);
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
