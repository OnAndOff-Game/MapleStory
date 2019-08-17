#pragma once

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

private:

	void LoadData(const std::string& _filename);

private:

	Node* m_pPaser;

	std::string m_strName;

	int m_nHp;
	int m_nMp;
	const MobInfo* m_pMobInfo;

	std::vector<Component*> m_vComponent;	
};

