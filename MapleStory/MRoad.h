#pragma once

class MRoad : public Singleton<MRoad>
{
public:

	MRoad();
	~MRoad();

	void Init();
	void LoadData(class Node* pNode);
	void Update(float _delta);
	RoadLine* GetLine(Gdiplus::Point& _pt);
	RoadLine* GetLine(int _num);

	void Render(Gdiplus::Graphics* _mem);
	
	void Release();

public:
	std::vector<RoadLine>	m_vRoad;

	bool bCollision;
		
};

#define ROAD MRoad::GetInstance()
