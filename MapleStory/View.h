#pragma once

class View
{
public:
	static void CameraFollow(int speed);
	static Gdiplus::PointF viewPort;
	static Gdiplus::Point Target;
};