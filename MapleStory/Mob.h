#pragma once

class MSpriteComponent;

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

private:

	void LoadData(const std::string& _filename);

private:

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
//	MSpriteComponent;
	//MInput;
//	Skill;
};

