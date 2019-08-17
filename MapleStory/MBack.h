#pragma once
class MBack : public MObject
{
public:
	MBack(const Maple::BACK& _backdata, Asset* _asset);
	~MBack();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();
	Gdiplus::Rect& GetSize();

public:

	Maple::BACK BackData;


private:

	Asset* mAsset;
};

