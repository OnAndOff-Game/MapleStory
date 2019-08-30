#pragma once


const char* ORIGIN = "origin";
const char* INLINK = "_inlink";
const char* LEFT_TOP = "lt";
const char* RIGHT_BOTTOM = "rb";
const char* HEAD = "head";
const char* DELAY = "delay";
const char* BEGIN_ALPHA = "a0";
const char* END_ALPHA = "a1";
const char* Z_ORDER = "z";

class MParser
{
public:

	void Mob(const std::string& _filename);

	EMAnimType AnimTypeSetting(std::string& inAnim);
	void GetImgData(IMG_DATA& outImgData, Node& inNode);
	void GetMobData(MobData& outMobData, Node& inNode);
};

