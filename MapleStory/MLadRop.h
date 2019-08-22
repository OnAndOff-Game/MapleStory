#pragma once

class MObject;
class MPhysics;

class MLadRop : public MObject
{
public:

	MLadRop();
	MLadRop(Maple::LADDER_ROPE& _lrdata);
	~MLadRop();

	virtual void Init();
	virtual void LoadData(const std::string& _filename) {}
	void		 LoadData(Node& _node);
	virtual void Update(float _delta);


private:

	Maple::LADDER_ROPE m_stLRData;


};

