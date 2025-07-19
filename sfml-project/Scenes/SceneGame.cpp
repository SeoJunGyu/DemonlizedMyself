#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Monster.h"
#include "UiHud.h"
#include "StatUiHud.h"
#include "ButtonGo.h"
#include "Skill.h"

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
	texIds.push_back("graphics/flag.png");
	texIds.push_back("graphics/skillSlot.png");
	texIds.push_back("graphics/Explode.png");
	texIds.push_back("graphics/ExplodeEffect.png");
	texIds.push_back("graphics/GrassGround.png");
	texIds.push_back("graphics/sprite_sheet.png");
	texIds.push_back("graphics/Warrior_Sheet-Effect.png");
	texIds.push_back("graphics/HeroKnight.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");
	fontIds.push_back("fonts/Maplestory_Light.ttf");	

	//애니메이션 로드
	ANI_CLIP_MGR.Load("animations/warrior_Idle.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Run.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Attack.csv");
	ANI_CLIP_MGR.Load("animations/warrior_Death.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Idle.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Attack.csv");
	ANI_CLIP_MGR.Load("animations/HeroKnight_Death.csv");
	ANI_CLIP_MGR.Load("animations/skill_Explode.csv");

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

	//플레이어 생성
	player = (Player*)AddGameObject(new Player("Player"));
	player->SetPosition({ 0.f, 0.f });
	player->SetScale({ 2.5f, 2.5f });

	//몬스터 생성
	for (int i = 0; i < 100; i++)
	{
		Monster* monster = (Monster*)AddGameObject(new Monster());
		monster->SetActive(false);
		monster->SetScale({ -2.5f, 2.5f });
		monsterPool.push_back(monster);
	}

	skill = (Skill*)AddGameObject(new Skill("Skill"));

	//백그라운드 설정
	SetBackGround();

	//Ui설정
	uiHud = (UiHud*)AddGameObject(new UiHud("UiHud"));
	uiHud->sortingLayer = SortingLayers::UI;

	// Stat Ui 설정
	statUi = (StatUiHud*)AddGameObject(new StatUiHud("StatUiHud"));
	statUi->sortingLayer = SortingLayers::UI;

	// 항복 버튼
	btnSurrender = (ButtonGo*)AddGameObject(new ButtonGo("btnSurrender"));
	btnSurrender->SetClick([this]()
		{
			//Enter();
			//SCENE_MGR.ChangeScene(SceneIds::Game);
			player->OnDamage(player->GetMaxHp());
		}
	);

	// 스탯 업 버튼
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

	// UI 전환 버튼
	btnChangeStat = (ButtonGo*)AddGameObject(new ButtonGo("btnChangeStat"));
	btnChangeStat->SetClick([this]()
		{
			isStat = true;
			statUi->SetIsStat(isStat);
			statUi->SetIsSkill(!isStat);
		}
	);

	btnChangeSkill = (ButtonGo*)AddGameObject(new ButtonGo("btnChangeSkill"));
	btnChangeSkill->SetClick([this]()
		{
			isStat = false;
			statUi->SetIsStat(isStat);
			statUi->SetIsSkill(!isStat);
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

	sf::Vector2f playerPos = player->GetPosition();
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	//뷰 설정
	uiView.setSize(size);
	uiView.setCenter(center);
	
	worldView.setCenter({ playerPos.x, playerPos.y + size.y * 0.1f });
	

	SetBackGround();

	Scene::Enter();
	
	worldView.setSize(size);
	//SetStatButton();
	spawnCount = 0;

	// 페이드 인 아웃 설정
	SetupFadeEffect();

	// 카메라 쉐이크 설정
	originalViewCenter = worldView.getCenter();
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

	UpdateFade(dt); //페이드 인 아웃 업데이트

	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f playerPos = player->GetPosition();

	worldView.setCenter({ playerPos.x, playerPos.y + size.y * 0.15f });
	originalViewCenter = worldView.getCenter();

	UpdateScreenShake(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << InputMgr::GetMousePosition().x << ", " << InputMgr::GetMousePosition().y << std::endl;
	}
	

	//몬스터 풀 관리
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

	//std::cout << spawnCount << std::endl; //플레이어 이동하고있는지 테스트

	// 상단 UI 설정
	uiHud->SetTextLevel(player->GetLevel());
	uiHud->SetTextReward(player->GetGold(), player->GetGem());

	Scene::Update(dt);

	if (btnSurrender)
	{
		SetButton();
		ChangeButton();
		btnSurrender->Update(dt);
	}
	
	if (spawnCount >= maxSpawn && monsterList.empty())
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	//몬스터 총 HP 넘기기
	totalCurrentHp = 0;
	for (auto monster : monsterList)
	{
		if (!monster->GetActive())
		{
			continue; //몬스터 없으면 다음 반복 진행
		}

		totalCurrentHp += monster->GetHp();
	}
	uiHud->SetTotalHp(totalCurrentHp, totalMaxHp);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	
	window.draw(iconBtnSurrender);
	window.draw(fadeRect);
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
		back->SetPosition({ player->GetPosition().x, player->GetPosition().y - 100.f });
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

			// 왼쪽부터 오른쪽으로 배치
			ground->SetPosition({ player->GetPosition().x - (groundWidth * 4) + groundWidth * i, player->GetPosition().y });
			ground->sortingLayer = SortingLayers::Background;
			ground->sortingOrder = 1;

			groundList.push_back(ground);
		}
	}
}

