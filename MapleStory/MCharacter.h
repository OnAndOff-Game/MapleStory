#pragma once

class MSpriteComponent;
class MPhysics;
class MState;
class ISkill;
class MDamageFont;
//struct LADDER_ROPE;

class MCharacter : public MObject
{
public:
	MCharacter();
	MCharacter(const std::string& _filename);
	~MCharacter();

	virtual void Init() override;
	virtual void Update(float _delta) override;
	void Render(Gdiplus::Graphics* _memG);
	void Release();

	void GetLadderRope(std::list<Maple::LADDER_ROPE>& _ladderrope);
	void HandleInput(EMAnimType _atype);
	void SetComponent(Component* _pComp);

	void Revision();
	bool IsJump();

	Gdiplus::Rect const& GetCollisionRect();

	void HitDamage(int _damage);
	void SetLevitation();

	bool IsCollision();

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
	MPhysics* physics;
	ObjectId objectId;

	int m_nHp;
	int m_nMp;
	int m_nMaxHp;
	int m_nMaxMp;
private:
	
	//const MobInfo* m_pMobInfo;

	std::vector<Component*> component;

	MSpriteComponent* m_pSprites;
	MDamageFont* m_pDF;

	std::list<Maple::LADDER_ROPE>* m_pLdRope;

	MState* m_pState;

	Node* m_Paser;
	std::string m_strName;
	Gdiplus::Rect collisionRect;
	EMAnimType playerState;

	bool	m_bHit;
	bool	m_bCollision;
	DWORD	m_dwHitTick;

	bool m_bDie;
	bool bFalling;
	   	

	int skillCnt;
	int attackCnt;
	
	bool bFlag;
};

