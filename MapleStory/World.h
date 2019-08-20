#pragma once
#include "Node.h"
#include "Asset.h"
#include "MTile.h"
#include "MBack.h"
#include "MPortal.h"
#include "TempObj.h"
#include <list>

namespace Maple
{
	struct INFO
	{
		int version;
		int cloud;
		int town;
		float mobRate;
		std::string bgm;
		int returnMap;
		int forcedMap;
		int hideMinimap;
		int moveLimit;
		std::string mapMark;

		std::string tS;
	};

	struct FOOTHOLD
	{
		int x1;
		int x2;
		int y1;
		int y2;
	};

	struct LAYER
	{
		INFO info;
		std::list<MTile*> tile;
		std::list<TempObj*> obj;
	};

	class World
	{
	public:
		LAYER layer[8];
		std::list<MBack*> back;
		std::list<FOOTHOLD> footHold;
		std::list<MPortal*> portal;
		
		void PortalData(Node o);
		void BackData(Node o);
		void ObjData(Node o, int i);
		void TileData(Node o, int i);

		CPoint centerPos;
		CPoint mapSize;
	};
}