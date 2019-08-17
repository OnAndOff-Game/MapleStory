#pragma once
#include <list>

class MTile;
class MBack;
class TempObj;
class MTemp;

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

	struct BACK
	{
		int x;
		int y;
		int rx;
		int ry;
		int type;
		int cx;
		int cy;
		std::string bS;
		std::string no;
		int a;
		int front;
		int ani;
		int f;
	};

	struct TILE
	{
		int x;
		int y;
		std::string u;
		std::string no;
		int zM;
		std::string GetTileName()
		{
			std::string temp = u;
			temp += "." + no + ".png";

			return temp;
		}
	};

	struct OBJECT
	{
		std::string oS;
		std::string l0;
		std::string l1;
		std::string l2;
		int x;
		int y;
		int z;
		int f;
		int zM;
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
		
		CPoint centerPos;
		CPoint mapSize;
	};
}