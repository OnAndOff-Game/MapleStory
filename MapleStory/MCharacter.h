#pragma once


class MCharacter : public MObject
{
public:
	void Init();
	void Update(float _delta);
	void Render(Gdiplus::Graphics* _memG);

	void Hit(int _damage);

	void Move();
	void Jump();
	void Down();
	void Dead();

private:

	int m_nHp;
	int m_nMp;

	bool m_bDie;


};

