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

void ResourceManager::InitSound()
{
	System_Create(&pFmod);
	pFmod->init(10, FMOD_INIT_NORMAL, 0);
}

void ResourceManager::LoadSound(std::string BgmPath)
{
	if (!curBgSound.compare(BgmPath))
		return;
	curBgSound = BgmPath;
	ch[0]->stop();
	pFmod->update();
	r = pFmod->createSound(curBgSound.c_str(), FMOD_LOOP_NORMAL, NULL, &music[0]);
	r = pFmod->createSound("Sound/Game/Portal.mp3", FMOD_DEFAULT, NULL, &music[2]);
	r = pFmod->createSound("Sound/Game/Jump.mp3", FMOD_DEFAULT, NULL, &music[1]);
}

void ResourceManager::PlaySound(int _type)
{
	bool bIsPlaying = false;

	if (_type == 0)
	{
	ch[_type]->isPlaying(&bIsPlaying);
	if (bIsPlaying)
		return;
	}
		
	r = pFmod->playSound(music[_type], NULL, false, &ch[_type]);
}

void ResourceManager::ReleaseSound()
{
	
}