void SceneGame::UpdateBackGround()
{
	float groundWidth = 48.f * 3.f; //바닥 텍스쳐 사이즈 * scale 배율
	auto size = FRAMEWORK.GetWindowSizeF();

	for (auto back : backList)
	{
		back->SetPosition({ player->GetPosition().x, player->GetPosition().y - 100.f });
	}

	//왼쪽 경계 검사
	float leftBound = player->GetPosition().x - size.x * 0.5f - groundWidth;
	float rightBound = player->GetPosition().x + size.x * 0.5f + groundWidth;

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
	// 항복 버튼
	btnSurrender->sortingLayer = SortingLayers::UI;
	btnSurrender->sortingOrder = 10;
	btnSurrender->SetFont("fonts/Maplestory_Light.ttf");
	//btnSurrender->SetText("Surrender");
	btnSurrender->SetPosition({ uiHud->GetHpBarBg().getPosition().x + uiHud->GetHpBarBg().getLocalBounds().width + btnSurrender->GetLocalBounds().width + 40.f, uiHud->GetHpBarBg().getPosition().y + 15.f});
	//btnSurrender->SetFontSize(10);
	btnSurrender->SetSize({ 57.f, 57.f });

	iconBtnSurrender.setPosition({ btnSurrender->GetPosition().x + btnSurrender->GetLocalBounds().width * 0.5f, btnSurrender->GetPosition().y + btnSurrender->GetLocalBounds().height * 0.5f});
	iconBtnSurrender.setTexture(TEXTURE_MGR.Get("graphics/flag.png")); //항복 아이콘 텍스쳐 설정
	Utils::SetOrigin(iconBtnSurrender, Origins::MC);

	// 스탯 업 버튼
	if (isStat)
	{
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
		btnDexUp->SetPosition({ statUi->GetDexBack().getPosition().x + statUi->GetDexBack().getLocalBounds().width - 140, statUi->GetDexBack().getPosition().y + statUi->GetDexBack().getLocalBounds().height * 0.5f + 13.f });
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
	
	// UI 전환 버튼
	btnChangeStat->sortingLayer = SortingLayers::UI;
	btnChangeStat->sortingOrder = 10;
	btnChangeStat->SetFont("fonts/Maplestory_Light.ttf");
	btnChangeStat->SetText("Stat");
	btnChangeStat->SetPosition({ 100.f, statUi->GetBack().getPosition().y + 30.f});
	btnChangeStat->SetFontSize(15);
	btnChangeStat->SetSize({ 50.f, 30.f });
	btnChangeStat->SetOrigin(Origins::MC);
	btnChangeStat->SetFillColor(sf::Color(22, 30, 43));

	btnChangeSkill->sortingLayer = SortingLayers::UI;
	btnChangeSkill->sortingOrder = 10;
	btnChangeSkill->SetFont("fonts/Maplestory_Light.ttf");
	btnChangeSkill->SetText("Skill");
	btnChangeSkill->SetPosition({ btnChangeStat->GetPosition().x + 100.f , statUi->GetBack().getPosition().y + 30.f});
	btnChangeSkill->SetFontSize(15);
	btnChangeSkill->SetSize({ 50.f, 30.f });
	btnChangeSkill->SetOrigin(Origins::MC);
	btnChangeSkill->SetFillColor(sf::Color(22, 30, 43));
}

void SceneGame::ChangeButton()
{
	btnStatReset->SetActive(isStat);
	btnStrUp->SetActive(isStat);
	btnDexUp->SetActive(isStat);
	btnAgiUp->SetActive(isStat);
	btnLukUp->SetActive(isStat);
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
		//i / groupSize : 몇번째 그룹인지 확인 (groupsize가 한 그룹 마리수)
		float offsetX = spawnSpace * (i + 1) + (i / groupSize) * groupSpace; //spawnSpace * (i + 1) : 한 그룹 내의 간격 / (i / groupSize) * groupSpace : 그룹별 간격
		float spawnX = baseX + offsetX; //기준점부터 그룹 위치 설정

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

void SceneGame::SetupFadeEffect()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	fadeRect.setSize({ size.x, size.y * 0.5f });
	fadeRect.setPosition(0.f, 0.f);
	fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

	fadeAlpha = 255.0f;
	fadeIn = true;
	fadeOut = false;
	fadeTimer = 0.0f;
}

void SceneGame::UpdateFade(float dt)
{
	if (fadeIn)
	{
		FadeIn(dt);
	}
	else if (fadeOut)
	{
		FadeOut(dt);
	}
}

void SceneGame::FadeIn(float dt)
{
	fadeTimer += dt;

	float progress = fadeTimer / fadeInterval;
	if (progress > 1.0f)
	{
		progress = 1.0f; //진행률이 더 올라가지 않도록 고정
	}

	fadeAlpha = 255.0f * (1.0f - progress); //255에서 0으로 감소

	if (progress >= 1.0f)
	{
		fadeAlpha = 0.0f;
		fadeIn = false;
		fadeTimer = 0.0f;
	}

	UpdateFadeColor();
}

void SceneGame::FadeOut(float dt)
{
	fadeTimer += dt * 2.7f;

	float progress = fadeTimer / fadeInterval;
	if (progress > 1.0f)
	{
		progress = 1.0f; //진행률이 더 올라가지 않도록 고정
	}

	fadeAlpha = 255.0f * progress; //0에서 255로 증가

	if (progress >= 1.0f)
	{
		fadeAlpha = 255.0f;
		fadeTimer = 0.0f;
	}
	UpdateFadeColor();
}

void SceneGame::UpdateFadeColor()
{
	int alphaInt = static_cast<int>(fadeAlpha + 0.5f);
	fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alphaInt)));
}

void SceneGame::StartSceenShake(float duration, float magnitude)
{
	shakeDuration = duration;
	shakeTimer = 0.f;
	shakeMagnitude = magnitude;
}

void SceneGame::UpdateScreenShake(float dt)
{
	if (shakeTimer < shakeDuration)
	{
		shakeTimer += dt;

		float progress = shakeTimer / shakeDuration;
		if (progress > 1.0f)
		{
			progress = 1.0f; //진행률이 더 올라가지 않도록 고정
		}
		float currentMagnitude = shakeMagnitude * (1.f - progress);

		float offsetX = Utils::RandomRange(-currentMagnitude, currentMagnitude);
		float offsetY = Utils::RandomRange(-currentMagnitude, currentMagnitude);

		worldView.setCenter(originalViewCenter + sf::Vector2f(offsetX, offsetY));
		//std::cout << "Camera Shake" << std::endl;
	}
	else
	{
		worldView.setCenter(originalViewCenter);
	}
}
