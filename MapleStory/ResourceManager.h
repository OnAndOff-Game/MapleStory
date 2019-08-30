#pragma once

#define SpriteManager ResourceManager::GetInstance()
#define SoundManager ResourceManager::GetInstance()

using namespace FMOD;

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	Gdiplus::Image* GetAssetImg(std::string _name);

	void Release();

private:

	Gdiplus::Image* LoadAssetImg(std::string _name);

private:
	   
	std::unordered_map <size_t, Gdiplus::Image*> m_mAssetImg;


	// 사운드 부분
public:
	void InitSound();
	void LoadBackGroundSound(std::string BgmPath);
	void LoadSound();
	void PlaySound(int _type);
	void StopSound();
	void ReleaseSound();
private:
	void SoundErrorCheck();

	std::string curBgSound;
	System* soundSystem;
	std::vector<Sound*> music;
	std::vector<Channel*> soundChannel;
	FMOD_RESULT soundResult;
};