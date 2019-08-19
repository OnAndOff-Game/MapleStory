#include "pch.h"
#include "Asset.h"
#include "MSprite.h"

MSprite::MSprite()
{
}

MSprite::MSprite(const SPRDATA& _sprdata,EMRenderType _type) : m_SprData(_sprdata),
m_eRenderType(_type)

{
	m_vImgData.clear();
	m_vAsset.clear();
}

MSprite::~MSprite()
{
}

void MSprite::Init()
{
	std::string filename;

	for (int i = 0; i < m_SprData.cnt; ++i)
	{
		filename =	m_SprData.path + '/' + m_SprData.name + '.';
		
		filename += (i + 48);
		filename += ".png";

		LPIMG_DATA pImgdata = ASSETMGR->GetAssetData(filename);
		
		m_vImgData.push_back(pImgdata);
		m_vAsset.push_back(new Asset(m_eRenderType, filename, *pImgdata));
	}
}

void MSprite::Update(MObject* _obj, float _delta)
{
	m_vAsset[m_nFrame]->Update(_obj, _delta);
}

void MSprite::Release()
{
	m_vImgData.clear();
	
	for (auto it : m_vAsset)
	{
		delete it;
	}
	
	m_vAsset.clear();
}

EMAnimType MSprite::GetAnimType()
{
	return m_SprData.type;
}

std::string& MSprite::GetName()
{
	return m_SprData.name;
}

void MSprite::SetFrame(int _frame)
{
	if (m_nFrame > m_SprData.cnt)
		m_nFrame = m_SprData.cnt;

	else if (_frame < 0)
		m_nFrame = 0;

	else
		m_nFrame = _frame;
}

int MSprite::GetFrame()
{
	return m_SprData.cnt;
}

int MSprite::GetCurrentDelay()
{
	if (m_vImgData[m_nFrame] != nullptr)
		return m_vImgData[m_nFrame]->delay;
	else
		return -1;
}

IMG_DATA const& MSprite::GetCurrentImgData()
{
	return *m_vImgData[m_nFrame];
}

void MSprite::LoadData(const std::string& _name)
{
}

void MSprite::SetAsset(Asset* _asset)
{
	m_vAsset.push_back(_asset);
}

void MSprite::SetFlip(bool _flip)
{
	m_vAsset[m_nFrame]->SetFlip(_flip);
}
