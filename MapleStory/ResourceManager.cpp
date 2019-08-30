#include "pch.h"
#include "ResourceManager.h"
#include <io.h>
#include <cstring>


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
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
		it.second = nullptr;
	}

	m_mAssetImg.clear();
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
	System_Create(&soundSystem);
	soundSystem->init(Sound_Cnt, FMOD_INIT_NORMAL, 0);
}

void ResourceManager::LoadBackGroundSound(std::string BgmPath)
{
	if (!curBgSound.compare(BgmPath))
		return;
	music[Sound_BackGround]->release();

	curBgSound = BgmPath;
	soundResult = soundSystem->createSound(curBgSound.c_str(), SoundType::Sound_BackGround, NULL, &music[Sound_BackGround]);
}

void ResourceManager::LoadSound()
{
	const char* str[] = { 
		"Sound/Bgm00/GoPicnic.mp3",
		"Sound/Game/Jump.mp3",
		"Sound/Game/Portal.mp3",
		"Sound/Game/Jump.mp3" };

	for (int i = 0; i < Sound_Cnt; i++)
	{
		Sound* Temp;
		soundResult = soundSystem->createSound(str[i], i, NULL, &Temp);
		if (soundResult == FMOD_RESULT::FMOD_OK)
		{
			music.push_back(Temp);
		}
	}
	soundChannel.resize(Sound_Cnt, nullptr);
}

void ResourceManager::PlaySound(int _type)
{
	if (_type == SoundType::Sound_BackGround)
	{
	bool backGroundPlaying = false;
	soundChannel[_type]->isPlaying(&backGroundPlaying);
	if (backGroundPlaying)
		return;
	}
		
	soundResult = soundSystem->playSound(music[_type], NULL, false, &soundChannel[_type]);
	SoundErrorCheck();
}

void ResourceManager::StopSound()
{
}

void ResourceManager::ReleaseSound()
{
	for (int i = 0; i < Sound_Cnt; i++)
	{
		music[i]->release();
	}
}

void ResourceManager::SoundErrorCheck()
{
	if (soundResult != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", soundResult, FMOD_ErrorString(soundResult));
		exit(-1);
	}
}