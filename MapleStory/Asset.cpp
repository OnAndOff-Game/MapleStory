#include "pch.h"
#include "MapleStory.h"
#include "Asset.h"

Asset::Asset() : img{ nullptr }, fliping{ false }, rendering{ true },
red{ PERCENT_MAX }, alpha{ PERCENT_MAX }, m_pCachedBitmap{ nullptr }
{
}

Asset::Asset(EMRenderType inType, const std::string& inAsset, int inZorder, bool inFixing)
	: fliping{ false }, rendering{ true }, red{ PERCENT_MAX }, alpha{ PERCENT_MAX }
{
	renderType = inType;

	fixing = inFixing;
	zorder = inZorder;

	img = SpriteManager->GetAssetImg(inAsset);

	rect.X = 0;
	rect.Y = 0;
	
	imgSize.X = rect.Width = img->GetWidth();
	imgSize.Y = rect.Height = img->GetHeight();

	customPosition.X = imgSize.X / 2;
	customPosition.Y = imgSize.Y / 2;
	
	m_pCachedBitmap = BmpToCahcedBmp(img, imgSize.X, imgSize.Y);
}

Asset::Asset(EMRenderType inType, const std::string& inAsset, IMG_DATA const& inImgData, bool inFixing)
	: fliping{ false }, rendering{ true }, red{ PERCENT_MAX }, alpha{ PERCENT_MAX }
{
	renderType = inType;

	fixing = inFixing;
	zorder = inImgData.z;

	img = SpriteManager->GetAssetImg(inAsset);

	customPosition = inImgData.origin;

	rect.X = 0;
	rect.Y = 0;

	imgSize.X = rect.Width = img->GetWidth();
	imgSize.Y = rect.Height = img->GetHeight();

	m_pCachedBitmap = BmpToCahcedBmp(img, imgSize.X, imgSize.Y);
}


Asset::Asset(EMRenderType inType, const std::string& inAsset, Gdiplus::Rect& inRect, int inZorder, bool inFixing)
	: fliping{ false }, rendering{ true }, red{ PERCENT_MAX }, alpha{ PERCENT_MAX }
{
	renderType = inType;

	fixing = inFixing;
	zorder = inZorder;

	img = SpriteManager->GetAssetImg(inAsset);

	imgSize.X = img->GetWidth();
	imgSize.Y = img->GetHeight();

	rect = inRect;

	customPosition.X = inRect.Width / 2;
	customPosition.Y = inRect.Height / 2;

	m_pCachedBitmap = BmpToCahcedBmp(img, rect.Width, rect.Height);
}

Asset::~Asset()
{
}

void Asset::Init()
{
	red = alpha = PERCENT_MAX;
	rendering = true;
	fixing = false;
}

void Asset::Update(MObject* _obj, float _delta)
{
	if (rendering)
	{
		if (!fixing)
		{
			rect.X = _obj->Transform.Translation.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2;
			rect.Y = _obj->Transform.Translation.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2;
		}

		else
		{
			rect.X = _obj->Transform.Translation.X + offsetPosition.X;
			rect.Y = _obj->Transform.Translation.Y + offsetPosition.Y;
		}

		if (renderType == EMRenderType::eMRenderType_Object)
		{
			if (rect.X - rect.Width < Constants::SCREEN_SIZE_X &&
				rect.X + rect.Width > 0 &&
				rect.Y - rect.Height < Constants::SCREEN_SIZE_Y &&
				rect.Y + rect.Height > 0)
				BATCHRENDER->BatchDraw(renderType, img, rect, customPosition, zorder, alpha, red, fliping);
		}
		else
		{
			if (rect.X - rect.Width < Constants::SCREEN_SIZE_X &&
				rect.X + rect.Width > 0 &&
				rect.Y - rect.Height < Constants::SCREEN_SIZE_Y &&
				rect.Y + rect.Height > 0)
				BATCHRENDER->BatchDraw(renderType, m_pCachedBitmap, rect, customPosition, zorder, alpha, red, fliping);
		}
		
	}
}

	void Asset::Render(Gdiplus::Graphics * _memG)
	{

	}

	void Asset::Release()
	{	
		if (this->m_pCachedBitmap != nullptr)
			delete m_pCachedBitmap;
		BATCHRENDER->Clear();
	}

	void Asset::SetAlpha(float inAlpha)
	{
		alpha = inAlpha;
	}

	void Asset::SetRed(float inRed)
	{
		red = inRed;
	}

	void Asset::SetRender(bool inRendering)
	{
		rendering = inRendering;
	}

	void Asset::SetFlip(bool inFliping)
	{
		fliping = inFliping;
	}

	void Asset::SetOffset(Gdiplus::Point & inOffsetPosition)
	{
		offsetPosition = inOffsetPosition;
	}

	Gdiplus::Point& Asset::GetImgSize()
	{
		return imgSize;
	}

	Gdiplus::Rect& Asset::GetSize()
	{
		return rect;
	}

	Gdiplus::CachedBitmap* Asset::BmpToCahcedBmp(Gdiplus::Image * inImg, int inSizeX, int inSizeY)
	{
		CClientDC dc(theApp.m_pMainWnd);
		Gdiplus::Graphics G(dc);

		Bitmap* LocalBmp = new Bitmap(inSizeX, inSizeY, &G);
		Gdiplus::Graphics* LocalG = new Gdiplus::Graphics(LocalBmp);
		LocalBmp->RotateFlip(Rotate180FlipY);
		LocalG->DrawImage(inImg, 0, 0, inSizeX, inSizeY);
		CachedBitmap* cachedbmp = new CachedBitmap(LocalBmp, &G);

		delete LocalG;
		delete LocalBmp;
		return cachedbmp;
	}
