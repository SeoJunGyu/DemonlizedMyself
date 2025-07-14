#include "stdafx.h"
#include "UiHud.h"
#include "Button.h"
#include "Player.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	auto size = FRAMEWORK.GetWindowSizeF();

	//최상단 : 46 69 85
	//상단 버튼 : 22 30 43
	//맨 밑 바탕 : 32 43 61
	//스텟 버튼 : 73 183 110
	topBack.setSize({ size.x - 30.f, 50.f });
	topBack.setPosition({ 15.f, 25.f });
	topBack.setFillColor(sf::Color(36, 43, 79, 200));

	goldBack.setSize({ 150.f, 30.f });
	Utils::SetOrigin(goldBack, Origins::ML);
	goldBack.setPosition({ topBack.getPosition().x + topBack.getLocalBounds().width * 0.5f, topBack.getPosition().y + topBack.getLocalBounds().height * 0.5f});
	goldBack.setFillColor(sf::Color(32, 43, 61, 255));

	gemBack.setSize({ 150.f, 30.f });
	Utils::SetOrigin(gemBack, Origins::ML);
	gemBack.setPosition({ goldBack.getPosition().x + goldBack.getLocalBounds().width + 10.f, topBack.getPosition().y + topBack.getLocalBounds().height * 0.5f });
	gemBack.setFillColor(sf::Color(32, 43, 61, 255));

	back.setSize({ size.x, size.y * 0.5f });
	back.setPosition({ 0.f, size.y * 0.5f });
	back.setFillColor(sf::Color(32, 43, 61, 255));

	//textLevel = new TextGo(fontId);
	currentLevel = 0;

	// 상단 UI 배치
	
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	time = 0.f;

	textHp.setFont(FONT_MGR.Get(fontId));
	textLevel.setFont(FONT_MGR.Get(fontId));
	textTime.setFont(FONT_MGR.Get(fontId));

	playerHpBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	playerHpBarbg.setSize({ 300.f, 25.f });
	Utils::SetOrigin(playerHpBarbg, Origins::ML);

	playerHpBar.setFillColor(sf::Color(32, 150, 128, 255));
	playerHpBar.setSize({ 300.f, 25.f });
	Utils::SetOrigin(playerHpBar, Origins::ML);

	per = playerHpBar.getSize().x / player->GetHp();
}

void UiHud::Update(float dt)
{
	UpdateTextTime(dt);
	UpdateHpBar();
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(topBack);
	window.draw(goldBack);
	window.draw(gemBack);
	window.draw(back);
	window.draw(textTime);
	window.draw(textLevel);

	window.draw(playerHpBarbg);
	window.draw(playerHpBar);
	window.draw(textHp);
}

void UiHud::UpdateHpBar()
{
	playerHpBarbg.setPosition(playerHpBar.getPosition());
	playerHpBar.setPosition({200.f, 100.f});

	float fill = per * player->GetHp();
	playerHpBar.setSize({ fill, playerHpBar.getSize().y });

	textHp.setString(std::to_string(player->GetHp()) + " / " + std::to_string(player->GetMaxHp()));
	textHp.setPosition(playerHpBarbg.getPosition().x + playerHpBarbg.getLocalBounds().width * 0.5f, playerHpBarbg.getPosition().y + playerHpBarbg.getLocalBounds().height * 0.5f);
	textHp.setCharacterSize(10);
	textHp.setFillColor(sf::Color::White);

	Utils::SetOrigin(textHp, Origins::BC);
}

void UiHud::UpdateTextTime(float t)
{
	time += t;

	textTime.setString(std::to_string(time));
	textTime.setPosition(topBack.getLocalBounds().width, topBack.getLocalBounds().height + 30);
	textTime.setCharacterSize(20);
	textTime.setFillColor(sf::Color::Black);
	Utils::SetOrigin(textTime, Origins::TR);
}

void UiHud::SetTextTime(float time)
{
	textTime.setString(std::to_string(time));
	textTime.setPosition(topBack.getLocalBounds().width, topBack.getLocalBounds().height + 30);
	textTime.setCharacterSize(5);
	textTime.setFillColor(sf::Color::Black);
	Utils::SetOrigin(textTime, Origins::TL);
}

void UiHud::SetTextLevel(int level)
{
	/*
	textLevel->GetText().setString("Lv " + std::to_string(level));
	textLevel->SetPosition({ topBack.getPosition().x + 10, topBack.getPosition().y + 30 });
	textLevel->GetText().setCharacterSize(50);
	textLevel->SetFillColor(sf::Color::Black);
	textLevel->SetOrigin(Origins::TL);
	textLevel->sortingLayer = SortingLayers::UI;
	textLevel->sortingOrder = 10;
	*/
	textLevel.setString("Lv " + std::to_string(level));
	textLevel.setPosition(topBack.getPosition().x + 10, topBack.getPosition().y + 30);
	textLevel.setCharacterSize(10);
	textLevel.setFillColor(sf::Color::White);

	Utils::SetOrigin(textLevel, Origins::TL);
}
