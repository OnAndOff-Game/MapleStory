#include "pch.h"
#include "Asset.h"
#include "MBack.h"



MBackground::MBackground(const BACKGROUND& _backdata, Asset* _asset)
{
	BackData = _backdata;
	mAsset = _asset;
	m_eObjType = EMObjType::eMObjType_Map;
}

MBackground::~MBackground()
{
}

void MBackground::Init()
{
}

void MBackground::LoadData(const std::string& _filename)
{
}

void MBackground::Update(float _delta)
{
	mAsset->Update(this, _delta);
}

void MBackground::Release()
{
	if (mAsset != nullptr)
	{
		delete mAsset;
		mAsset = nullptr;
	}
}


Gdiplus::Point& MBackground::GetAssetSize()
{
	return mAsset->GetImgSize();
}

Gdiplus::Rect& MBackground::GetSize()
{
	return mAsset->GetSize();
}
