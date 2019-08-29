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

	void DrawLine(bool _bdraw);

public:
	std::vector<RoadLine>	road;

	bool bCollision;
		
};

#define ROAD (MRoad::GetInstance())
