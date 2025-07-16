#pragma once
#include "GameObject.h"

class ButtonGo;
class Player;

class UiHud :
    public GameObject
{
protected:
	std::string fontId = "fonts/Maplestory_Light.ttf";

	Player* player = nullptr;

	sf::Sprite playerIcon;
	std::string iconTexId = "graphics/Worrior_Icon.png";

	sf::RectangleShape topBack; //상단 UI 배경
	sf::RectangleShape goldBack;
	sf::RectangleShape gemBack;

	sf::Sprite Gold;
	sf::Sprite Gem;
	std::string texIdGold = "graphics/Gold.png";
	std::string texIdGem = "graphics/Gem.png";

	sf::Sprite iconEnemyHealth;
	sf::Sprite iconHealth;
	std::string texIdEnemyIcon = "graphics/Enemy.png";
	std::string texIdHealth = "graphics/Player.png";

	sf::Text textTime;
	float time;

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

	// Monster HpBar
	sf::RectangleShape monsterHpBar;
	sf::RectangleShape monsterHpBarbg; //53 53 63
	float monsterHpPer = 0.f;
	int totalMaxHp = 0;
	int totalCurrentHp = 0;

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

	void SetTotalHp(int currentHp, int MaxHp);

	sf::RectangleShape GetHpBarBg() const { return playerHpBarbg; }
};

