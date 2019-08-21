#pragma once

class MSpriteComponent;
class MPhysics;

class Mob : public MObject
{
public:
	Mob();
	Mob(const std::string& _filename);
	~Mob();

	void Init();
	void Release();

	void Update(float _delta);
	void Render(Gdiplus::Graphics* _memG);
	void SetComponent(Component* _pComp);


	void Hit(int _damage);

	int GetExp();
	int GetPAtk();
	int GetMAtk();
	int GetLv();

	void Move();
	void Jump();
	void Stand();
	void Dead();
	void Skill();
	void Attack();
	
	bool GetFalling() { return bFalling; }
	void SetFalling(bool _bFalling) {bFalling = _bFalling;}

	void LoadData(const std::string& _filename);

private:


	void LoadInfo(Node _node);

private:

	bool bFalling;

	ProxyID m_ProxyID;

	Node m_Paser;

	std::string m_strName;

	int m_nHp;
	int m_nMp;
	
	int m_nSkillCnt;
	int m_nAtkCnt;
	MobInfo m_MobInfo;

	std::vector<Component*> m_vComponent;
	   
	MSpriteComponent* m_pSprites;
	MPhysics* m_pPhysics;
//	MSpriteComponent;
	//MInput;
//	Skill;
};

