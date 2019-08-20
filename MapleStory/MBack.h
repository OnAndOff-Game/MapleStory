#pragma once
struct BACK
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

class MBack : public MObject
{
public:
	MBack(const BACK& _backdata, Asset* _asset);
	~MBack();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();
	Gdiplus::Rect& GetSize();

public:

	BACK BackData;


private:

	Asset* mAsset;
};

