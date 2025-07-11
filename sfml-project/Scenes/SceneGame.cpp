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

	//�ִϸ��̼� �ε�
	ANI_CLIP_MGR.Load("animations/warrior_Idle.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Jump.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Run.csv");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Game");
	//go->GetText().setString("���� 2");
	//go->GetText().setString(L"���� 2");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	player = (Player*)AddGameObject(new Player());

	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, -200.f });

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}