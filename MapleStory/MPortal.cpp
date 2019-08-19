#include "pch.h"
#include "MPortal.h"


MPortal::MPortal(const PORTAL& _portaldata, Asset* _asset)
{
	PortalData = _portaldata;
	mAsset = _asset;
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
	mAsset->Update(this, _delta);
}

void MPortal::Release()
{
	if (mAsset != nullptr)
	{
		delete mAsset;
		mAsset = nullptr;
	}
}

Gdiplus::Point& MPortal::GetAssetSize()
{
	return mAsset->GetImgSize();
}
