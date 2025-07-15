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

	//����, ����ġ, ����ġ��, ���� ����Ʈ, ���� �ؽ�Ʈ, ���� ����, ���� �� ��ư
	//���� < - > ��ȭ ��ȯ ��ư
	sf::Text textLevel;
	sf::Text textStatPoint;

	// ����ġ
	sf::RectangleShape expBar;
	sf::RectangleShape expBarbg; //53 53 63
	sf::Text textExp;
	float expPer = 0.f;

	// ���� â
	sf::RectangleShape strBack;
	sf::RectangleShape dexBack;
	sf::RectangleShape agiBack;
	sf::RectangleShape lukBack;

	sf::Text textStr;
	sf::Text textValueStr;
	sf::Text textLevelStr;
	Button* btnStrUp = nullptr;

	sf::Text textDex;
	sf::Text textValueDex;
	sf::Text textLevelDex;
	Button* btnDexUp = nullptr;

	sf::Text textAgi;
	sf::Text textValueAgi;
	sf::Text textLevelAgi;
	Button* btnAgiUp = nullptr;

	sf::Text textLuk;
	sf::Text textValueLuk;
	sf::Text textLevelLuk;
	Button* btnLukUp = nullptr;

	// ��ư
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
	void SetStat();
};

