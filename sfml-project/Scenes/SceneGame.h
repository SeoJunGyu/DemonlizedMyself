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
	int maxSpawn = 20; //최대 스폰 수
	float spawnSpace = 150.f; //몬스터 간격
	float groupSpace = 300.f; //4마리 출력 후 그룹 간격
	int groupSize = 4; //출력할 한 그룹 총 마리 수

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

