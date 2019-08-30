#pragma once

class Asset;

class MDamageFont : public MObject
{
public:

	MDamageFont();
	MDamageFont(int _sprname);
	~MDamageFont();

	virtual void Init();
	virtual void LoadData(const std::string& _filename);
	virtual void Update(float _delta);
	void Release();

	void SetDamage(int _damage, Gdiplus::Point& pos);

private:

	int m_nSprName;
	std::string m_strDamage;

	Asset* m_pFont[10];

	std::list<int> m_lDamage;

	DWORD m_dwTick;
};

