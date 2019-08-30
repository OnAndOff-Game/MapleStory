#include "pch.h"
#include "MapleStory.h"
#include "Asset.h"

Asset::Asset()
{
	//m_pImgDB = nullptr;
}

Asset::Asset(EMRenderType _type, const std::string& _assetname, int _z, bool _billboard)
{
	m_eType = _type;
	bFlip = false;
	bRender = true;
	bBillBoard = _billboard;
	z = _z;

	m_pImg = SpriteManager->GetAssetImg(_assetname);
	//SetAssetData(_imgname);

	rect.X = 0;
	rect.Y = 0;
	ImgSize.X = rect.Width = m_pImg->GetWidth();
	ImgSize.Y = rect.Height = m_pImg->GetHeight();
	Red = Alpha = 1.0f;
	CustomPos.X = ImgSize.X / 2;
	CustomPos.Y = ImgSize.Y / 2;

	m_pCachedBitmap = BmpToCahcedBmp(m_pImg, ImgSize.X, ImgSize.Y);
}

Asset::Asset(EMRenderType _type, const std::string& _assetname, IMG_DATA const& _imgdata, bool _billboard)
{
	m_eType = _type;
	bFlip = false;
	bRender = true;
	bBillBoard = _billboard;
	z = _imgdata.z;
	CustomPos = _imgdata.origin;

	m_pImg = SpriteManager->GetAssetImg(_assetname);
	//SetAssetData(_imgname);

	rect.X = 0;
	rect.Y = 0;
	ImgSize.X = rect.Width = m_pImg->GetWidth();
	ImgSize.Y = rect.Height = m_pImg->GetHeight();
	Red = Alpha = 1.0f;

	m_pCachedBitmap = BmpToCahcedBmp(m_pImg,ImgSize.X,ImgSize.Y);
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
	Red = Alpha = 1.0f;
	CustomPos.X = _size.Width / 2;
	CustomPos.Y = _size.Height / 2;

	m_pCachedBitmap = BmpToCahcedBmp(m_pImg, rect.Width, rect.Height);
}

Asset::~Asset()
{
}

void Asset::Init()
{
	Red = Alpha = 1.0f;
	bRender = true;
}

void Asset::Update(MObject* _obj, float _delta)
{
	if (bRender)
	{
		if (!bBillBoard)
		{
			rect.X = _obj->Transform.Translation.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2;
			rect.Y = _obj->Transform.Translation.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2;
		}

		else
		{
			rect.X = _obj->Transform.Translation.X + offsetPosition.X;
			rect.Y = _obj->Transform.Translation.Y + offsetPosition.Y;
		}

		if (m_eType == EMRenderType::eMRenderType_Object)
		{

			if (rect.X - rect.Width < Constants::SCREEN_SIZE_X &&
				rect.X + rect.Width > 0 &&
				rect.Y - rect.Height < Constants::SCREEN_SIZE_Y &&
				rect.Y + rect.Height > 0)
				BATCHRENDER->BatchDraw(m_eType, m_pImg, rect, CustomPos, z, Alpha, Red, bFlip);
		}
		else
		{
			if (rect.X - rect.Width < Constants::SCREEN_SIZE_X &&
				rect.X + rect.Width > 0 &&
				rect.Y - rect.Height < Constants::SCREEN_SIZE_Y &&
				rect.Y + rect.Height > 0)
				BATCHRENDER->BatchDraw(m_eType, m_pCachedBitmap, rect, CustomPos, z, Alpha, Red, bFlip);
		}
	}
}

void Asset::Render(Gdiplus::Graphics* _memG)
{

}

void Asset::Release()
{
	//if (m_pImg != nullptr)
	//{
	//	delete m_pImg;
	//	m_pImg = nullptr;
	//}
	if (m_pCachedBitmap != nullptr)
	{
		delete m_pCachedBitmap;
		m_pCachedBitmap = nullptr;
	}
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

void Asset::SetRed(float _r)
{
	Red = _r;
}

void Asset::SetOffset(Gdiplus::Point& InOffsetPosition)
{
	offsetPosition = InOffsetPosition;
}

Gdiplus::Point& Asset::GetImgSize()
{
	return ImgSize;
}

Gdiplus::Rect& Asset::GetSize()
{
	return rect;
}

Gdiplus::CachedBitmap* Asset::BmpToCahcedBmp(Gdiplus::Image* img, int SizeX, int SizeY)
{
	CClientDC dc(theApp.m_pMainWnd);
	Graphics G(dc);

	Bitmap* m_pBmp = new Bitmap(SizeX, SizeY, &G);
	Graphics* pG = new Graphics(m_pBmp);
	m_pBmp->RotateFlip(Rotate180FlipY);
	pG->DrawImage(img, 0, 0, SizeX, SizeY);
	CachedBitmap* cachedbmp = new CachedBitmap(m_pBmp, &G);

	delete pG;
	delete m_pBmp;
	return cachedbmp;
}
