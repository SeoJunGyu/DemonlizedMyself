#pragma once
#include "GameObject.h"

class Button;
class Player;

class UiHud :
    public GameObject
{
protected:
	std::string fontId = "fonts/Maplestory_Light.ttf";

	sf::RectangleShape topBack; //상단 UI 배경
	sf::RectangleShape back;

	sf::Text textTime;
	float time;

	//TextGo* textLevel = nullptr;

	// 플레이어 정보
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarbg; //53 53 63
	float per = 0.f;

	sf::Text textLevel;
	sf::Text textExp;
	sf::Text textGold;
	sf::Text textGem;
	sf::Text textHp;

	// 버튼
	Button* btnStat = nullptr;
	Button* btnEnhance = nullptr;
	Button* btnSurrender = nullptr;

	// 스탯 창
	sf::Text statNameStr;
	sf::Text statValueStr;
	sf::Text statLevelStr;
	Button* btnStrUp = nullptr;

	sf::Text statNameDex;
	sf::Text statValueDex;
	sf::Text statLevelDex;
	Button* btnDexUp = nullptr;

	sf::Text statNameAgi;
	sf::Text statValueAgi;
	sf::Text statLevelAgi;
	Button* btnAgiUp = nullptr;

	sf::Text statNameLuk;
	sf::Text statValueLuk;
	sf::Text statLevelLuk;
	Button* btnLukUp = nullptr;

	//수치 정보
	int currentLevel = 1;
	float currentExp = 0.f;
	float maxExp = 100.f;
	int gold = 0;
	int gem = 0;
	int statPoints = 0;

	int strLevel = 0;
	int dexLevel = 0;
	int agiLevel = 0;
	int lukLevel = 0;

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
	void UpdateTextTime(float time);

	// Set
	void SetTextTime(float t);
	void SetTextLevel(int level);
};

