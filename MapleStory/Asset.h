#pragma once

class Asset : public Component
{
public:
	Asset();
	Asset(EMRenderType inType, const std::string& inAsset, int inZorder = 0, bool inFixing = false);
	Asset(EMRenderType inType, const std::string& inAsset, IMG_DATA const& inImgData, bool inFixing = false);
	Asset(EMRenderType inType, const std::string& inAsset, Gdiplus::Rect& _size, int inZorder = 0, bool inFixing = false);
	~Asset();
	
	void Init();
	void Update(MObject* _obj, float _delta);
	void Render(Gdiplus::Graphics* _memG);
	void Release();

	void SetAlpha(float inAlpha);
	void SetRed(float inRed);
	
	void SetRender(bool inRendering);
	void SetFlip(bool inFliping);
	void SetOffset(Gdiplus::Point& inOffsetPosition);
	
	Gdiplus::Point& GetImgSize();
	Gdiplus::Rect& GetSize();
	
private:
	// 비트맵을 캐시비트맵으로 바꿔줍니다.
	Gdiplus::CachedBitmap* BmpToCahcedBmp(Gdiplus::Image* inImg, int inSizeX, int inSizeY);

private:

	EMRenderType	renderType;

	Gdiplus::CachedBitmap* m_pCachedBitmap;
	Gdiplus::Image* img;

	Gdiplus::Rect rect;
	
	Gdiplus::Point customPosition;
	Gdiplus::Point imgSize;
	Gdiplus::Point offsetPosition;

	float alpha;
	float red;

	int zorder;

	bool fixing;
	bool fliping;
	bool rendering;  	
};

