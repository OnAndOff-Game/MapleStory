#pragma once
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace Maple;
using namespace Gdiplus;

class MRoad;

class Map
{
public:
	Map();
	Map(const char* fileName);
	~Map();
	void Init();
	void Load(const char* fileName);
	void Update(float delta);
	void Render(CDC* pDC);
	void Release();

private:
	std::string mapCode;

	World* world;
	Mob* pMob;
	Node mapNode;

	bool test;

	Gdiplus::PointF Target;
};