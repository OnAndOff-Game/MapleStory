#pragma once

class MInput : public Component
{
public:
	void Init();
	void Update(DWORD _elapsedTime);
	void Render(Gdiplus::Graphics* _memG);

};

