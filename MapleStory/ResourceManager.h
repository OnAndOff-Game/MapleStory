#pragma once

#define SpriteManager ResourceManager::GetInstance()
#define SoundManager ResourceManager::GetInstance()

using namespace FMOD;

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	
	Gdiplus::Image* GetAssetImg(std::string _name);

	void Release();

private:

	Gdiplus::Image* LoadAssetImg(std::string _name);

private:
	   
	std::unordered_map <size_t, Gdiplus::Image*> m_mAssetImg;

	// 사운드 부분

public:

	void InitSound();
	void LoadSound(std::string BgmPath);
	void PlaySound(int _type);
	void StopSound();
	void ReleaseSound();
private:
	void SoundErrorCheck();
	std::string curBgSound;
	System* pFmod;
	Channel* ch[10];
	Sound* music[10];
	FMOD_RESULT r;
};