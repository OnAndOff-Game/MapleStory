#include "pch.h"
#include "MRoad.h"

MRoad::MRoad() : bCollision(false)
{
	m_vRoad.clear();
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
				RoadLine rl;
				rl.layer = layer;
				rl.group = group;
				rl.id = std::stoi(o3.GetName());
				rl.line1.X = o3["x1"].GetValueInt();
				rl.line1.Y = o3["y1"].GetValueInt();
				rl.line2.X = o3["x2"].GetValueInt();
				rl.line2.Y = o3["y2"].GetValueInt();
				rl.prv = o3["prev"].GetValueInt();
				rl.nxt = o3["next"].GetValueInt();

				m_vRoad.push_back(rl);
			}
		}
	}

	std::sort(m_vRoad.begin(), m_vRoad.end(),
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

	//for (auto &it : m_vRoad)
	//{
	//	double wd = it.line2.X - it.line1.X;
	//	double ht = it.line2.Y - it.line1.Y;



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
	//	if (m_vRoad[m_vRGroup[cnt].line[i]].line1.X < _pt.X && m_vRoad[m_vRGroup[cnt].line[i]].line2.X > _pt.X)
	//	{
	//	//	std::cout << "좌표 x : " << pt.X << "캐릭 y : " << pt.Y;
	//		return &m_vRoad[m_vRGroup[cnt].line[i]];
	//	}
	//}
	return nullptr;
}

RoadLine* MRoad::GetLine(int _num)
{
	if (_num > m_vRoad.size() || _num < 0)
		return nullptr;
	else
		return &m_vRoad[_num];
}

void MRoad::Render(Gdiplus::Graphics* _mem)
{
	if (bCollision)
	{
		Gdiplus::Pen MPen(Gdiplus::Color(255, 0, 0), 3);
		for (auto& it : m_vRoad)
		{
			_mem->DrawLine(&MPen, it.line1.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2, it.line1.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2,
				it.line2.X - View::viewPort.X + Constants::SCREEN_SIZE_X / 2, it.line2.Y - View::viewPort.Y + Constants::SCREEN_SIZE_Y / 2);
		}
	}
}

void MRoad::Release()
{
	m_vRoad.clear();
}

void MRoad::DrawLine(bool _bdraw)
{
	bCollision = _bdraw;
}
