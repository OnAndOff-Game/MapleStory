#include "pch.h"
#include "ResourceManager.h"
#include <io.h>
#include <cstring>


ResourceManager::ResourceManager()
{
}

Image* ResourceManager::GetAssetImg(std::string _name)
{
	std::hash<std::string> hash_key;

	Image* pImg = nullptr;
	
	auto it = m_mAssetImg.find(hash_key(_name));

	if (it == m_mAssetImg.end())
		pImg = LoadAssetImg(_name);
	else
		pImg = it->second;

	return pImg;
}

void ResourceManager::Release()
{
	for (auto it : m_mAssetImg)
	{
		delete it.second;
	}
}

Image* ResourceManager::LoadAssetImg(std::string _name)
{
	std::wstring file;// (A2W(_name.c_str()));
	file.assign(_name.begin(), _name.end());
	Image* img = new Image(file.c_str());
	std::hash<std::string> hash_key;
	//S - > WSº¯È¯ 
	
	m_mAssetImg.insert(std::make_pair(hash_key(_name), img));

	return img;
}
