#pragma once

class MObject;

class MPhysics : public Component
{
public:
	
	MPhysics();
	~MPhysics();

	void Init();
	void Update(MObject* _obj, float _delta);
	void Release();

	void SetImgData(IMG_DATA const& _imgdata);
	void SetVelocity(float _vx, float _vy);
	void SetVelocityX(float _vx);


	
private:
	RoadLine const* m_pRL;
	IMG_DATA const* m_pImgData;
	float vx, vy;
	int RoadNum;
};

