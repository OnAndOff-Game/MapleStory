#include "pch.h"
#include "View.h"

Gdiplus::PointF View::viewPort;
Gdiplus::Point View::Target;

void View::CameraFollow(int speed)
{
	Gdiplus::PointF temp;
	temp.X = Lerp(viewPort.X, Target.X, speed*0.001);
	temp.Y = Lerp(viewPort.Y, Target.Y, speed*0.001);
	viewPort = temp;
}
