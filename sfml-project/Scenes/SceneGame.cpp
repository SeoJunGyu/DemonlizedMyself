#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Monster.h"
#include "UiHud.h"
#include "StatUiHud.h"
#include "ButtonGo.h"

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
	texIds.push_back("graphics/Worrior_Icon.png");
	texIds.push_back("graphics/big_bar.png");
	texIds.push_back("graphics/basic_bar.png");
	texIds.push_back("graphics/Icon_frame.png");
	texIds.push_back("graphics/Gold.png");
	texIds.push_back("graphics/Gem.png");
	texIds.push_back("graphics/Enemy.png");
	texIds.push_back("graphics/Player.png");
	texIds.push_back("graphics/GrassGround.png");
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/Warrior_Sheet-Effect.png");
	texIds.push_back("graphics/HeroKnight.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");
	fontIds.push_back("fonts/Maplestory_Light.ttf");	

	//�ִϸ��̼� �ε�
	ANI_CLIP_MGR.Load("animations/warrior_Idle.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Run.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Attack.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Idle.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Attack.csv");

	SOUNDBUFFER_MGR.Load("audios/TitleBGM.wav");
	SOUNDBUFFER_MGR.Load("audios/BattleBGM.wav");
	SOUNDBUFFER_MGR.Load("audios/LevelUp.wav");
	SOUNDBUFFER_MGR.Load("audios/StatUp.wav");
	SOUNDBUFFER_MGR.Load("audios/StatUpFail.wav");
	SOUNDBUFFER_MGR.Load("audios/Player_whoosh.wav");
	SOUNDBUFFER_MGR.Load("audios/Worrior_whoosh.wav");
	SOUNDBUFFER_MGR.Load("audios/Hero_whoosh.wav");
	SOUNDBUFFER_MGR.Load("audios/hit.wav");
	SOUNDBUFFER_MGR.Load("audios/Death.wav");

	SOUND_MGR.Init(60);
	sf::SoundBuffer& buffer = SOUNDBUFFER_MGR.Get("audios/BattleBGM.wav");

	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	//�÷��̾� ����
	player = (Player*)AddGameObject(new Player("Player"));
	player->SetPosition({ 0.f, 0.f });
	player->SetScale({ 2.5f, 2.5f });

	//���� ����
	for (int i = 0; i < 100; i++)
	{
		Monster* monster = (Monster*)AddGameObject(new Monster());
		monster->SetActive(false);
		monster->SetScale({ -2.5f, 2.5f });
		monsterPool.push_back(monster);
	}

	//��׶��� ����
	SetBackGround();

	//Ui����
	uiHud = (UiHud*)AddGameObject(new UiHud("UiHud"));
	uiHud->sortingLayer = SortingLayers::UI;

	// Stat Ui ����
	statUi = (StatUiHud*)AddGameObject(new StatUiHud("StatUiHud"));
	statUi->sortingLayer = SortingLayers::UI;

	// �׺� ��ư
	btnSurrender = (ButtonGo*)AddGameObject(new ButtonGo("btnSurrender"));
	btnSurrender->SetClick([this]()
		{
			//Enter();
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
	);

	// ���� �� ��ư
	btnStrUp = (ButtonGo*)AddGameObject(new ButtonGo("btnStrUp"));
	btnStrUp->SetClick([this]()
		{
			if (player->GetStatPoint() > 0)
			{
				SOUND_MGR.PlaySfx("audios/StatUp.wav");
				player->SetStr(1);
				player->SetStatPoint(1);
			}
			else
			{
				SOUND_MGR.PlaySfx("audios/StatUpFail.wav");
			}
		}
	);

	btnDexUp = (ButtonGo*)AddGameObject(new ButtonGo("btnDexUp"));
	btnDexUp->SetClick([this]()
		{
			if (player->GetStatPoint() > 0)
			{
				SOUND_MGR.PlaySfx("audios/StatUp.wav");
				player->SetDex(1);
				player->SetStatPoint(1);
			}
			else
			{
				SOUND_MGR.PlaySfx("audios/StatUpFail.wav");
			}
		}
	);

	btnAgiUp = (ButtonGo*)AddGameObject(new ButtonGo("btnAgiUp"));
	btnAgiUp->SetClick([this]()
		{
			if (player->GetStatPoint() > 0)
			{
				SOUND_MGR.PlaySfx("audios/StatUp.wav");
				player->SetAgi(1);
				player->SetStatPoint(1);
			}
			else
			{
				SOUND_MGR.PlaySfx("audios/StatUpFail.wav");
			}
		}
	);

	btnLukUp = (ButtonGo*)AddGameObject(new ButtonGo("btnLukUp"));
	btnLukUp->SetClick([this]()
		{
			if (player->GetStatPoint() > 0)
			{
				SOUND_MGR.PlaySfx("audios/StatUp.wav");
				player->SetLuk(1);
				player->SetStatPoint(1);
			}
			else
			{
				SOUND_MGR.PlaySfx("audios/StatUpFail.wav");
			}
		}
	);

	btnStatReset = (ButtonGo*)AddGameObject(new ButtonGo("btnStatReset"));
	btnStatReset->SetClick([this]()
		{
			if (player->GetStatPoint() > 0)
			{
				SOUND_MGR.PlaySfx("audios/StatUpFail.wav");
				player->StatReset();
			}
		}
	);

	Scene::Init();
}

