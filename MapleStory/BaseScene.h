#pragma once

#define SCENE_CONSTRUCTOR using Scene::Scene;

class Scene
{
public:
	Scene(const char* SceneName) : Name(SceneName) {}

	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* _memG);
	virtual void Release();
	virtual void LeftButtonDown(UINT nFlags, CPoint point);

public:
	CString GetName();

private:
	bool bLoop;
	CString Name;
};