#include "pch.h"
#include "ObjectMgr.h"

//void AssetMgr::SetAssetData(IMG_DATA& _data)
//{
//	std::hash<std::string> hash_key;
//
//	m_mAssetData.insert(std::make_pair(hash_key(_data.filename), _data));
//}
//
//const IMG_DATA& AssetMgr::operator[](const std::string& _key)
//{
//	std::hash<std::string> hashkey;
//	LPIMG_DATA pImgData;
//
//	auto it = m_mAssetData.find(hashkey(_key));
//
//	if (it == m_mAssetData.end())
//		throw "error";
//	else
//		pImgData = &it->second;
//
//	return *pImgData;
//}
//
//LPIMG_DATA AssetMgr::GetAssetData(const std::string& _assetname)
//{
//	std::hash<std::string> hash_key;
//
//	LPIMG_DATA pImgData = nullptr;
//
//	auto it = m_mAssetData.find(hash_key(_assetname));
//
//	if (it == m_mAssetData.end())
//		return pImgData;
//	else
//		pImgData = &it->second;
//
//	return pImgData;
//}

