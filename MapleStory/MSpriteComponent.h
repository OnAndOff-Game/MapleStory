#pragma once

class MSprite;

class MSpriteComponent : public Component
{
public:
	MSpriteComponent();
	MSpriteComponent(const std::string& _filename,EMRenderType _type);
	MSpriteComponent(int _strid, EMRenderType _type);
	~MSpriteComponent();

	void Init();
	void Update(MObject* _obj, float _delta);
	void Release();

	int GetCurFrame();

	//Animation State
	void Play();
	void Stop();
	void Pause();
	void Resume();
	void Reverse();

	void SetCurrentAnim(EMAnimType _type);
	void SetCurrentAnim(EMAnimType _type, int _cnt);
	void SetSpriteAnim(MSprite* _Sprite);

	//
	void SetLooping(bool _bLooping);
	bool IsLooping() const;
	//bool 
private:
	
	std::multimap<EMAnimType, MSprite*> m_mSprites;

	EMRenderType m_eRenderType;

	MSprite* m_pSprite;

	int m_nSprID;

	int m_nFrame;

	bool m_bLooping;
	bool m_bPlaying;
	
	float m_nCurrentTime;

	float m_fFrameUpdateSec;
	float m_fPlayRate;
};

