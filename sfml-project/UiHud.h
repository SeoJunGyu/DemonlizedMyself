#pragma once
#include "GameObject.h"

class ButtonGo;
class Player;
class SceneGame;

class UiHud :
    public GameObject
{
protected:
	std::string fontId = "fonts/Maplestory_Light.ttf";

	Player* player = nullptr;

	sf::RectangleShape topBack; //상단 UI 배경
	sf::RectangleShape goldBack;
	sf::RectangleShape gemBack;

	sf::Text textTime;
	float time;

	//TextGo* textLevel = nullptr;

	// 플레이어 정보
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarbg; //53 53 63
	float hpPer = 0.f;
	sf::Text textHp;

	sf::Text textLevel;
	sf::Text textGold;
	sf::Text textGem;

	sf::RectangleShape expBar;
	sf::RectangleShape expBarbg; //53 53 63
	float expPer = 0.f;

	//ButtonGo* btnSurrender = nullptr;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	// Update
	void UpdateHpBar();
	void UpdateExpBar();
	void UpdateTextTime(float time);

	// Set
	void SetTextTime(float t);
	void SetTextLevel(int level);
	void SetTextReward(int gold, int gem);

	//void SetBtnSurrender(ButtonGo* btn) { btnSurrender = btn; }
	//void SetSurrender();
};

