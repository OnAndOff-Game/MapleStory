#include "pch.h"
#include "Asset.h"
#include "Mob.h"
#include "MPortal.h"


MPortal::MPortal(const PORTAL& _portaldata)
{
	m_eObjType = EMObjType::eMO_Obj;
	PortalData = _portaldata;

	for (int i = 0; i < 8; i++)
	{
		std::string path = "Portal/";
		path += "pv.";
		path += (i + 48);
		path += ".png";
		IMG_DATA data;
		Gdiplus::Image* img = SpriteManager->GetAssetImg(path);
		data.origin.X = img->GetWidth() / 2;
		data.origin.Y = img->GetHeight() -5 ;
		data.z = 4;
		mAsset[i] = new Asset(EMRenderType::eMR_Map,path,data);
	}
	curAni = 0;
	curAniTime = 0;
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

bool MPortal::PortalCollision(Gdiplus::Point& player)
{
	if (player.X - 10 < GetPosition().X &&
		player.X + 10 > GetPosition().X &&
		player.Y - 10 < GetPosition().Y &&
		player.Y + 10 > GetPosition().Y)
		return true;
	return false;
}

Gdiplus::Point& MPortal::GetAssetSize()
{
	return mAsset[0]->GetImgSize();
}