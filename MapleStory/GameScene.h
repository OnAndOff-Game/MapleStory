#pragma once

class SprMgr;
class Asset;
class Map;
class Mob;
class MCharacter;
class GameUI;

class GameScene : public Scene
{
public:
	SCENE_CONSTRUCTOR

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* _memG);
	void Release();

private:
	Map* map;
	MCharacter* player;
	GameUI* gameUI;
};