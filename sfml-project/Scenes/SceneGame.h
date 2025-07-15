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
	float spawnSpace = 150.f; //���� ����
	float groupSpace = 300.f; //4���� ��� �� �׷� ����
	int groupSize = 4; //����� �� �׷� �� ���� ��

	// Background
	std::vector<SpriteGo*> backList;
	std::list<SpriteGo*> groundList;
	int backCount = 0;

	ButtonGo* btnSurrender = nullptr;

	ButtonGo* btnStrUp = nullptr;
	ButtonGo* btnDexUp = nullptr;
	ButtonGo* btnAgiUp = nullptr;
	ButtonGo* btnLukUp = nullptr;
	
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
};

