#pragma once
class MObject
{
public:

	virtual void Init() = 0;
	virtual void LoadData(const std::string& _filename) = 0;
	virtual void Update(float _delta) = 0;
	//virtual void Render(Gdiplus::Graphics* _memG) = 0;

	void SetPosition(const Gdiplus::Point& _pt);
	void SetPosition(int x, int y);
	Gdiplus::Point& GetPosition();

	void Offset(const Gdiplus::Point& _pt);
	void Offset(int x, int y);
	
	//don't Using Function 
	bool IsSelected() const { return false; }

public:

	MTransform	Transform;
};

