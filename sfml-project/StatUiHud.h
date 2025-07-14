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
};

