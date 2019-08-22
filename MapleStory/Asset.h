#pragma once

class Asset : public Component
{
public:
	Asset();
	Asset(EMRenderType _type, const std::string& _assetname, int _z = 0, bool _billboard = false);
	Asset(EMRenderType _type, const std::string& _assetname, IMG_DATA const& _imgdata, bool _billboard = false);
	Asset(EMRenderType _type, const std::string& _assetname, Gdiplus::Rect& _size, int _z = 0, bool _billboard = false);
	~Asset();
	void Init();
	void Update(MObject* _obj, float _delta);
	void Render(Gdiplus::Graphics* _memG);
	void Release();
	
	//void			SetAssetData(const std::string& _assetname);
	//IMG_DATA const*	GetAssetData() const ;

	void SetAlpha(float _alpha);
	void SetRed(float _r);
	void SetAlphablending();

	void SetFlip(bool _flip) { bFlip = _flip; }

	void SetRotate(bool _bRotate);
	void SetDrawPoint();
	void SetScale();
	
	Gdiplus::Point& GetImgSize();
	Gdiplus::Rect& GetSize();
	Gdiplus::Rect& GetCollisionBounding();
	

private:

	EMRenderType	m_eType;

	Gdiplus::Image* m_pImg;
	Gdiplus::Point CustomPos;
	Gdiplus::Point ImgSize;

	bool bBillBoard;
	int z;
	float Alpha;
	float Red;
	bool bFlip;
	bool bRender;
	Gdiplus::Rect rect;
	   	
	//IMG_DATA const* m_pImgDB;
};

