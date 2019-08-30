#include "pch.h"
#include "Asset.h"
#include "TempObj.h"

TempObj::TempObj() : mAsset(nullptr)
{
	m_eObjType = EMObjType::eMObjType_Obj;

}

TempObj::TempObj(const OBJECT& _objdata, Asset* _asset)
{
	m_eObjType = EMObjType::eMObjType_Obj;
	ObjData = _objdata;
	mAsset = _asset;
}

TempObj::~TempObj()
{
}

void TempObj::Init()
{
}

void TempObj::LoadData(const std::string& _filename)
{
	//m_pAsset = SpriteManager->GetAssetImg(_filename);
}

void TempObj::Update(float _delta)
{
	mAsset->Update(this, _delta);
}

void TempObj::Release()
{
	if (mAsset != nullptr)
	{
		mAsset->Release();
		delete mAsset;
		mAsset = nullptr;
	}
}

Gdiplus::Point& TempObj::GetAssetSize()
{
	return mAsset->GetImgSize();
}