#pragma once

class MainScene : public Scene
{
public:
	SCENE_CONSTRUCTOR

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* _memG);

private:
};