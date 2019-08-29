#include "pch.h"
#include "MRoad.h"

MRoad::MRoad() : bCollision(false)
{
	road.clear();
}

MRoad::~MRoad()
{
}

void MRoad::Init()
{
}

void MRoad::LoadData(Node* pNode)
{
	for (auto o = pNode->begin(); o; o = o++)
	{
		auto layer = std::stoi(o.GetName());
		for (auto o2 = o.begin(); o2; o2 = o2++)
		{
			auto group = std::stoi(o2.GetName());

			for (auto o3 = o2.begin(); o3; o3 = o3++)
			{
				RoadLine localRoadLine;
				localRoadLine.layer = layer;
				localRoadLine.group = group;
				localRoadLine.id = std::stoi(o3.GetName());
				localRoadLine.startLine.X = o3["x1"].GetValueInt();
				localRoadLine.startLine.Y = o3["y1"].GetValueInt();
				localRoadLine.endLine.X = o3["x2"].GetValueInt();
				localRoadLine.endLine.Y = o3["y2"].GetValueInt();
				localRoadLine.prev = o3["prev"].GetValueInt();
				localRoadLine.next = o3["next"].GetValueInt();

				road.push_back(localRoadLine);
			}
		}
	}

	std::sort(road.begin(), road.end(),
		[](RoadLine const& _l1, RoadLine const& _l2) { return _l1.id < _l2.id; });
}

void MRoad::Update(float _delta)
{
}

RoadLine* MRoad::GetLine(Gdiplus::Point& _pt)
{

	//int cnt = 0;
	////MRoadGroup* pTemp = nullptr;
	//int dt = 0;

	//for (auto &it : road)
	//{
	//	double wd = it.endLine.X - it.startLine.X;
	//	double ht = it.endLine.Y - it.startLine.Y;



	//	if (_pt.Y > it..Y && _pt.X > it.colpt1.X && _pt.X < it.colpt2.X)
	//	{
	//		if (_pt.Y - it.colpt1.Y > 0)
	//		{
	//			if (dt == 0)
	//			{
	//				dt = _pt.Y - it.colpt1.Y;
	//			}

	//			else
	//				if (dt > _pt.Y - it.colpt1.Y)
	//				{
	//					dt = _pt.Y - it.colpt1.Y;
	//					cnt++;
	//				}
	//		}
	//	}
	//}

	////std::cout << "캐릭 x : " << _pt.X << "캐릭 y : " << _pt.Y;


	//for (int i = 0; i < m_vRGroup[cnt].line.size(); ++i)
	//{
	//	if (road[m_vRGroup[cnt].line[i]].startLine.X < _pt.X && road[m_vRGroup[cnt].line[i]].endLine.X > _pt.X)
	//	{
	//	//	std::cout << "좌표 x : " << pt.X << "캐릭 y : " << pt.Y;
	//		return &road[m_vRGroup[cnt].line[i]];
	//	}
	//}
	return nullptr;
}

RoadLine* MRoad::GetLine(int _num)
{
	if (_num > road.size() || _num < 0)
		return nullptr;
	else
		return &road[_num];
}

void MRoad::Render(Gdiplus::Graphics* _mem)
{
	if (bCollision)
	{
		Gdiplus::Pen MPen(Gdiplus::Color(255, 0, 0), 3);

		for (auto& it : road)
		{
			_mem->DrawLine(&MPen, it.startLine.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2, it.startLine.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2,
				it.endLine.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2, it.endLine.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2);
		}
	}
}

void MRoad::Release()
{
	road.clear();
}

void MRoad::DrawLine(bool _bdraw)
{
	bCollision = _bdraw;
}
