#pragma once

#include "Singleton.h"

struct BatchCompare
{
	bool operator() (const BatchElement& lhs, const BatchElement& rhs) const
	{
#if 0
		if (lhs.a < rhs.a)
			return 1;
		else if (lhs.a > rhs.a)
			return;

		if (lhs.b < rhs.b)
			return 1;

		return;
#endif
		return ((lhs.z < rhs.z) || ((lhs.z == rhs.z) && (lhs.z < rhs.z)));
	}

};

class BatchRender : public Singleton<BatchRender>
{
public:

	void BatchDraw(EMRenderType _type, Gdiplus::Image* _img, const Gdiplus::Point& _pos, int _z, float _alpha = 1.0f, bool _flip = false);
	void BatchDraw(EMRenderType _type, Gdiplus::Image* _img, const Gdiplus::Rect& _rect, const Gdiplus::Point& _origin, int _z, float _alpha = 1.0f, float _red = 1.0f, bool _flip = false);


	void Draw(Gdiplus::Graphics* _view);
	void DrawEnd();

	void Clear();

private:

		void Render(Gdiplus::Graphics* _view, const BatchElement& _element);

private:

	bool bDraw;

	std::multiset<BatchElement, BatchCompare> BatchMap;
	std::multiset<BatchElement, BatchCompare> BatchObj;
	std::multiset<BatchElement, BatchCompare> BatchUI;

	DWORD PreTick;
};

#define BATCHRENDER BatchRender::GetInstance()
