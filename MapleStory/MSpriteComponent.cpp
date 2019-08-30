#include "pch.h"
#include "MSprite.h"
#include "MSpriteComponent.h"

MSpriteComponent::MSpriteComponent()
{
}

MSpriteComponent::MSpriteComponent(const std::string& _filename, EMRenderType _type) : m_eRenderType(_type),
m_nCurrentTime(0), m_nFrame(0), m_bPlaying(true), m_bLooping(true), m_bFlip(false), m_pSprite(nullptr)
{
	m_nSprID = std::stoi(_filename);
}

MSpriteComponent::MSpriteComponent(int _strid, EMRenderType _type) : m_nSprID(_strid), m_eRenderType(_type),
m_nCurrentTime(0), m_nFrame(0), m_bPlaying(true), m_bLooping(true), m_bFlip(false), m_pSprite(nullptr)
{
}

MSpriteComponent::~MSpriteComponent()
{
}

void MSpriteComponent::Init()
{
	int cnt = SPRMGR->GetSpriteDataCnt(m_nSprID);

	for (int i = 0; i < cnt; ++i)
	{
		MSprite* pSpr = new MSprite(SPRMGR->GetSpriteData(m_nSprID, i), m_eRenderType);

		pSpr->Init();

		SpritesMap.insert(std::make_pair(pSpr->GetAnimType(), pSpr));
	}	
}

void MSpriteComponent::Update(MObject* _obj, float _delta)
{
	if (m_pSprite != nullptr)
	{
		if (m_bPlaying)
		{
			m_nCurrentTime += _delta;

			if (m_nCurrentTime >= m_pSprite->GetCurrentDelay())
			{
				if (m_nFrame + 1 < m_pSprite->GetFrame())
					m_nFrame++;
				else
				{
					m_pSprite->AssetReset();

					if (!m_bLooping)
						Stop();
					else
						m_nFrame = 0;
				}
				
				m_nCurrentTime = 0;
				m_pSprite->SetFrame(m_nFrame);
			}
		}
		m_pSprite->SetFlip(m_bFlip);

		m_pSprite->Update(_obj, _delta);
	}
	//imgdata;
}

void MSpriteComponent::Release()
{
	for (auto it : SpritesMap)
	{
		it.second->Release();
		delete it.second;
	}
}

void MSpriteComponent::Play()
{
	m_bPlaying = true;
	m_nFrame = 0;
	m_nCurrentTime = 0;
}

void MSpriteComponent::Stop()
{
	m_bPlaying = false;
	m_nFrame = 0;
	m_nCurrentTime = 0;
}

void MSpriteComponent::Pause()
{
	m_bPlaying = false;
}

void MSpriteComponent::Resume()
{
	m_bPlaying = true;
}

void MSpriteComponent::Reverse()
{
}

void MSpriteComponent::SetCurrentAnim(EMAnimType _type)
{
	if (SpritesMap.find(_type) == SpritesMap.end())
		return;
	
	m_pSprite = SpritesMap.find(_type)->second;

	if (m_pSprite == nullptr)
		m_pSprite = SpritesMap.begin()->second;

	m_nFrame = 0;
}
 
void MSpriteComponent::SetCurrentAnim(EMAnimType _type, int _cnt)
{
	auto anim = SpritesMap.equal_range(_type);

	if (anim.first == anim.second)
		return;

	else
	{
		auto sprite = anim.first;

		for (int i = 0; i < _cnt; ++i)
		{
			sprite++;
		}

		m_pSprite = sprite->second;

		if (m_pSprite == nullptr)
			m_pSprite = SpritesMap.begin()->second;
	}
}

void MSpriteComponent::SetAlpha(float _alpha)
{
	if (m_pSprite != nullptr)
		m_pSprite->SetAlpha(_alpha);
}

void MSpriteComponent::SetRed(float _red)
{
	if (m_pSprite != nullptr)
		m_pSprite->SetRed(_red);
}

IMG_DATA const& MSpriteComponent::GetCurrentImgData()
{
	if (m_pSprite != nullptr)
		return m_pSprite->GetCurrentImgData();
	else
		return SpritesMap.find(EMAnimType::eMAnimType_Moving)->second->GetCurrentImgData();
}

void MSpriteComponent::SetLooping(bool _bLooping)
{
	m_bLooping = _bLooping;
}

void MSpriteComponent::SetFlip(bool _flip)
{
	m_bFlip = _flip;
}
