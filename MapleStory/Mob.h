#pragma once

class MSpriteComponent;
class MPhysics;
class MState;

class Mob : public MObject
{
public:
	Mob();
	Mob(const std::string& _filename);
	~Mob();

	void Init();
	void Release();

	void Update(float _delta);
	void HandleInput(EMAnimType _atype);
	void Render(Gdiplus::Graphics* _memG);
	void SetComponent(Component* _pComp);


	void Hit(int _damage);

	int GetExp();
	int GetPushed();
	int GetPAtk();
	int GetMAtk();
	int GetLv();

	void Move();
	void Jump();
	void Stand();
	void Dead();
	void Skill(int _Cnt);
	void Attack(int _Cnt);


	Gdiplus::Rect const& GetColRc();

	bool GetFalling() { return bFalling; }
	void SetFalling(bool _bFalling) {bFalling = _bFalling;}

	void LoadData(const std::string& _filename);

	void SetDirection(int dir);



private:
	
	//MobInfo LoadInfo(Node& _node);

public:

	ObjectId objectId;

private:

	float m_MoveTime;
	int m_Direction;

	bool bFalling;


	Node m_Paser;

	std::string m_strName;

	Gdiplus::Rect m_rcCollision;

	int m_nHp;
	int m_nMp;
	
	int m_nSkillCnt;
	int m_nAtkCnt;
	//MobInfo m_MobInfo;


	std::vector<Component*> m_vComponent;
	   
	MSpriteComponent* m_pSprites;
	MPhysics* m_pPhysics;

	//State Patern
	MState* m_pState;


//	MSpriteComponent;
	//MInput;
//	Skill;
};

