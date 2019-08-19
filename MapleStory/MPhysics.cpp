#include "pch.h"
#include "MPhysics.h"

double const fall_speed = 670;
double const gravity_acc = 2000;
double const walk_speed = 125;



bool GetIntersectPoint(const Gdiplus::PointF& AP1, const Gdiplus::PointF& AP2,
	const Gdiplus::Point& BP1, const Gdiplus::Point& BP2, Gdiplus::PointF* IP)
{
	double t;
	double s;
	double under = (BP2.Y - BP1.Y) * (AP2.X - AP1.X) - (BP2.X - BP1.X) * (AP2.Y - AP1.Y);
	if (under == 0) return false;

	double _t = (BP2.X - BP1.X) * (AP1.Y - BP1.Y) - (BP2.Y - BP1.Y) * (AP1.X - BP1.X);
	double _s = (AP2.X - AP1.X) * (AP1.Y - BP1.Y) - (AP2.Y - AP1.Y) * (AP1.X - BP1.X);

	t = _t / under;
	s = _s / under;

	if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	IP->X = AP1.X + t * (double)(AP2.X - AP1.X);
	IP->Y = AP1.Y + t * (double)(AP2.Y - AP1.Y);

	return true;
}

MPhysics::MPhysics() : m_pRL(nullptr), m_pImgData(nullptr)
{
	vx = 0;
	vy = 1;
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
	//float delta = (_delta);
	
	//	std::cout << Lerp(0, walk_speed, delta) << std::endl;

		//_obj->Offset(Lerp(0, 50, delta), 0);

	//	std::cout << "delta : " << _delta << std::endl;

		//fabsf
	int stab = 0;
	float delta = _delta * 0.001f;
	Gdiplus::PointF pos(_obj->GetPosition().X, _obj->GetPosition().Y);

	if (stab < _delta)
	{
		stab = 0;
	}

	while (stab < _delta)
	{
		stab++;
		if (m_pRL == nullptr)
		{
			Gdiplus::PointF d(vx * walk_speed * delta, vy * fall_speed * delta);
			Gdiplus::PointF posd = pos + d;
			Gdiplus::PointF crd;
			bool bCheck = false;

			for (auto& it : ROAD->m_vRoad)
			{
				if (GetIntersectPoint(pos, posd, it.line1, it.line2, &crd) == true)
				{
					std::cout << "x : " << crd.X << "y : " << crd.Y << std::endl;

					m_pRL = &it;
					bCheck = true;
				}				
			}

			if (!bCheck)
			{
				crd = posd;
				vy = 1;
			}

			pos = crd;
									
			if (m_pRL != nullptr)
			{
				double fx = m_pRL->line2.X - m_pRL->line1.X;
				double fy = m_pRL->line2.Y - m_pRL->line1.Y;

				if (m_pRL->line1.X == m_pRL->line2.X)
				{
					if (fy > 0)
						pos.X += -1.0f;
					else
						pos.X += 1.0f;

					vx = 0;
					m_pRL = nullptr;
				}

				else
				{
					vy = 0;
				}
			}
		}

		else
		{
			double nx = pos.X + vx * walk_speed * delta;
			double ny = pos.Y + vy * fall_speed * delta;

			if (nx > m_pRL->line2.X)
			{
				RoadLine* nxt = nullptr;

				if (m_pRL->nxt)
					nxt = ROAD->GetLine(m_pRL->nxt);

				if (nxt == nullptr)
				{
					nx = m_pRL->line2.X + 1.0f;
					ny = m_pRL->line2.Y;
					vy = 1;
					m_pRL = nullptr;
				}

				else if (nxt->line1.X < nxt->line2.X)
				{
					m_pRL = nxt;

					double fx = m_pRL->line2.X - m_pRL->line1.X;
					double fy = m_pRL->line2.Y - m_pRL->line1.Y;
					double dot = (vx * walk_speed * delta * fx + vy * fall_speed * delta * fy) / (fx * fx + fy * fy);
					
					if(nx < m_pRL->line1.X)
						nx = m_pRL->line1.X;

					ny = m_pRL->line1.Y + dot * fy;
				}

				else if (nxt->line1.Y < nxt->line2.Y)
				{
					nx = m_pRL->line2.X + 1.0f;
					ny = m_pRL->line2.Y;
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

				else if (prev->line1.Y > prev->line2.Y)
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

			pos.X = nx;
			pos.Y = ny;
	//		_obj->SetPosition(nx, ny);
		}
	}

	_obj->SetPosition(pos.X, pos.Y);

}

void MPhysics::Release()
{
}

void MPhysics::SetImgData(IMG_DATA const& _imgdata)
{
	m_pImgData = &_imgdata;
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

/*

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

		if (n1 >= 0 && n1 <= 1 && n2 >= 0 && n2 <= distance && denom < 0)
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
			nx = m_pRL->line2.X - 1.0f;
			ny = m_pRL->line2.Y;
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
*/