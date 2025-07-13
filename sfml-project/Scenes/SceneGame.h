#pragma once
#include "Scene.h"

class SpriteGo;
class Player;
class Monster;

class SceneGame :
    public Scene
{
protected:
	Player* player = nullptr;
	Monster* monster = nullptr;

	// Background
	std::vector<SpriteGo*> backList;
	std::list<SpriteGo*> groundList;
	int backCount = 0;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetBackGround();
	void UpdateBackGround();
};

