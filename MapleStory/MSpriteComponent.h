#pragma once

class MSpriteComponent : public Component
{
public:

	void Init();
	void Update(MObject* _obj, DWORD _elapsedTime);


	int GetCurFrame();

	//Animation State
	void Play();
	void Stop();
	void Pause();
	void Resume();
	void Reverse();

	void SetSpriteAnim(class MSprite* _Sprite);

	//
	bool IsLooping() const;
	//bool 
private:

	MSprite* m_pSpriteAnim;

	std::vector<MSprite*> m_vSprites;

	int m_nFrame;
	int m_nCurFrame;

	bool m_bLooping;
	bool m_bPlaying;

	float m_fFrameUpdateSec;
	float m_fPlayRate;


};

