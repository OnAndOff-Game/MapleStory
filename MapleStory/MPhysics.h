#pragma once

class MObject;

class MPhysics : public Component
{
public:
	
	MPhysics();
	MPhysics(int _fs, int _speed);
	~MPhysics();

	void Init();
	void Update(MObject* _obj, float _delta);
	void Release();


	void SetJump(bool bJumping);
	bool IsJump();

	void SetInfo();
	void SetImgData(IMG_DATA const& _imgdata);
	void SetVelocity(float _vx, float _vy);
	void SetVelocityX(float _vx);
	void SetVelocityY(float _vy);
	void SetLevitation();


	
private:

	RoadLine const* m_pRL;
	RoadLine const* m_pJumpRL;
	IMG_DATA const* m_pImgData;
	float vx, vy;
	int RoadNum;
	bool bJumping;
	


	int fs;
	int speed;
};

