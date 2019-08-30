#pragma once

// HUD�� ��׶����Դϴ�.
class UIBackground : public MObject
{
public:
	UIBackground();
	virtual void Init() override;
	virtual void LoadData(const std::string& _filename) override;
	virtual void Update(float _delta) override;
	void Release();

private:
	// baseBackgroundSprite[0] -> ä��, �������� ��׶���
	// baseBackgroundSprite[1] -> ü�¹�, ������ ��׶���
	Asset* baseBackgroundSprite[2];

	const int backgroundSize = 2; // ��׶����� ����
};