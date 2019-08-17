#pragma once


class AssetMgr : public Singleton<AssetMgr>
{
public:

	AssetMgr();
	~AssetMgr();

	void LoadAssetData(const std::string& _filename);
	void UnLoadAssetData(const std::string& _name);

	LPIMG_DATA GetAssetData(const std::string& _assetname);
	void SetAssetData(IMG_DATA& _data);

	const IMG_DATA& operator[](const std::string&);

private:

	std::unordered_map<size_t, IMG_DATA> m_mAssetData;

	//std::
};

#define ASSETMGR AssetMgr::GetInstance()