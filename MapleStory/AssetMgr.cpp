#include "pch.h"
#include "AssetMgr.h"

AssetMgr::AssetMgr()
{
	m_mAssetData.clear();
}

AssetMgr::~AssetMgr()
{
	if (m_mAssetData.empty())
		m_mAssetData.clear();
}

void AssetMgr::UnLoadAssetData(const std::string& _assetname)
{
	std::hash<std::string> hashKey;
		
	m_mAssetData.erase(hashKey(_assetname));
}

void AssetMgr::LoadAssetData(const std::string& _filename)
{
}

void AssetMgr::SetAssetData(IMG_DATA& _data)
{
	std::hash<std::string> hash_key;
	   
	m_mAssetData.insert(std::make_pair(hash_key(_data.filename), _data));
}

const IMG_DATA& AssetMgr::operator[](const std::string& _key)
{
	std::hash<std::string> hashkey;
	IMG_DATA pImgData;
		
	auto it = m_mAssetData.find(hashkey(_key));

	if (it == m_mAssetData.end())
		throw "error";
	//else
	//	pImgData = &;

	return it->second;
}

LPIMG_DATA AssetMgr::GetAssetData(const std::string& _assetname)
{
	std::hash<std::string> hash_key;

	LPIMG_DATA pImgData = nullptr;

	auto it = m_mAssetData.find(hash_key(_assetname));

	if (it == m_mAssetData.end())
		return pImgData;
	else
		pImgData = &it->second;

	return pImgData;	
}
