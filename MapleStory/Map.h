#pragma once
#include "rapidxml.hpp"
#include "MCharacter.h"

using namespace rapidxml;
using namespace Maple;
using namespace Gdiplus;

class MRoad;
class MCharacter;

class Map
{
public:
	Map();
	Map(const char* fileName);
	Map(int mapCode);
	~Map();
	void Init();
	void Load(int InMapCode);
	void Update(float delta);
	void Render(CDC* pDC);
	void Release();

	void PlayerInPortal(MCharacter* player);

	World* world;
private:
	int mapCode;

	MCharacter* player;

	Mob* pMob;
	Node mapNode;

	Gdiplus::PointF Target;
};