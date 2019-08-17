#pragma once

class View
{
public:
	static void CameraFollow(Gdiplus::PointF& pt, int speed);
	static Gdiplus::PointF viewPort;
};