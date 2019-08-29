#pragma once

class MPlayer : public MObject
{
public:

	MPlayer() {}
	~MPlayer() {}
	
	void Init();
	void Update(float _delta);
	void Render(Gdiplus::Graphics* _memG);
	
private:

};

