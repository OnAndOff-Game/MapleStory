#pragma once
#include "Node.h"
#include "Asset.h"
#include "MTile.h"
#include "MBack.h"
#include "MPortal.h"
#include "MLife.h"
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

	struct LADDER_ROPE
	{
		int l;
		int uf;
		int x;
		int y1;
		int y2;
		int page;
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
		std::list<MLife*> life;
		std::list<LADDER_ROPE> ladderRope;
		
		void PortalData(Node o);
		void BackData(Node o);
		void ObjData(Node o, int i);
		void TileData(Node o, int i);
		void LadderData(Node o);
		void LifeData(Node o);
		void Clear();

		CPoint centerPos;
		CPoint mapSize;
	};
}