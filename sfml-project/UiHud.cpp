#include "stdafx.h"
#include "UiHud.h"
#include "ButtonGo.h"
#include "Player.h"
#include "SceneGame.h"
#include <iomanip>

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	auto size = FRAMEWORK.GetWindowSizeF();

	//scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	//최상단 : 46 69 85
	//상단 버튼 : 22 30 43
	//맨 밑 바탕 : 32 43 61
	//스텟 버튼 : 73 183 110
	//경험치 바 : 15 201 224
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
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	playerIcon.setTexture(TEXTURE_MGR.Get(iconTexId), true);
	Gold.setTexture(TEXTURE_MGR.Get(texIdGold), true);
	Gem.setTexture(TEXTURE_MGR.Get(texIdGem), true);
	iconEnemyHealth.setTexture(TEXTURE_MGR.Get(texIdEnemyIcon), true);
	iconHealth.setTexture(TEXTURE_MGR.Get(texIdHealth), true);

	time = 0.f;

	textHp.setFont(FONT_MGR.Get(fontId));
	textGold.setFont(FONT_MGR.Get(fontId));
	textGem.setFont(FONT_MGR.Get(fontId));
	textLevel.setFont(FONT_MGR.Get(fontId));
	textTime.setFont(FONT_MGR.Get(fontId));

	// Player HPBar
	playerHpBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	playerHpBarbg.setSize({ 300.f, 25.f });
	Utils::SetOrigin(playerHpBarbg, Origins::ML);

	playerHpBar.setFillColor(sf::Color(35, 117, 157));
	playerHpBar.setSize({ 300.f, 25.f });
	Utils::SetOrigin(playerHpBar, Origins::ML);

	hpPer = playerHpBar.getSize().x / player->GetHp();

	// Player EXPBar
	expBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	expBarbg.setSize({ size.x - 30.f, 8.f });
	Utils::SetOrigin(expBarbg, Origins::ML);

	expBar.setFillColor(sf::Color(15, 201, 224));
	expBar.setSize({ size.x - 30.f, 8.f });
	Utils::SetOrigin(expBar, Origins::ML);

	expPer = expBar.getSize().x / player->GetMaxExp();

	// Monster HpBar
	monsterHpBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	monsterHpBarbg.setSize({ 300.f, 25.f });
	Utils::SetOrigin(monsterHpBarbg, Origins::ML);

	monsterHpBar.setFillColor(sf::Color(168, 41, 0));
	monsterHpBar.setSize({ 300.f, 25.f });
	Utils::SetOrigin(monsterHpBar, Origins::ML);
	
}

void UiHud::Update(float dt)
{
	UpdateTextTime(dt);
	UpdateHpBar();
	UpdateExpBar();
}

void UiHud::Draw(sf::RenderWindow& window)
{
	//상단
	window.draw(topBack);
	window.draw(textLevel);
	window.draw(goldBack);
	window.draw(gemBack);
	window.draw(textGold);
	window.draw(textGem);
	window.draw(textTime);

	window.draw(playerIcon);
	window.draw(Gold);
	window.draw(Gem);
	window.draw(iconEnemyHealth);
	window.draw(iconHealth);

	//플레이어 hp
	window.draw(playerHpBarbg);
	window.draw(playerHpBar);
	window.draw(textHp);

	//플레이어 exp
	window.draw(expBarbg);
	window.draw(expBar);

	//몬스터 hp
	window.draw(monsterHpBarbg);
	window.draw(monsterHpBar);
	
}

void UiHud::UpdateHpBar()
{
	// Player HpBar
	playerHpBar.setPosition({ 200.f, 140.f });
	playerHpBarbg.setPosition(playerHpBar.getPosition());

	float fill = hpPer * player->GetHp();
	playerHpBar.setSize({ fill, playerHpBar.getSize().y });

	textHp.setString(std::to_string(player->GetHp()) + " / " + std::to_string(player->GetMaxHp()));
	textHp.setPosition(playerHpBarbg.getPosition().x + playerHpBarbg.getLocalBounds().width * 0.5f, playerHpBarbg.getPosition().y + playerHpBarbg.getLocalBounds().height * 0.5f - 10.f);
	textHp.setCharacterSize(10);
	textHp.setFillColor(sf::Color::White);

	Utils::SetOrigin(textHp, Origins::BC);

	// Monster HpBar
	monsterHpBar.setPosition({ 200.f, 170.f });
	monsterHpBarbg.setPosition(monsterHpBar.getPosition());

	float monsterFill = monsterHpPer * totalCurrentHp;
	monsterHpBar.setSize({ monsterFill, monsterHpBar.getSize().y });

	// Icon
	iconHealth.setPosition({ playerHpBarbg.getPosition().x - 20.f, playerHpBarbg.getPosition().y });
	Utils::SetOrigin(iconHealth, Origins::MR);
	iconEnemyHealth.setPosition({ monsterHpBarbg.getPosition().x - 20.f, monsterHpBarbg.getPosition().y });
	Utils::SetOrigin(iconEnemyHealth, Origins::MR);
	
}

void UiHud::UpdateExpBar()
{
	expBarbg.setPosition(expBar.getPosition());
	expBar.setPosition({ topBack.getPosition().x, topBack.getPosition().y + topBack.getLocalBounds().height + expBar.getLocalBounds().height * 0.5f});

	float fill = expPer * player->GetExp();
	expBar.setSize({ fill, expBar.getSize().y });
}

void UiHud::UpdateTextTime(float t)
{
	time += t;
	std::stringstream tmp;
	tmp << std::fixed << std::setprecision(3) << time;

	//textTime.setString(std::to_string(time));
	textTime.setString(tmp.str());
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
	textLevel.setString("Lv " + std::to_string(level));
	textLevel.setPosition(topBack.getPosition().x + 20.f, topBack.getPosition().y + 35.f);
	textLevel.setCharacterSize(10);
	textLevel.setFillColor(sf::Color::White);

	Utils::SetOrigin(textLevel, Origins::TL);

	// PlayerIcon
	playerIcon.setPosition({ textLevel.getPosition().x , textLevel.getPosition().y - 23.f });
	playerIcon.setScale({ 1.2f, 1.2f });
}

void UiHud::SetTextReward(int gold, int gem)
{
	// Gold
	textGold.setString(std::to_string(gold));
	textGold.setPosition(goldBack.getPosition().x + goldBack.getLocalBounds().width - 10.f, goldBack.getPosition().y - 5.f);
	textGold.setCharacterSize(20);
	textGold.setFillColor(sf::Color::White);

	Utils::SetOrigin(textGold, Origins::MR);

	Gold.setPosition({ textGold.getPosition().x - 140.f , textGold.getPosition().y - 10.f });

	// Gem
	textGem.setString(std::to_string(gem));
	textGem.setPosition(gemBack.getPosition().x + gemBack.getLocalBounds().width - 10.f, gemBack.getPosition().y - 5.f);
	textGem.setCharacterSize(20);
	textGem.setFillColor(sf::Color::White);

	Utils::SetOrigin(textGem, Origins::MR);

	Gem.setPosition({ textGem.getPosition().x - 140.f , textGem.getPosition().y - 10.f });
}

void UiHud::SetTotalHp(int currentHp, int MaxHp)
{
	totalMaxHp = MaxHp;
	totalCurrentHp = currentHp;

	if (totalMaxHp > 0)
	{
		monsterHpPer = 300.f / totalMaxHp;
	}
	else
	{
		monsterHpPer = 0.f;
	}
}
