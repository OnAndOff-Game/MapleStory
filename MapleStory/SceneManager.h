#pragma once

class SceneManager
{
public:
	SceneManager();

	void LoadScene(const char *pName);
	void LoadScene(int index);
	void RenderScene(Gdiplus::Graphics* _memG);
	void Init();
	void Update(float Delta);
	void SendLButtonDown(UINT nFlags, CPoint point);
	void Release();
	
	Scene* GetCurScene();

	static SceneManager& GetInstance();
private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
};

