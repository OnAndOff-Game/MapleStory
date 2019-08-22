#pragma once

class MSpriteComponent;
class MPhysics;
class MState;
//struct LADDER_ROPE;

class MCharacter : public MObject
{
public:
	MCharacter();
	MCharacter(const std::string& _filename);
	~MCharacter();

	void Init();
	void Update(float _delta);
	void Render(Gdiplus::Graphics* _memG);
	void Release();

	void GetLadderRope(std::list<Maple::LADDER_ROPE>& _ladderrope);
	void HandleInput(EMAnimType _atype);
	void SetComponent(Component* _pComp);

	Gdiplus::Rect const& GetColRc();

	void HitDamage(int _demage);
	void SetLevitation();

	void Move();
	void Jump();
	bool Stand();
	void Hit();
	void Die();
	void Skill();
	void Attack();
	void Prone();
	void Ladder();
	void Rope();

	void LoadData(const std::string& _filename);

public:

	ProxyID m_ProxyID;

private:


	const MobInfo* m_pMobInfo;

	std::vector<Component*> m_vComponent;

	MSpriteComponent* m_pSprites;
	MPhysics* m_pPhysics;

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
};

