#include "pch.h"
#include "MSprite.h"

MSprite::MSprite()
{
}

MSprite::MSprite(const SPRDATA& _sprdata) : m_SprData(_sprdata)
{

}

MSprite::~MSprite()
{
}

void MSprite::Init()
{
	m_SprData.sprname;
	m_SprData.name;
	m_SprData.cnt;
}

void MSprite::Update(DWORD _dwElsape)
{

}

void MSprite::LoadData(const std::string& _name)
{
	//m_pSprData;
}
void MSprite::SetAsset(Asset* _asset)
{
	m_vAsset.push_back(_asset);
}
