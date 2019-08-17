#include "pch.h"
#include "MRoad.h"

MRoad::MRoad()
{
	m_vRGroup.clear();
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
		for (auto o2 = o.begin(); o2; o2 = o2++)
		{					   		
			MRoadGroup group;

			group.layer = std::stoi(o.GetName());
			group.num = std::stoi(o2.GetName());

			for (auto o3 = o2.begin(); o3; o3 = o3++)
			{
				m_vRoad[group.num].line1.X = o3["x1"].GetValueInt();
				m_vRoad[group.num].line1.Y = o3["y1"].GetValueInt();
				m_vRoad[group.num].line2.X = o3["x2"].GetValueInt();
				m_vRoad[group.num].line2.Y = o3["y2"].GetValueInt();
				m_vRoad[group.num].prv	= o3["prev"].GetValueInt();
				m_vRoad[group.num].nxt	= o3["next"].GetValueInt();
							   
				if (m_vRoad[group.num].prv == 0)
					group.Begin = std::stoi(o3.GetName());
				
				if (m_vRoad[group.num].nxt == 0)
					group.End = std::stoi(o3.GetName());


				if (group.line.size() == 0)
				{
					group.colpt1.X = m_vRoad[group.num].line1.X;
					group.colpt1.Y = m_vRoad[group.num].line1.Y;
					group.colpt2.X = m_vRoad[group.num].line2.X;
					group.colpt2.Y = m_vRoad[group.num].line2.Y;
				}

				if (group.colpt1.X > m_vRoad[group.num].line1.X)
					group.colpt1.X = m_vRoad[group.num].line1.X;

				if (group.colpt1.Y > m_vRoad[group.num].line1.Y)
					group.colpt1.Y = m_vRoad[group.num].line1.Y;
				
				if (group.colpt2.X < m_vRoad[group.num].line2.X)
					group.colpt2.X = m_vRoad[group.num].line2.X;

				if (group.colpt2.Y < m_vRoad[group.num].line2.Y)
					group.colpt2.Y = m_vRoad[group.num].line2.Y;

				group.line.push_back(std::stoi(o3.GetName()));
			}
			m_vRGroup.push_back(group);
		}
	}
}

void MRoad::Update(float _delta)
{
}

RoadLine* MRoad::GetLine(Gdiplus::Point& _pt)
{
	MRoadGroup* pTemp = nullptr;
	int dt = 0;

	for (auto it : m_vRGroup)
	{
		if (_pt.Y > it.colpt1.Y && _pt.X > it.colpt1.X && _pt.X < it.colpt2.X)
		{
			if (_pt.Y - it.colpt1.Y > 0)
			{
				if (dt == 0)
				{
					dt = _pt.Y - it.colpt1.Y;
					pTemp = &it;
				}
				else
					if (dt > _pt.Y - it.colpt1.Y)
					{
						dt = _pt.Y - it.colpt1.Y;
						pTemp = &it;
					}
			}
		}
	}

	for (int i = 0; i < pTemp->line.size(); ++i)
	{
		if (m_vRoad[pTemp->line[i]].line1.X > _pt.X && m_vRoad[pTemp->line[i]].line1.X < _pt.X)
			return &m_vRoad[pTemp->line[i]];
	}

	return nullptr;
}

void MRoad::Release()
{
	m_vRGroup.clear();
	m_vRoad.clear();
}
