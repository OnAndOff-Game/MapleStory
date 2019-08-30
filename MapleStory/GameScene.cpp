#include "pch.h"
#include "Asset.h"
#include "MPortal.h"
#include "MCharacter.h"
#include "Mob.h"
#include "Map.h"
#include "GameUI.h"
#include "GameScene.h"

void GameScene::Init()
{
	map = new Map(100000000);
	map->Init();
	
	player = new MCharacter("Mob/131.img.xml");
	player->Init();
	player->Move();
	player->SetPosition(112, 216);

	gameUI = new GameUI();
	gameUI->Init();
		
	OBJMGR->SetObject(player->objectId.GetObjectId(), player);
}

void GameScene::Update(float Delta)
{
	//player->Update(Delta);
	//pMob->Update(Delta);
	//pMob2->Update(Delta);
	
	if (KEY_DOWN(VK_ESCAPE))
	{
		AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_APP_EXIT);
	}
	
	OBJMGR->Update(Delta);
	map->Update(Delta);
	//player->GetLadderRope(map->world->ladderRope);


	// 포탈 이동
	if (GetAsyncKeyState('A'))
		map->PlayerInPortal(player);

	if (GetAsyncKeyState('O'))
		ROAD->DrawLine(true);
	
	if (GetAsyncKeyState('I'))
		ROAD->DrawLine(false);

	// 인게임 모든 HUD
	gameUI->Update(Delta);

	// 카메라 이동
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

	View::CameraFollow(3 * Delta);
}


void GameScene::Render(Gdiplus::Graphics* _memG)
{
	gameUI->Render(_memG);
}

void GameScene::Release()
{
	if (map != nullptr)
	{
		map->Release();
		delete map;
	}
	
	if (player != nullptr)
	{
		player->Release();
		delete player;
	}
	
	if (gameUI != nullptr)
	{
		gameUI->Release();
		delete gameUI;
	}
}
