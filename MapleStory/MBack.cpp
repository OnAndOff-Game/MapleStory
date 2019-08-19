#include "pch.h"
#include "MBack.h"
#include "Asset.h"



MBack::MBack(const BACK& _backdata, Asset* _asset)
{
	BackData = _backdata;
	mAsset = _asset;
}

MBack::~MBack()
{
}

void MBack::Init()
{
}

void MBack::LoadData(const std::string& _filename)
{
}

void MBack::Update(float _delta)
{
	mAsset->Update(this, _delta);
}

void MBack::Release()
{
	if (mAsset != nullptr)
	{
		delete mAsset;
		mAsset = nullptr;
	}
}


Gdiplus::Point& MBack::GetAssetSize()
{
	return mAsset->GetImgSize();
}

Gdiplus::Rect& MBack::GetSize()
{
	return mAsset->GetSize();
}
