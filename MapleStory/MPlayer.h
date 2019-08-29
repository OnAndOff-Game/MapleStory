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

	//const MobInfo* m_pMobInfo;

	std::vector<Component*> m_vComponent;

	MSpriteComponent* m_pSprites;
	//	MPhysics* m_pPhysics;
	MDamageFont* m_pDF;

	std::list<Maple::LADDER_ROPE>* m_pLdRope;

	MState* m_pState;

	Node m_Paser;
	std::string m_strName;
	Gdiplus::Rect m_rcCollision;
	EMAnimType playerState;

	bool	m_bHit;
	bool	m_bCollision;
	DWORD	m_dwHitTick;

	bool m_bDie;
	bool bFalling;

	int m_nHp;
	int m_nMp;

	int m_nSkillCnt;
	int m_nAtkCnt;

	std::list<ISkill*> skills;

	bool bFlag;
};

