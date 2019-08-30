#pragma once

// HUD의 백그라운드입니다.
class UIBackground : public MObject
{
public:
	UIBackground();
	virtual void Init() override;
	virtual void LoadData(const std::string& _filename) override;
	virtual void Update(float _delta) override;
	void Release();

private:
	// baseBackgroundSprite[0] -> 채팅, 아이콘의 백그라운드
	// baseBackgroundSprite[1] -> 체력바, 레벨의 백그라운드
	Asset* baseBackgroundSprite[2];

	const int backgroundSize = 2; // 백그라운드의 개수
};