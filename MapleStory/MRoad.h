#pragma once

class MRoad
{
public:

	MRoad();
	~MRoad();

	void Init();
	void LoadData(class Node* pNode);
	void Update(float _delta);
	RoadLine* GetLine(Gdiplus::Point& _pt);
//	RoadLine* GetLine(Gdiplus::Point& _pt);
	
	void Release();

private:
	
	std::vector<RoadLine>	m_vRoad;
		
};

