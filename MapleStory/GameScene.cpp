#include "pch.h"
#include "Asset.h"
#include "MPortal.h"
#include "Mob.h"
#include "Map.h"
#include "GameScene.h"

void GameScene::Init()
{
	map = new Map("xml/100000000.img.xml");
	map->Init();


	player = new Mob("Mob/131.img.xml");
	player->Init();
	player->Move();
	player->SetPosition(112, 206);
}

PointF target(800, 30);
void GameScene::Update(float Delta)
{
	map->Update(Delta);
	player->Update(Delta);

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
