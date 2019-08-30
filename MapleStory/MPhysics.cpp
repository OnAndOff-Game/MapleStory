#include "pch.h"
#include "MPhysics.h"

double const fall_speed = 200;
double const gravity_acc = 2000;
double const walk_speed = 120;

bool GetIntersectPoint(const Gdiplus::PointF& AP1, const Gdiplus::PointF& AP2,
	const Gdiplus::Point& BP1, const Gdiplus::Point& BP2, Gdiplus::PointF* IP)
{
	double t;
	double s;
	double under = static_cast<double>(BP2.Y - BP1.Y) * (AP2.X - AP1.X) - static_cast<double>(BP2.X - BP1.X) * static_cast<double>(AP2.Y - AP1.Y);
	if (under == 0) return false;

	double _t = static_cast<double>(BP2.X - BP1.X) * static_cast<double>(AP1.Y - BP1.Y) - static_cast<double>(BP2.Y - BP1.Y) * static_cast<double>(AP1.X - BP1.X);
	double _s = static_cast<double>(AP2.X - AP1.X) * static_cast<double>(AP1.Y - BP1.Y) - static_cast<double>(AP2.Y - AP1.Y) * static_cast<double>(AP1.X - BP1.X);

	t = _t / under;
	s = _s / under;

	if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	IP->X = AP1.X + t * static_cast<double>(AP2.X - AP1.X);
	IP->Y = AP1.Y + t * static_cast<double>(AP2.Y - AP1.Y);

	return true;
}

MPhysics::MPhysics() : roadLine(nullptr), m_pJumpRL(nullptr), imgData(nullptr),
velocityX(0.f), velocityY(1.f), isJumping(false), slidingFriction(0), speed(0)
{
	RoadNum = 0;
}

MPhysics::MPhysics(int _fs, int _speed) : roadLine(nullptr), m_pJumpRL(nullptr),
velocityX(0.f), velocityY(1.f), imgData(nullptr), isJumping(false),
slidingFriction(_fs), speed(_speed)
{
	RoadNum = 0;
}

MPhysics::~MPhysics()
{
}

void MPhysics::Init()
{
	speed += walk_speed;
}

