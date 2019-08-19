#pragma once

class MSprite : public Component
{
public:

	MSprite();
	MSprite(const SPRDATA& _sprdata, EMRenderType _type);
	~MSprite();

	void Init();
	void Update(MObject* _obj, float _delta);
	void Release();

	EMAnimType GetAnimType();
	std::string& GetName();

	void SetFrame(int _frame);
	int GetFrame();

	int GetCurrentDelay();
	IMG_DATA const& GetCurrentImgData();

	//void SetAnim(const std::string& _anim);
	void SetAsset(Asset* _asset);
	void SetFlip(bool _flip);

	void LoadData(const std::string& _name);

public:

	EMRenderType m_eRenderType;
		
private:
	
	SPRDATA m_SprData;

	std::vector<IMG_DATA*> m_vImgData;

	std::vector<Asset*> m_vAsset;

	int m_nFrame;

	//Gdiplus::Point ImgSize;
	//Gdiplus::Point ImgUV;
	//Gdiplus::Image* ImageTexture;
};

