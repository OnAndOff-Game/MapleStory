#pragma once
#include "rapidxml.hpp"
#include "MCharacter.h"

using namespace rapidxml;
using namespace Maple;
using namespace Gdiplus;

class MRoad;

class Map
{
public:
	Map();
	Map(const char* fileName);
	Map(int mapCode);
	~Map();
	void Init();
	void Load(int mapCode);
	void Update(float delta);
	void Render(CDC* pDC);
	void Release();

	World* world;
private:
	std::string mapCode;

	MCharacter* player;

	Mob* pMob;
	Node mapNode;

	bool test;

	Gdiplus::PointF Target;
};