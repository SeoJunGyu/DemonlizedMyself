#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "AniPlayer.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/Warrior_Sheet-Effect.png");
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	//애니메이션 로드
	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Idle.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Jump.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Run.csv");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Dev 2");
	//go->GetText().setString("데브 2");
	//go->GetText().setString(L"데브 2");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	AddGameObject(new AniPlayer());

	Scene::Init();
}

void SceneDev2::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	//uiView.setSize(size);
	//uiView.setCenter(center);
	//worldView.setSize(size);
	//worldView.setCenter({ 0.f, -200.f });

	Scene::Enter();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}