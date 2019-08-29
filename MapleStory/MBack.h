#pragma once
struct BACKGROUND
{
	int x;
	int y;
	int rx;
	int ry;
	int type;
	int cx;
	int cy;
	std::string bS;
	std::string no;
	int a;
	int front;
	int ani;
	int f;
};

class MBackground : public MObject
{
public:
	MBackground(const BACKGROUND& _backdata, Asset* _asset);
	~MBackground();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();
	Gdiplus::Rect& GetSize();

public:

	BACKGROUND BackData;


private:

	Asset* mAsset;
};

