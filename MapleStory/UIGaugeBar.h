#pragma once

// �������ٸ� ��Ÿ�� UI�Դϴ�.
class UIGaugeBar : public MObject
{
public:
	UIGaugeBar();
	virtual void Init() override;
	virtual void LoadData(const std::string& _filename) override;
	virtual void Update(float _delta) override;
	void Release();

private:
	Asset* gaugeBarSprite; // ü��, ����, ����ġ�� �������� ��������Ʈ
	Asset* gaugeBarGraduationSprite; // ���������� �׶��̼� ��������Ʈ
};