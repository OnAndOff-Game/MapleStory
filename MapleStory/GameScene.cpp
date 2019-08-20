#include "pch.h"
#include "Asset.h"
#include "Mob.h"
#include "Map.h"
#include "GameScene.h"

void GameScene::Init()
{
	map = new Map("xml/100000000.img.xml");
	map->Init();
}

PointF target(800, 30);
void GameScene::Update(float Delta)
{
	map->Update(Delta);

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		View::Target.X-= 50;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		View::Target.X+= 50;
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		View::Target.Y -= 50;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		View::Target.Y += 50;
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
