#pragma once
class ISkill : public MObject
{
public:
	void Init();
	void LoadData(const std::string& _filename);
	void Update(float _delta);

private:

	MSpriteComponent* m_pSprites;
};