void MPhysics::Update(MObject* _obj, float _delta)
{
	int stab = 0;
	float delta = _delta * CONVERT_SECOND * PHYSICS_EXACTVALUE;

	Gdiplus::PointF position(_obj->GetPosition().X, _obj->GetPosition().Y);
	Gdiplus::PointF cross;

	while (stab != STAB_COUNT)
	{
		if (isJumping)
		{
			velocityY += 0.01f;
			m_pJumpRL = roadLine;
			roadLine = nullptr;
		}

		if (roadLine == nullptr)
		{
			Gdiplus::PointF derivative(velocityX * speed * delta, velocityY * fall_speed * delta);
			Gdiplus::PointF localpositionitionDerivative = position + derivative;

			for (auto& it : ROAD->road)
			{
				if (GetIntersectPoint(position, localpositionitionDerivative, it.startLine, it.endLine, &cross) == true)
					if (!(position.Y > it.startLine.Y && position.Y > it.endLine.Y) && &it != m_pJumpRL)
						roadLine = &it;
			}

			if (roadLine != nullptr)
			{
				isJumping = false;
				m_pJumpRL = nullptr;

				if (roadLine->startLine.X == roadLine->endLine.X)
				{
					if (position.Y < roadLine->startLine.Y && position.Y < roadLine->endLine.Y)
					{
						if (velocityX > 0)
							position.X += REVISAL;

						if (velocityX < 0)
							position.X -= REVISAL;
					}
					else
					{
						if (velocityX < 0)
							position.X += REVISAL;

						if (velocityX > 0)
							position.X -= REVISAL;

						velocityX = 0;
					}

					velocityY = 1;
					roadLine = nullptr;
				}
				else
				{
					if (abs(cross.X - position.X) < abs(cross.X))
					{
						position.X += derivative.X;
						position.Y = cross.Y;
					}
					else
						position = cross;

					velocityY = 0;
				}
			}
			else
			{
				position = localpositionitionDerivative;
				if (velocityY > VELOCITY_MAX_Y)
					velocityY = VELOCITY_MAX_Y;
			}
		}

		else
		{
			Gdiplus::PointF derivative(velocityX * speed * delta, velocityY * fall_speed * delta);
			Gdiplus::PointF localpositionitionDerivative = position + derivative;

			if (localpositionitionDerivative.X < roadLine->startLine.X)
			{
				RoadLine* prevLine = ROAD->GetLine(roadLine->prev - 1);

				if (prevLine == nullptr)
				{
					velocityY = 1;
					derivative.Y = velocityY * speed * delta;
					roadLine = nullptr;
				}
				else
				{
					if (prevLine->startLine.X == prevLine->endLine.X)
					{
						if (prevLine->endLine.Y < prevLine->startLine.Y)
						{
							velocityY = 1;
							derivative.Y = velocityY * speed * delta;
							roadLine = nullptr;

						}
						else if (localpositionitionDerivative.Y < prevLine->startLine.Y &&
							localpositionitionDerivative.Y > prevLine->endLine.Y)
						{
							velocityY = VELOCITY_MAX_Y;
							derivative.Y = velocityY * speed * delta;
							velocityX = 0;
							position.X += REVISAL;
							roadLine = nullptr;
						}
						else
						{
							roadLine = prevLine;
							velocityY = 0;
							velocityX = 0;

							position.X += REVISAL;

							derivative.X = 0;
							derivative.Y = 0;
						}
					}
					else if (localpositionitionDerivative.X > prevLine->startLine.X &&
						localpositionitionDerivative.X < prevLine->endLine.X)
					{
						roadLine = prevLine;

						if (roadLine->endLine.Y != roadLine->startLine.Y)
						{
							double x = roadLine->endLine.X - roadLine->startLine.X;
							double y = roadLine->endLine.Y - roadLine->startLine.Y;
							derivative.Y = (y / x) * derivative.X;
						}
					}
				}

			}
			else if (localpositionitionDerivative.X > roadLine->endLine.X)
			{
				RoadLine* nextLine = ROAD->GetLine(roadLine->next - 1);

				if (nextLine == nullptr)
				{
					velocityY = 1;
					derivative.Y = velocityY * speed * delta;
					roadLine = nullptr;
				}
				else
				{
					if (nextLine->startLine.X == nextLine->endLine.X)
					{
						if (nextLine->endLine.Y > nextLine->startLine.Y)
						{
							velocityY = 1;
							derivative.Y = velocityY * speed * delta;
							roadLine = nullptr;
						}
						else if (localpositionitionDerivative.Y > nextLine->startLine.Y &&
							localpositionitionDerivative.Y < nextLine->endLine.Y)
						{
							velocityY = VELOCITY_MAX_Y;
							derivative.Y = velocityY * speed * delta;
							velocityX = 0;
							position.X -= REVISAL;
							roadLine = nullptr;
						}
						else
						{
							roadLine = nextLine;

							velocityY = 0;
							velocityX = 0;

							position.X -= REVISAL;

							derivative.X = 0;
							derivative.Y = 0;
						}
					}
					else if (localpositionitionDerivative.X > nextLine->startLine.X && localpositionitionDerivative.X < nextLine->endLine.X)
					{
						roadLine = nextLine;

						if (roadLine->endLine.Y != roadLine->startLine.Y)
						{
							double x = roadLine->endLine.X - roadLine->startLine.X;
							double y = roadLine->endLine.Y - roadLine->startLine.Y;

							derivative.Y = (y / x) * derivative.X;
						}
					}
				}
			}
			else
			{
				if (roadLine->startLine.X != roadLine->endLine.X && roadLine->endLine.Y != roadLine->startLine.Y)
				{
					double x = roadLine->endLine.X - roadLine->startLine.X;
					double y = roadLine->endLine.Y - roadLine->startLine.Y;
					double px = localpositionitionDerivative.X - roadLine->startLine.X;
					derivative.Y = (y / x) * derivative.X;
				}
			}

			position = position + derivative;

		}

		stab++;
	}

	_obj->SetPosition(position.X, position.Y);

}

void MPhysics::Release()
{
}

void MPhysics::SetJumping(bool _isJumping)
{
	isJumping = _isJumping;
}

bool MPhysics::IsJumping()
{
	if (isJumping || roadLine == nullptr)
		return false;
	else
		return true;
}

bool MPhysics::IsFloor()
{
	if (roadLine == nullptr)
		return false;

	if (roadLine->group != 0)
		return true;

	return false;
}

void MPhysics::SetImgData(IMG_DATA const& _imgData)
{
	imgData = &_imgData;
}

void MPhysics::SetVelocity(float _velocityX, float _velocityY)
{
	velocityX = _velocityX;
	velocityY = _velocityY;
}

void MPhysics::SetVelocityX(float _velocityX)
{
	velocityX = _velocityX;
}

void MPhysics::SetVelocityY(float _velocityY)
{
	velocityY = _velocityY;
}

void MPhysics::SetLevitation()
{
	roadLine = nullptr;
}

float MPhysics::GetVelocityX()
{
	return velocityX;
}

float MPhysics::GetVelocityY()
{
	return velocityY;
}