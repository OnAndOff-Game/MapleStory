#include "pch.h"
#include "View.h"

Gdiplus::PointF View::viewPort = Gdiplus::PointF(0,0);

void View::CameraFollow(Gdiplus::PointF& pt, int speed)
{
	viewPort.X = Lerp(viewPort.X, pt.X, speed);
	viewPort.Y = Lerp(viewPort.Y, pt.Y, speed);
}
