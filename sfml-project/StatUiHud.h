#pragma once
#include "GameObject.h"

class Player;

class StatUiHud :
    public GameObject
{
protected:
	std::string fontId = "fonts/Maplestory_Light.ttf";

	Player* player = nullptr;

	sf::RectangleShape back;

	//레벨, 경험치, 경험치바, 스탯 포인트, 스탯 텍스트, 스탯 레벨, 스탯 업 버튼
	//스탯 < - > 강화 전환 버튼
	sf::Text textLevel;
	sf::Text textNameStatPoint;
	sf::Text textStatPoint;

	// 경험치
	sf::RectangleShape expBar;
	sf::RectangleShape expBarbg; //53 53 63
	sf::Text textExp;
	float expPer = 0.f;

	// 스탯 창
	sf::RectangleShape strBack;
	sf::RectangleShape dexBack;
	sf::RectangleShape agiBack;
	sf::RectangleShape lukBack;

	sf::Text textStr;
	sf::Text textValueStr;
	sf::Text textLevelStr;

	sf::Text textDex;
	sf::Text textValueDex;
	sf::Text textLevelDex;

	sf::Text textAgi;
	sf::Text textValueAgi;
	sf::Text textLevelAgi;

	sf::Text textLuk;
	sf::Text textValueLuk;
	sf::Text textLevelLuk;

public:
	StatUiHud(const std::string& name = "");
	virtual ~StatUiHud() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::RectangleShape GetStrBack() const { return strBack; }
	sf::RectangleShape GetDexBack() const { return dexBack; }
	sf::RectangleShape GetAgiBack() const { return agiBack; }
	sf::RectangleShape GetLukBack() const { return lukBack; }

	// Update
	void UpdateExpBar();
	void UpdateStat();

	// Set
	void SetStat();
};

