#pragma once

struct PORTAL
{
	std::string pn;
	int pt;
	int x;
	int y;
	int tm;
	std::string tn;
};

class MPortal : public MObject
{
public:
	MPortal(const PORTAL& _portaldata);
	~MPortal();

	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);
	void Release();

	bool PortalCollision(Gdiplus::Point& player);

	Gdiplus::Point& GetAssetSize();
	Gdiplus::Rect& GetSize();

public:

	PORTAL PortalData;


private:
	int curAni;
	float curAniTime;
	Asset* mAsset[8];
};