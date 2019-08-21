#pragma once

class MSpriteComponent;
class MPhysics;

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



	void SetComponent(Component* _pComp);

	void Hit(int _damage);


	void Move();
	void Jump();
	void Stand();
	void Dead();
	void Skill();
	void Attack();

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
};

