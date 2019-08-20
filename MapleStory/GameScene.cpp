#include "pch.h"
#include "Asset.h"
#include "MPortal.h"
#include "Mob.h"
#include "Map.h"
#include "GameScene.h"

void GameScene::Init()
{
	map = new Map(106010102);
	map->Init();


	player = new Mob("Mob/131.img.xml");
	player->Init();
	player->Move();
	player->SetPosition(112, 206);
}

PointF target(800, 30);
void GameScene::Update(float Delta)
{
	player->Update(Delta);
	map->Update(Delta);

	if (GetAsyncKeyState('A'))
		map->Load(100000000);

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
