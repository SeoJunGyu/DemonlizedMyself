#pragma once
#include "Scene.h"

class Player;

class SceneGame :
    public Scene
{
protected:
	Player* player = nullptr;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

