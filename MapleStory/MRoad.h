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
	
	void Release();

private:

	std::map<int, RoadLine> m_vRoad;
	
	std::vector<MRoadGroup> m_vRGroup;
	
//	std::map<int, Group>

//	std::
	//	layer
	//group

};

