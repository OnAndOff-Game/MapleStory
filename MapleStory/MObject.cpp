#include "pch.h"
#include "MObject.h"

void MObject::SetPosition(const Gdiplus::Point& _pt)
{
	Transform.Translation = _pt;
}

void MObject::SetPosition(int _x, int _y)
{
	Transform.Translation.X = _x;
	Transform.Translation.Y = _y;
}

Gdiplus::Point& MObject::GetPosition()
{
	return Transform.Translation;
}

void MObject::Offset(const Gdiplus::Point& _pt)
{
	Transform.Translation = Transform.Translation + _pt;
}

void MObject::Offset(int _x, int _y)
{
	Transform.Translation.X += _x;
	Transform.Translation.Y += _y;
}
