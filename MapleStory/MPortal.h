#pragma once

struct PORTAL
{
	int x;
	int y;
};


class MPortal : public MObject
{
public:
	MPortal(const PORTAL& _portaldata, Asset* _asset);
	~MPortal();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	Gdiplus::Point& GetAssetSize();

public:

	PORTAL PortalData;


private:

	Asset* mAsset;
};
