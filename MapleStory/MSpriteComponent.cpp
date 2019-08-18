#include "pch.h"
#include "MSprite.h"
#include "MSpriteComponent.h"

MSpriteComponent::MSpriteComponent()
{
}

MSpriteComponent::MSpriteComponent(const std::string& _filename, EMRenderType _type) : m_eRenderType(_type)
{
	m_nSprID = std::stoi(_filename);
	m_bPlaying = m_bLooping = true;
	m_nCurrentTime = 0;
	m_nFrame = 0;
}

MSpriteComponent::MSpriteComponent(int _strid, EMRenderType _type) : m_nSprID(_strid), m_eRenderType(_type)
{
	m_bPlaying = m_bLooping = true;
	m_nCurrentTime = 0;
	m_nFrame = 0;
}

MSpriteComponent::~MSpriteComponent()
{
}

void MSpriteComponent::Init()
{
	int cnt = SPRMGR->GetSprDataCnt(m_nSprID);

	for (int i = 0; i < cnt; ++i)
	{
		MSprite* pSpr = new MSprite(SPRMGR->GetSprData(m_nSprID, i), m_eRenderType);

		pSpr->Init();

		m_mSprites.insert(std::make_pair(pSpr->GetAnimType(), pSpr));
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
					if (!m_bLooping)
						Stop();
					else
						m_nFrame = 0;
				
				m_nCurrentTime = 0;
				m_pSprite->SetFrame(m_nFrame);
			}
		}
	}

	m_pSprite->Update(_obj, _delta);
}

void MSpriteComponent::Release()
{
	for (auto it : m_mSprites)
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
	m_pSprite = m_mSprites.find(_type)->second;

	m_nFrame = 0;
}

void MSpriteComponent::SetCurrentAnim(EMAnimType _type, int _cnt)
{
	auto anim = m_mSprites.equal_range(_type);

	if (anim.first == anim.second)
		return;

	else
	{
		auto spr = anim.first;
		for (int i = 0; i < _cnt; ++i)
		{
			spr++;
		}

		m_pSprite = spr->second;
	}
}

void MSpriteComponent::SetLooping(bool _bLooping)
{
	m_bLooping = _bLooping;
}
