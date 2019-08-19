#pragma once

class MTile : public MObject
{
public:

	MTile();
	MTile(const Maple::TILE& _tiledata, Asset* _asset);
	~MTile();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();

public:

	Maple::TILE TileData;
	

private:
	
	Asset* mAsset;
};

