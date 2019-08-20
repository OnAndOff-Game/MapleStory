#pragma once

struct OBJECT
{
	std::string oS;
	std::string l0;
	std::string l1;
	std::string l2;
	int x;
	int y;
	int z;
	int f;
	int zM;
};

class TempObj : public MObject
{
public:

	TempObj();
	TempObj(const OBJECT& _objdata, Asset* _asset);
	~TempObj();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();

public:
	
	OBJECT ObjData;

private:
	Asset* mAsset;
};

