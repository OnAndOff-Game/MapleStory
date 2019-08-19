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


	//카메라 이동 Target 좌표가 곧 캐릭터 좌표가 될것.
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		target.X += 30;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		target.X -= 30;
	if (GetAsyncKeyState(VK_UP) & 0x8001)
		target.Y -= 30;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		target.Y += 30;
	View::viewPort.X = Lerp(View::viewPort.X, target.X, 5 * Delta * 0.001);
	View::viewPort.Y = Lerp(View::viewPort.Y, target.Y, 5 * Delta * 0.001);
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
