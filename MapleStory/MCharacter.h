#pragma once

class MSpriteComponent;
class MPhysics;
class MState;

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


	void HandleInput(EMAnimType _atype);
	void SetComponent(Component* _pComp);
	

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

private:
	
	bool m_bDie;

	EMAnimType playerState;
	
	bool bFalling;

	ProxyID m_ProxyID;

	Node m_Paser;

	std::string m_strName;

	int m_nHp;
	int m_nMp;

	int m_nSkillCnt;
	int m_nAtkCnt;
	const MobInfo* m_pMobInfo;

	std::vector<Component*> m_vComponent;

	MSpriteComponent* m_pSprites;
	MPhysics* m_pPhysics;


	MState* m_pState;
};

