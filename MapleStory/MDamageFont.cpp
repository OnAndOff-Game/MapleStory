#include "pch.h"
#include "Asset.h"
#include "MDamageFont.h"

MDamageFont::MDamageFont()
{
	m_dwTick = 0;
	Init();
}

MDamageFont::MDamageFont(int _sprname)
{
}

MDamageFont::~MDamageFont()
{
}

void MDamageFont::Init()
{	   
	for (int i = 0; i < 10; ++i)
	{
		std::string path = "Font/101.";
		path += std::to_string(i);
		path += ".png";

		m_pFont[i] = new Asset(EMRenderType::eMRenderType_UI, path);
	}

}

void MDamageFont::LoadData(const std::string& _filename)
{
}

void MDamageFont::Update(float _delta)
{
	Gdiplus::Point pt = Transform.Translation;

	m_dwTick += _delta;
	int i = 0;

	if (m_dwTick > ERARER_TIME)
	{
		m_dwTick = 0;

		for (auto& it : m_lDamage)
		{
			m_pFont[it]->SetAlpha(1.0f);
		}

		m_lDamage.clear();
	}

	Transform.Translation.X -= 50 * m_lDamage.size() / 2 - 40;

	for (auto& it : m_lDamage)
	{
		Transform.Translation.X += 50;

		if (m_dwTick > BLENDING_TIME)
		{
			m_pFont[it]->SetAlpha(1.0 - Lerp(0, 1, (m_dwTick - BLENDING_TIME) * 0.001));
		}

		m_pFont[it]->Update(this, _delta);	
	}

	Transform.Translation = pt;
}

void MDamageFont::Release()
{

	for (int i = 0; i < 10; ++i)
	{
		if (m_pFont[i] != nullptr)
		{
			m_pFont[i]->Release();
			delete m_pFont[i];
			m_pFont[i] = nullptr;
		}
	}

	m_lDamage.clear();
}

void MDamageFont::SetDamage(int _damage, Gdiplus::Point& pos)
{
	m_strDamage = std::to_string(_damage);
	
	for(int i = 0; i < m_strDamage.length(); ++i)
	{
		m_lDamage.push_back(m_strDamage[i] - 48);
	}

	Transform.Translation = pos;
}
