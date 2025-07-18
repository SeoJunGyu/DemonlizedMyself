#pragma once
#include "Scene.h"

class SpriteGo;
class Player;
class Monster;
class UiHud;
class StatUiHud;
class ButtonGo;

class SceneGame :
    public Scene
{
protected:
	Player* player = nullptr;
	UiHud* uiHud = nullptr;
	StatUiHud* statUi = nullptr;

	// Monster
	std::list<Monster*> monsterList;
	std::list<Monster*> monsterPool;
	int maxSpawn = 20; //�ִ� ���� ��
	int spawnCount = 0;
	float spawnSpace = 150.f; //���� ����
	float groupSpace = 300.f; //4���� ��� �� �׷� ����
	int groupSize = 4; //����� �� �׷� �� ���� ��

	int totalCurrentHp = 0;
	int totalMaxHp = 0;

	// Background
	std::vector<SpriteGo*> backList;
	std::list<SpriteGo*> groundList;
	int backCount = 0;

	// Button
	ButtonGo* btnSurrender = nullptr;
	sf::Sprite iconBtnSurrender;
	std::string texIdIconBtnSurrender = "graphics/flag.png";

	ButtonGo* btnStrUp = nullptr;
	ButtonGo* btnDexUp = nullptr;
	ButtonGo* btnAgiUp = nullptr;
	ButtonGo* btnLukUp = nullptr;

	ButtonGo* btnStatReset = nullptr;

	// Fade In Out
	sf::RectangleShape fadeRect;
	float fadeAlpha = 100.f;
	bool fadeIn = false;
	bool fadeOut = false;
	float fadeInterval = 3.0f;
	float fadeTimer = 0.0f;

	// CameraShake
	sf::Vector2f originalViewCenter;

	float shakeDuration = 0.f;
	float shakeTimer = 0.f;
	float shakeMagnitude = 10.f; //��鸲 ����
	
public:
	SceneGame();
	~SceneGame() = default;
	
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	const std::list<Monster*>& GetMonsters() const { return monsterList; }

	void SetBackGround();
	void UpdateBackGround();

	void SetButton();

	void SpawnMonster(int count);

	// Fade In Out
	void SetupFadeEffect();

	void UpdateFade(float dt);
	void FadeIn(float dt);
	void FadeOut(float dt);
	void UpdateFadeColor();

	void SetFadeOut(bool fadeOut) { this->fadeOut = fadeOut; }
	bool GetFadeOut() const { return fadeOut; }

	float GetFadeAlpha() const { return fadeAlpha; }

	// CameraShake
	void StartSceenShake(float duration, float magnitude);
	void UpdateScreenShake(float dt);
};

