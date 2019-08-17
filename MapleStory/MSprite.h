#pragma once

class MSprite
{
public:

	MSprite();
	MSprite(const SPRDATA& _sprdata);
	~MSprite();

	void Init();
	void Update(DWORD _dwElsape);

	void SetAnim(const std::string& _anim);
	void SetAsset(Asset* _asset);

	void LoadData(const std::string& _name);
		

private:
	
	SPRDATA m_SprData;

//	IMG_DATA

	std::vector<Asset*> m_vAsset;

	Gdiplus::Point ImgSize;
	Gdiplus::Point ImgUV;
	Gdiplus::Image* ImageTexture;
};

