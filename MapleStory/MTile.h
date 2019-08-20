#pragma once

struct TILE
{
	int x;
	int y;
	std::string u;
	std::string no;
	int zM;
	std::string GetTileName()
	{
		std::string temp = u;
		temp += "." + no + ".png";

		return temp;
	}
};

class MTile : public MObject
{
public:

	MTile();
	MTile(const TILE& _tiledata, Asset* _asset);
	~MTile();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();

public:

	TILE TileData;
	

private:
	
	Asset* mAsset;
};

