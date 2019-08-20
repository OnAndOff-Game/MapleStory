#include "pch.h"
#include "Asset.h"
#include "MPortal.h"


MPortal::MPortal(const PORTAL& _portaldata)
{
	PortalData = _portaldata;
	
	for (int i = 0; i < 8; i++)
	{
		std::string path = "Portal/";
		path += "pv.";
		path += (i + 48);
		path += ".png";

		mAsset[i] = new Asset(EMRenderType::eMR_Map, path);
	}
	curAni = 0;
}

MPortal::~MPortal()
{
}

void MPortal::Init()
{
}

void MPortal::LoadData(const std::string& _filename)
{
}

void MPortal::Update(float _delta)
{
	curAniTime += _delta;
	if (curAniTime > 10)
	{
		curAni++;
		if (curAni > 7)
			curAni = 0;
		curAniTime = 0;
	}
	mAsset[curAni]->Update(this, _delta);
}

Gdiplus::Point& MPortal::GetAssetSize()
{
	return mAsset[0]->GetImgSize();
}
