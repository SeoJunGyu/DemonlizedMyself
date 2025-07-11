#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/Warrior_Sheet-Effect.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	//애니메이션 로드
	ANI_CLIP_MGR.Load("animations/warrior_Idle.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Jump.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Run.csv");

	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Game");
	//go->GetText().setString("데브 2");
	//go->GetText().setString(L"데브 2");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	player = (Player*)AddGameObject(new Player("Player"));
	player->SetPosition(center);
	player->SetScale({ 2.5f, 2.5f });

	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	sf::Vector2f playerPos = player->GetPosition();

	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ playerPos.x, playerPos.y - size.y * 0.25f });

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f playerPos = player->GetPosition();

	worldView.setCenter({ playerPos.x, playerPos.y + size.y * 0.2f });
	std::cout << player->GetPosition().x << std::endl;

	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}