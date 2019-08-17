#pragma once

#define SpriteManager ResourceManager::GetInstance()

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
};