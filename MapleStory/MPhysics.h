#pragma once

#define VELOCITY_MAX_Y 3
#define STAB_COUNT 10

const float REVISAL = 1.0f;
const float CONVERT_SECOND = 0.001f;
const float PHYSICS_EXACTVALUE = 0.1f;
const float FRAMESPEED = 4.0f;

class MObject;

class MPhysics : public Component
{
public:
	
	MPhysics();
	MPhysics(int _fs, int _speed);
	~MPhysics();

	virtual void Init() override;
	virtual void Update(MObject* _obj, float _delta) override;
	virtual void Release() override;
	
	void SetJumping(bool _isJumping);
	bool IsJumping();
	bool IsFloor();

	void SetInfo();
	void SetImgData(IMG_DATA const& _imgData);
	void SetVelocity(float _velocityX, float _velocityY);
	void SetVelocityX(float _velocityX);
	void SetVelocityY(float _velocityY);
	void SetLevitation();

	float GetVelocityX();
	float GetVelocityY();
	
private:

	RoadLine const* roadLine;
	RoadLine const* m_pJumpRL;
	IMG_DATA const* imgData;

	float velocityX, velocityY;
	int RoadNum;
	bool isJumping;

	int slidingFriction;
	int speed;
};

