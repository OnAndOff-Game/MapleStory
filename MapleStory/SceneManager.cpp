#include "pch.h"
#include "SceneManager.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager cm;
	return cm;
}

SceneManager::SceneManager()
	: CurScene(nullptr)
{
	mScene.push_back(new GameScene("GameScene"));
	mScene.push_back(new MainScene("MainScene"));

}

void SceneManager::LoadScene(const char *pName)
{
	for (auto& it : mScene)
	{
		if (!it->GetName().CompareNoCase(CString(pName)))
		{
			CurScene = it;
			CurScene->Init();
		}
	}
}

void SceneManager::LoadScene(int index)
{
	CurScene =  mScene[index];
	CurScene->Init();
}

void SceneManager::RenderScene(Gdiplus::Graphics* _memG)
{
	if (CurScene == nullptr) return;
	if (_memG == nullptr) return;
	
	CurScene->Render(_memG);
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}

void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	CurScene->LeftButtonDown(nFlags, point);
}

void SceneManager::Release()
{
	for (auto it : mScene)
	{
		it->Release();
		delete it;
	}
}

void SceneManager::Init()
{
	if (CurScene == nullptr) return;
	CurScene->Init();
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;
	CurScene->Update(Delta);
}