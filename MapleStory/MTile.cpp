#include "pch.h"
#include "Asset.h"
#include "MObject.h"
#include "MTile.h"

MTile::MTile() : mAsset(nullptr)
{
	m_eObjType = EMObjType::eMObjType_Map;
}

MTile::MTile(const TILE& _tiledata,Asset* _asset)
{
	m_eObjType = EMObjType::eMObjType_Map;
	TileData = _tiledata;
	mAsset = _asset;
}

MTile::~MTile()
{
}

void MTile::Init()
{
}

void MTile::LoadData(const std::string& _filename)
{
	//m_pAsset = SpriteManager->GetAssetImg(_filename);
}

void MTile::Update(float _delta)
{
	mAsset->Update(this, _delta);
}

void MTile::Release()
{
	if (mAsset != nullptr)
	{
		delete mAsset;
		mAsset = nullptr;
	}
}

Gdiplus::Point& MTile::GetAssetSize()
{
	return mAsset->GetImgSize();
}
