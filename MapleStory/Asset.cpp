#include "pch.h"
#include "Asset.h"

Asset::Asset()
{
	//m_pImgDB = nullptr;
}

Asset::Asset(EMRenderType _type, const std::string& _imgname, int _z, bool _billboard)
{
	m_eType = _type;
	bFlip = false;
	bRender = true;
	bBillBoard = _billboard;
	z = _z;

	m_pImg = SpriteManager->GetAssetImg(_imgname);
	//SetAssetData(_imgname);

	rect.X = 0;
	rect.Y = 0;
	ImgSize.X = rect.Width = m_pImg->GetWidth();
	ImgSize.Y = rect.Height = m_pImg->GetHeight();
	Alpha = 1.0f;
}

Asset::Asset(EMRenderType _type, const std::string& _imgname, Gdiplus::Rect& _size, int _z, bool _billboard)
{
	m_eType = _type;
	bFlip = false;
	bRender = true;
	bBillBoard = _billboard;
	z = _z;

	m_pImg = SpriteManager->GetAssetImg(_imgname);
	//SetAssetData(_imgname);
	ImgSize.X = m_pImg->GetWidth();
	ImgSize.Y = m_pImg->GetHeight();
	rect = _size;
	Alpha = 1.0f;
	Pos.X = _size.X;
	Pos.Y = _size.Y;
}

Asset::~Asset()
{
}

void Asset::Init()
{
}

void Asset::Update(MObject* _obj, float _delta)
{
	if (bRender)
	{
		if (!bBillBoard)
		{
			rect.X = _obj->Transform.Translation.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2; // + 카메라 X
			rect.Y = _obj->Transform.Translation.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2; // + 카메라 Y
		}

		else
		{
			rect.X = _obj->Transform.Translation.X;
			rect.Y = _obj->Transform.Translation.Y;
		}

		if (rect.X - rect.Width < Constants::SCREEN_SIZE_X  &&
			rect.X + rect.Width > 0 &&
			rect.Y - rect.Height< Constants::SCREEN_SIZE_Y &&
			rect.Y + rect.Height > 0)
			BATCHRENDER->BatchDraw(m_eType, m_pImg, rect, z, Alpha, bFlip);

	}
}

void Asset::Render(Gdiplus::Graphics* _memG)
{

}

void Asset::Release()
{
}

//void Asset::SetAssetData(const std::string& _assetname)
//{
//	IMG_DATA* pData = ASSETMGR->GetAssetData(_assetname);
//	
//	if (pData != nullptr)
//	{
//		m_pImgDB = pData;
//
//		m_pImg = SpriteManager->GetAssetImg(m_pImgDB->filename);	
//	}
//}

//IMG_DATA const* Asset::GetAssetData() const
//{
//	if (m_pImgDB != nullptr)
//		return m_pImgDB;
//
//	return nullptr;
//}

void Asset::SetAlpha(float _alpha)
{
	Alpha = _alpha;
}

Gdiplus::Point& Asset::GetImgSize()
{
	return ImgSize;
}

Gdiplus::Rect& Asset::GetSize()
{
	return rect;
}
