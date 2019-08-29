#pragma once
#include "Node.h"
#include "MTile.h"
#include "MBack.h"
#include "MPortal.h"
#include "MEnemy.h"
#include "TempObj.h"
#include <list>
class MLadRop;

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
		std::list<MBackground*> background;
		std::list<FOOTHOLD> footHold;
		std::list<MPortal*> portal;
		std::list<MEnemy*> enemy;
		std::list<MLadRop*> ladderRope;
		
		void PortalData(Node node);
		void BackData(Node node);
		void ObjData(Node node, int index);
		void TileData(Node node, int index);
		void LadderData(Node node);
		void EnemyData(Node node);
		void Clear();

		CPoint centerPos;
		CPoint mapSize;
	};
}