#include "stdafx.h"
#include "StatUiHud.h"
#include "Player.h"

StatUiHud::StatUiHud(const std::string& name)
	: GameObject(name)
{
}

void StatUiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	auto size = FRAMEWORK.GetWindowSizeF();

	// 하단 배경
	back.setSize({ size.x, size.y * 0.5f });
	back.setPosition({ 0.f, size.y * 0.5f });
	back.setFillColor(sf::Color(32, 43, 61, 255));
}

void StatUiHud::Release()
{
}

void StatUiHud::Reset()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	textLevel.setFont(FONT_MGR.Get(fontId));
	textExp.setFont(FONT_MGR.Get(fontId));

	// Player ExpBar
	expBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	expBarbg.setSize({ 300.f, 20.f });
	Utils::SetOrigin(expBarbg, Origins::ML);

	expBar.setFillColor(sf::Color(255, 183, 0, 255));
	expBar.setSize({ 300.f, 20.f });
	Utils::SetOrigin(expBar, Origins::ML);

	expPer = expBar.getSize().x / player->GetMaxExp();
}

void StatUiHud::Update(float dt)
{
	UpdateExpBar();
}

void StatUiHud::Draw(sf::RenderWindow& window)
{
	window.draw(back);

	window.draw(textLevel);

	//플레이어 exp
	window.draw(expBarbg);
	window.draw(expBar);
	window.draw(textExp);
}

void StatUiHud::UpdateExpBar()
{
	expBarbg.setPosition(expBar.getPosition());
	expBar.setPosition({ 100.f, back.getPosition().y + 100.f });

	float fill = expPer * player->GetExp();
	expBar.setSize({ fill, expBar.getSize().y });

	textLevel.setString("Lv " + std::to_string(player->GetLevel()));
	textLevel.setPosition(expBar.getPosition().x, expBar.getPosition().y - 40);
	textLevel.setCharacterSize(20);
	textLevel.setFillColor(sf::Color::White);

	Utils::SetOrigin(textLevel, Origins::TL);

	textExp.setString(std::to_string(player->GetExp()) + "%");
	textExp.setPosition(expBar.getPosition().x + expBarbg.getLocalBounds().width * 0.5f, expBar.getPosition().y - 5.f);
	textExp.setCharacterSize(20);
	textExp.setFillColor(sf::Color::White);

	Utils::SetOrigin(textExp, Origins::MC);
}
