#pragma once

class TempObj : public MObject
{
public:

	TempObj();
	TempObj(const Maple::OBJECT& _objdata, Asset* _asset);
	~TempObj();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();

public:
	
	Maple::OBJECT ObjData;

private:

	Asset* mAsset;
};

