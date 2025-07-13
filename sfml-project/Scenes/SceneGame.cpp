#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Monster.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/Background1.png");
	texIds.push_back("graphics/Background2.png");
	texIds.push_back("graphics/Background3.png");
	texIds.push_back("graphics/Background4.png");
	texIds.push_back("graphics/Background5.png");
	texIds.push_back("graphics/Background1.png");
	texIds.push_back("graphics/GrassGround.png");
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/Warrior_Sheet-Effect.png");
	texIds.push_back("graphics/HeroKnight.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	//애니메이션 로드
	ANI_CLIP_MGR.Load("animations/warrior_Idle.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Run.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Attack.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Idle.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Attack.csv");

	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	
	//테스트 텍스트
	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Game");
	//go->GetText().setString("데브 2");
	//go->GetText().setString(L"데브 2");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	//플레이어 생성
	player = (Player*)AddGameObject(new Player("Player"));
	player->SetPosition({ 0.f, 0.f });
	player->SetScale({ 2.5f, 2.5f });

	//몬스터 생성
	monster = (Monster*)AddGameObject(new Monster("Monster"));
	monster->SetPosition({ 500.f, 0.f });
	monster->SetScale({ -2.5f, 2.5f });
	//monster->SetScale({ 1.f, 1.f });

	//백그라운드 설정
	SetBackGround();

	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	sf::Vector2f playerPos = player->GetPosition();

	//뷰 설정
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

	if (InputMgr::GetKeyDown(sf::Keyboard::D)) 
	{
		monster->SetActive(false);
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << InputMgr::GetMousePosition().x << ", " << InputMgr::GetMousePosition().y << std::endl;
	}

	UpdateBackGround();

	//std::cout << player->GetPosition().x << std::endl; //플레이어 이동하고있는지 테스트

	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetBackGround()
{
	float groundWidth = 48.f * 3.f; //바닥 텍스쳐 사이즈 * scale 배율

	std::vector<std::string> texList =
	{
		"graphics/Background5.png",
		"graphics/Background4.png",
		"graphics/Background3.png",
		"graphics/Background2.png",
		"graphics/Background1.png"
	};

	for (int i = 0; i < 5; i++)
	{
		auto back = (SpriteGo*)AddGameObject(new SpriteGo(texList[i]));
		back->SetScale({ 3.f, 4.f });
		back->SetOrigin(Origins::MC);
		back->SetPosition(player->GetPosition());
		back->sortingLayer = SortingLayers::Background;
		back->sortingOrder = i - 4;
		backList.push_back(back);
		backCount++;
	}

	for (int i = 0; i < 8; i++)
	{
		auto ground = (SpriteGo*)AddGameObject(new SpriteGo("graphics/GrassGround.png"));
		ground->SetScale({ 3.f, 3.f });
		ground->SetOrigin(Origins::TC);

		// 왼쪽부터 오른쪽으로 배치
		ground->SetPosition({ player->GetPosition().x - (groundWidth * 4) + groundWidth * i, player->GetPosition().y});
		ground->sortingLayer = SortingLayers::Background;
		ground->sortingOrder = 1;

		groundList.push_back(ground);
	}
	
}

void SceneGame::UpdateBackGround()
{
	float groundWidth = 48.f * 3.f; //바닥 텍스쳐 사이즈 * scale 배율
	auto size = FRAMEWORK.GetWindowSizeF();

	for (auto back : backList)
	{
		back->SetPosition(player->GetPosition());
	}

	//왼쪽 경계 검사
	float leftBound = player->GetPosition().x - size.x * 0.5f - groundWidth;

	//앞쪽 바닥 왼쪽 경계 벗어나면 맨 뒤로 보내기
	SpriteGo* first = groundList.front();
	if (first->GetPosition().x + groundWidth * 0.5f < leftBound)
	{
		SpriteGo* last = groundList.back();
		sf::Vector2f newPos = last->GetPosition();
		newPos.x += groundWidth;
		first->SetPosition({ newPos.x, newPos.y });
		
		groundList.pop_front();
		groundList.push_back(first);
	}
}