void SceneGame::Enter()
{
	if (!SOUND_MGR.IsBgmPlaying())
	{
		SOUND_MGR.PlayBgm("audios/BattleBGM.wav");
	}

	totalCurrentHp = 0;
	totalMaxHp = 0;

	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	sf::Vector2f playerPos = player->GetPosition();

	//�� ����
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ playerPos.x, playerPos.y - size.y * 0.25f });

	SetBackGround();

	Scene::Enter();

	SetButton();
	spawnCount = 0;
}

void SceneGame::Exit()
{
	for (Monster* monster : monsterList)
	{
		monster->SetActive(false);
		monsterPool.push_back(monster);
	}

	monsterList.clear();

	for (auto ground : groundList)
	{
		RemoveGameObject(ground);
	}
	groundList.clear();

	//SOUND_MGR.StopBgm();
	SOUND_MGR.StopAllSfx();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	SOUND_MGR.Update(dt);

	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f playerPos = player->GetPosition();

	worldView.setCenter({ playerPos.x, playerPos.y + size.y * 0.2f });

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << InputMgr::GetMousePosition().x << ", " << InputMgr::GetMousePosition().y << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	//���� Ǯ ����
	auto it = monsterList.begin();
	while (it != monsterList.end())
	{
		if (!(*it)->GetActive())
		{
			monsterPool.push_back(*it);
			it = monsterList.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (spawnCount < maxSpawn)
	{
		SpawnMonster(4);
	}

	UpdateBackGround();

	//std::cout << spawnCount << std::endl; //�÷��̾� �̵��ϰ��ִ��� �׽�Ʈ

	// ��� UI ����
	uiHud->SetTextLevel(player->GetLevel());
	uiHud->SetTextReward(player->GetGold(), player->GetGem());

	Scene::Update(dt);

	if (btnSurrender)
	{
		SetButton();
		btnSurrender->Update(dt);
	}
	
	if (spawnCount >= maxSpawn && monsterList.empty())
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	//���� �� HP �ѱ��
	totalCurrentHp = 0;
	for (auto monster : monsterList)
	{
		if (!monster->GetActive())
		{
			continue; //���� ������ ���� �ݺ� ����
		}

		totalCurrentHp += monster->GetHp();
	}
	uiHud->SetTotalHp(totalCurrentHp, totalMaxHp);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetBackGround()
{
	float groundWidth = 48.f * 3.f; //�ٴ� �ؽ��� ������ * scale ����

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

	if (groundList.empty())
	{
		for (int i = 0; i < 8; i++)
		{
			auto ground = (SpriteGo*)AddGameObject(new SpriteGo("graphics/GrassGround.png"));
			ground->SetScale({ 3.f, 3.f });
			ground->SetOrigin(Origins::TC);

			// ���ʺ��� ���������� ��ġ
			ground->SetPosition({ player->GetPosition().x - (groundWidth * 4) + groundWidth * i, player->GetPosition().y });
			ground->sortingLayer = SortingLayers::Background;
			ground->sortingOrder = 1;

			groundList.push_back(ground);
		}
	}
}

void SceneGame::UpdateBackGround()
{
	float groundWidth = 48.f * 3.f; //�ٴ� �ؽ��� ������ * scale ����
	auto size = FRAMEWORK.GetWindowSizeF();

	for (auto back : backList)
	{
		back->SetPosition(player->GetPosition());
	}

	//���� ��� �˻�
	float leftBound = player->GetPosition().x - size.x * 0.5f - groundWidth;
	float rightBound = player->GetPosition().x + size.x * 0.5f + groundWidth;

	//���� �ٴ� ���� ��� ����� �� �ڷ� ������
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

	SpriteGo* last = groundList.back();
	if (last->GetPosition().x - groundWidth * 0.5f > rightBound)
	{
		SpriteGo* first = groundList.front();
		sf::Vector2f newPos = first->GetPosition();
		newPos.x -= groundWidth;
		last->SetPosition({ newPos.x, newPos.y });

		groundList.pop_back();
		groundList.push_front(last);
	}
}

void SceneGame::SetButton()
{
	// �׺� ��ư
	btnSurrender->sortingLayer = SortingLayers::UI;
	btnSurrender->sortingOrder = 10;
	btnSurrender->SetFont("fonts/Maplestory_Light.ttf");
	btnSurrender->SetText("Surrender");
	btnSurrender->SetPosition({ uiHud->GetHpBarBg().getPosition().x + uiHud->GetHpBarBg().getLocalBounds().width + btnSurrender->GetLocalBounds().width + 40.f, uiHud->GetHpBarBg().getPosition().y});
	btnSurrender->SetFontSize(10);

	// ���� �� ��ư
	btnStrUp->sortingLayer = SortingLayers::UI;
	btnStrUp->sortingOrder = 10;
	btnStrUp->SetFont("fonts/Maplestory_Light.ttf");
	btnStrUp->SetText("Str Up");
	btnStrUp->SetPosition({ statUi->GetStrBack().getPosition().x + statUi->GetStrBack().getLocalBounds().width - 140, statUi->GetStrBack().getPosition().y + statUi->GetStrBack().getLocalBounds().height * 0.5f + 13.f });
	btnStrUp->SetFontSize(15);
	btnStrUp->SetOrigin(Origins::MC);
	btnStrUp->SetFillColor(sf::Color(67, 179, 105));

	btnDexUp->sortingLayer = SortingLayers::UI;
	btnDexUp->sortingOrder = 10;
	btnDexUp->SetFont("fonts/Maplestory_Light.ttf");
	btnDexUp->SetText("Dex Up");
	btnDexUp->SetPosition({ statUi->GetDexBack().getPosition().x + statUi->GetDexBack().getLocalBounds().width -140, statUi->GetDexBack().getPosition().y + statUi->GetDexBack().getLocalBounds().height * 0.5f + 13.f});
	btnDexUp->SetFontSize(15);
	btnDexUp->SetOrigin(Origins::MC);
	btnDexUp->SetFillColor(sf::Color(67, 179, 105));

	btnAgiUp->sortingLayer = SortingLayers::UI;
	btnAgiUp->sortingOrder = 10;
	btnAgiUp->SetFont("fonts/Maplestory_Light.ttf");
	btnAgiUp->SetText("Agi Up");
	btnAgiUp->SetPosition({ statUi->GetAgiBack().getPosition().x + statUi->GetAgiBack().getLocalBounds().width - 140, statUi->GetAgiBack().getPosition().y + statUi->GetAgiBack().getLocalBounds().height * 0.5f + 13.f });
	btnAgiUp->SetFontSize(15);
	btnAgiUp->SetOrigin(Origins::MC);
	btnAgiUp->SetFillColor(sf::Color(67, 179, 105));

	btnLukUp->sortingLayer = SortingLayers::UI;
	btnLukUp->sortingOrder = 10;
	btnLukUp->SetFont("fonts/Maplestory_Light.ttf");
	btnLukUp->SetText("Luk Up");
	btnLukUp->SetPosition({ statUi->GetLukBack().getPosition().x + statUi->GetLukBack().getLocalBounds().width - 140, statUi->GetLukBack().getPosition().y + statUi->GetLukBack().getLocalBounds().height * 0.5f + 13.f });
	btnLukUp->SetFontSize(15);
	btnLukUp->SetOrigin(Origins::MC);
	btnLukUp->SetFillColor(sf::Color(67, 179, 105));

	btnStatReset->sortingLayer = SortingLayers::UI;
	btnStatReset->sortingOrder = 10;
	btnStatReset->SetFont("fonts/Maplestory_Light.ttf");
	btnStatReset->SetText("Stat Reset");
	btnStatReset->SetPosition({ 611.f, 577.f });
	btnStatReset->SetFontSize(15);
	btnStatReset->SetOrigin(Origins::ML);
	btnStatReset->SetTextOrigin();
	btnStatReset->SetFillColor(sf::Color(184, 152, 91));
	
}

void SceneGame::SpawnMonster(int count)
{
	int spawnable = std::min(count, maxSpawn - spawnCount);
	if (spawnable <= 0)
	{
		return;
	}

	float baseX = player->GetPosition().x + 600.f;
	if (!monsterList.empty())
	{
		baseX = monsterList.back()->GetPosition().x + 300.f;
	}

	for (int i = 0; i < count; i++)
	{
		//i / groupSize : ���° �׷����� Ȯ�� (groupsize�� �� �׷� ������)
		float offsetX = spawnSpace * (i + 1) + (i / groupSize) * groupSpace; //spawnSpace * (i + 1) : �� �׷� ���� ���� / (i / groupSize) * groupSpace : �׷캰 ����
		float spawnX = baseX + offsetX; //���������� �׷� ��ġ ����

		Monster* monster = nullptr;

		if (monsterPool.empty())
		{
			monster = (Monster*)AddGameObject(new Monster("Monster"));
			monster->Init();
		}
		else
		{
			monster = monsterPool.front();
			monsterPool.pop_front();
			monster->SetActive(true);
		}

		monster->SetAlive(true);
		monster->SetType((Monster::Type)Utils::RandomRange(0, (int)Monster::TotalType));
		monster->Reset();
		monster->SetPosition({ spawnX, player->GetPosition().y });
		monsterList.push_back(monster);
		spawnCount++;

		totalMaxHp += monster->GetMaxHp();
	}
}
