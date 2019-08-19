#include "pch.h"
#include "MPhysics.h"

double const fall_speed = 670;
double const gravity_acc = 2000;
double const walk_speed = 125;

MPhysics::MPhysics() : m_pRL(nullptr)
{

	vx = vy = 0.0f;
	RoadNum = 0;
}

MPhysics::~MPhysics()
{
}

void MPhysics::Init()
{
}

void MPhysics::Update(MObject* _obj, float _delta)
{
	float delta = _delta / 3;

	if (m_pRL == nullptr)
	{
		vy = 1;
		Gdiplus::Point pos = _obj->GetPosition();

		double dx1 = vx * delta;
		double dy1 = vy * delta;
		double distance = 1;
		double nnx = pos.X + dx1, nny = pos.Y + dy1;

		for (auto& it : ROAD->m_vRoad)
		{
			double dx2 = it.line2.X - it.line1.X;
			double dy2 = it.line2.Y - it.line1.Y;
			double dx3 = pos.X - it.line1.X;
			double dy3 = pos.Y - it.line1.Y;
			double denom = dx1 * dy2 - dy1 * dx2;
			double n1 = (dx1 * dy3 - dy1 * dx3) / denom;
			double n2 = (dx2 * dy3 - dy2 * dx3) / denom;

			if(n1 >= 0 && n1 <= 1 && n2 >= 0 && n2 <= distance && denom < 0)
				if (dx2 > 0)
				{
					nnx = pos.X + n2 * dx1;
					nny = pos.Y + n2 * dy1;
					distance = n2;
					m_pRL = &it;
				}
		}

		_obj->SetPosition(nnx, nny);

		if (m_pRL != nullptr)
		{
			double fx = m_pRL->line2.X - m_pRL->line1.X;
			double fy = m_pRL->line2.Y - m_pRL->line1.Y;

			if (m_pRL->line1.X == m_pRL->line2.X)
			{
				_obj->Offset(0, 1);
				m_pRL = nullptr;
			}
			
			else if (m_pRL->line1.X > m_pRL->line2.X)
			{
				if (fy > 0)
					_obj->Offset(1, 0);
				else
					_obj->Offset(-1, 0);

				m_pRL = nullptr;
			}
			else
			{
				if (vy > 5)
					vy = 5;
			}

			double dot = (vx * fx + vy * fy) / (fx * fx + fy * fy);
			vx = dot * fx;
			vy = dot * fy;
		}
	}

	else
	{
		Gdiplus::Point pos = _obj->GetPosition();

		double nx = pos.X + vx * delta;
		double ny = pos.Y + vy * delta;

		if (nx > m_pRL->line2.X)
		{
			RoadLine* nxt = ROAD->GetLine(m_pRL->nxt);
			if (nxt != nullptr)
			{
				nx = m_pRL->line2.X + 1.0f;
				ny = m_pRL->line2.Y;
				m_pRL = nullptr;
			}

			else if (nxt->line1.X < nxt->line2.X)
			{
				m_pRL = nxt;
				
				double fx = m_pRL->line2.X - m_pRL->line1.X;
				double fy = m_pRL->line2.Y - m_pRL->line1.Y;
				double dot = (vx * fx + vy * fy) / (fx * fx + fy * fy);
				
				nx = m_pRL->line1.X;
				ny = m_pRL->line1.Y;

				vx = dot * fx;
				vy = dot * fy;
			}

			else if (nxt->line1.Y > nxt->line2.Y)
			{
				nx = nxt->line2.X - 1.0f;
				ny = nxt->line2.Y;
				vx = 0; vy = 0;
			}

			else
			{
				nx = m_pRL->line2.X + 1.0f;
				ny = m_pRL->line2.Y;
				m_pRL = nullptr;
			}
		}

		else if (nx < m_pRL->line1.X)
		{
			RoadLine* prev = ROAD->GetLine(m_pRL->prv);

			if (prev != nullptr)
			{
				nx = m_pRL->line1.X - 1.0f;
				ny = m_pRL->line1.Y;
				m_pRL = nullptr;
			}

			else if (prev->line1.X < prev->line2.X)
			{
				m_pRL = prev;
				double fx = m_pRL->line2.X - m_pRL->line1.X;
				double fy = m_pRL->line2.Y - m_pRL->line1.Y;
				double dot = (vx * fx + vy * fy) / (fx * fx + fy * fy);
				nx = m_pRL->line2.X;
				ny = m_pRL->line2.Y;
				vx = dot * fx;
				vy = dot * fy;
			}

			else if (prev->line1.Y < prev->line2.Y)
			{
				nx = m_pRL->line1.X + 1.0f;
				ny = m_pRL->line1.Y;
				vx = 0;
				vy = 0;
			}

			else
			{
				nx = m_pRL->line1.X - 1.0f;
				ny = m_pRL->line1.Y;
				m_pRL = nullptr;
			}
		}
		_obj->SetPosition(nx, ny);	
	}


}

void MPhysics::Release()
{
}

void MPhysics::SetVelocity(float _vx, float _vy)
{
	vx = _vx;
	vy = _vy;
}

void MPhysics::SetVelocityX(float _vx)
{
	vx = _vx;
}
