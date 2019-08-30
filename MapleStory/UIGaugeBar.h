#pragma once

// 게이지바를 나타낼 UI입니다.
class UIGaugeBar : public MObject
{
public:
	UIGaugeBar();
	virtual void Init() override;
	virtual void LoadData(const std::string& _filename) override;
	virtual void Update(float _delta) override;
	void Release();

private:
	Asset* gaugeBarSprite; // 체력, 마력, 경험치의 게이지바 스프라이트
	Asset* gaugeBarGraduationSprite; // 게이지바의 그라데이션 스프라이트
};