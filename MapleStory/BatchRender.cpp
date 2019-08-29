#include "pch.h"
#include "MapleStory.h"
#include "BatchRender.h"

void BatchRender::BatchDraw(EMRenderType _type, Gdiplus::Image* _img, const Gdiplus::Point& _pos, int _z, float _alpha, bool _flip)
{
	if (!bDraw)
		Clear();

	BatchElement element;
	
	element.Pos = _pos;
	element.SizeX = _img->GetWidth();
	element.SizeY = _img->GetHeight();
	element.alpha = _alpha;
	element.bFlip = _flip;
	element.z = _z;
	element.img = _img;

	if (_type == EMRenderType::eMRenderType_Map)
		BatchMap.insert(element);

	else if (_type == EMRenderType::eMRenderType_Object)
		BatchObj.insert(element);
	   
	else if(_type == EMRenderType::eMRenderType_UI)
		BatchUI.insert(element);
}

void BatchRender::BatchDraw(EMRenderType _type, Gdiplus::Image* _img, const Gdiplus::Rect& _rect, const Gdiplus::Point& _origin, int _z, float _alpha, float _red, bool _flip)
{
	if (!bDraw)
		Clear();

	BatchElement element;

	_rect.GetLocation(&element.Pos);
	element.Origin = _origin;
	element.SizeX = _rect.Width;
	element.SizeY = _rect.Height;
	element.alpha = _alpha;
	element.red = _red;
	element.bFlip = _flip;
	element.z = _z;
	element.img = _img;

	if (_type == EMRenderType::eMRenderType_Map)
		BatchMap.insert(element);

	else if (_type == EMRenderType::eMRenderType_Object)
		BatchObj.insert(element);

	else if (_type == EMRenderType::eMRenderType_UI)
		BatchUI.insert(element);
}

void BatchRender::Draw(Gdiplus::Graphics* _view)
{
	//std::cout << "BatchMap : " << BatchMap.size() << std::endl;
	for (auto it : BatchMap)
	{
	//	if(it.z == 1)
		Render(_view, it);
	}

	for (auto it : BatchObj)
	{
		Render(_view, it);
	}

	for (auto it : BatchUI)
	{
		Render(_view, it);
	}

	bDraw = true;
}

void BatchRender::DrawEnd()
{
	bDraw = false;
}

CachedBitmap* BatchRender::BmpToCahcedBmp(Gdiplus::Image* img, int SizeX, int SizeY)
{
	CClientDC dc(theApp.m_pMainWnd);
	Graphics G(dc);

	Bitmap* m_pBmp = new Bitmap(SizeX, SizeY, &G);
	Graphics* pG = new Graphics(m_pBmp);
	pG->DrawImage(img, 0, 0, SizeX, SizeY);
	CachedBitmap* cachedbmp = new CachedBitmap(m_pBmp, &G);

	delete pG;
	delete m_pBmp;
	return cachedbmp;
}

void BatchRender::Render(Gdiplus::Graphics* _view, const BatchElement& _element)
{
	//Gdiplus::Rect Dst(Size.X,Size.Y, m_pImg->GetWidth(), m_pImg->GetHeight());

	DWORD Tick = GetTickCount64();
	DWORD Delta = Tick - PreTick;
	
	if (_element.alpha < 1.0f || _element.bFlip || _element.red > 1.0f)
	{
		Gdiplus::Bitmap bm(_element.img->GetWidth(), _element.img->GetHeight(), PixelFormat32bppARGB);
		Gdiplus::Graphics memG(&bm);
		
		Gdiplus::Rect rc(0, 0, _element.img->GetWidth(), _element.img->GetHeight());
		ColorMatrix colorMatrix = { _element.red, 0.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f, _element.alpha, 0.0f,
									 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		
		ImageAttributes imageAtt;
		imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
			   
		memG.DrawImage(_element.img, rc, 0, 0, _element.img->GetWidth(), _element.img->GetHeight(), Gdiplus::Unit::UnitPixel,
			&imageAtt, 0, nullptr);
			   
		if (_element.bFlip)
		{
			bm.RotateFlip(Rotate180FlipY);

			_view->DrawImage(&bm, Gdiplus::Rect(_element.Pos.X - (_element.img->GetWidth() - _element.Origin.X), _element.Pos.Y - _element.Origin.Y, _element.SizeX, _element.SizeY));
		}

		else
		{
			_view->DrawImage(&bm, Gdiplus::Rect(_element.Pos.X - _element.Origin.X, _element.Pos.Y - _element.Origin.Y, _element.SizeX, _element.SizeY));
		}

	}

	else
	{
		_view->DrawImage(_element.img, Gdiplus::Rect(_element.Pos.X - _element.Origin.X, _element.Pos.Y - _element.Origin.Y, _element.SizeX, _element.SizeY));
		//_view->DrawCachedBitmap(_element.cachedImg, _element.Pos.X - _element.Origin.X, _element.Pos.Y - _element.Origin.Y);
	}

//	if(Delta != 0)
	//	std::cout << "½Ã°£ : " << Delta << std::endl;

	PreTick = Tick;
}


void BatchRender::Clear()
{
	if (!BatchMap.empty())
		BatchMap.clear();

	if (!BatchObj.empty())
		BatchObj.clear();

	if (!BatchUI.empty())
		BatchUI.clear();

	bDraw = true;
}



