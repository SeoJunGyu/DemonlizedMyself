#pragma once
#include "GameObject.h"

class Player;
class Button;

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
	sf::Text textStatPoint;

	// 경험치
	sf::RectangleShape expBar;
	sf::RectangleShape expBarbg; //53 53 63
	sf::Text textExp;
	float expPer = 0.f;

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

	// 버튼
	Button* btnStat = nullptr;
	Button* btnEnhance = nullptr;

public:
	StatUiHud(const std::string& name = "");
	virtual ~StatUiHud() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	// Update
	void UpdateExpBar();
};

