#include "stdafx.h"
#include "StatUiHud.h"
#include "Player.h"
#include <iomanip>

StatUiHud::StatUiHud(const std::string& name)
	: GameObject(name)
{
}

void StatUiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	auto size = FRAMEWORK.GetWindowSizeF();

	// �ϴ� ���
	back.setSize({ size.x, size.y * 0.5f });
	back.setPosition({ 0.f, size.y * 0.5f });
	back.setFillColor(sf::Color(32, 43, 61, 255));

	strBack.setSize({ size.x - 20.f, 70.f });
	strBack.setPosition({ 10.f, back.getPosition().y + 130.f });
	strBack.setFillColor(sf::Color(46, 69, 85, 255));

	dexBack.setSize({ size.x - 20.f, 70.f });
	dexBack.setPosition({ 10.f, back.getPosition().y + 220.f });
	dexBack.setFillColor(sf::Color(46, 69, 85, 255));

	agiBack.setSize({ size.x - 20.f, 70.f });
	agiBack.setPosition({ 10.f, back.getPosition().y + 310.f });
	agiBack.setFillColor(sf::Color(46, 69, 85, 255));

	lukBack.setSize({ size.x - 20.f, 70.f });
	lukBack.setPosition({ 10.f, back.getPosition().y + 400.f });
	lukBack.setFillColor(sf::Color(46, 69, 85, 255));
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

	textStr.setFont(FONT_MGR.Get(fontId));
	textDex.setFont(FONT_MGR.Get(fontId));
	textAgi.setFont(FONT_MGR.Get(fontId));
	textLuk.setFont(FONT_MGR.Get(fontId));

	textValueStr.setFont(FONT_MGR.Get(fontId));
	textValueDex.setFont(FONT_MGR.Get(fontId));
	textValueAgi.setFont(FONT_MGR.Get(fontId));
	textValueLuk.setFont(FONT_MGR.Get(fontId));
	textLevelStr.setFont(FONT_MGR.Get(fontId));
	textLevelDex.setFont(FONT_MGR.Get(fontId));
	textLevelAgi.setFont(FONT_MGR.Get(fontId));
	textLevelLuk.setFont(FONT_MGR.Get(fontId));

	// Player ExpBar
	expBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	expBarbg.setSize({ 300.f, 20.f });
	Utils::SetOrigin(expBarbg, Origins::ML);

	expBar.setFillColor(sf::Color(255, 183, 0, 255));
	expBar.setSize({ 300.f, 20.f });
	Utils::SetOrigin(expBar, Origins::ML);

	expPer = expBar.getSize().x / player->GetMaxExp();

	SetStat();
}

void StatUiHud::Update(float dt)
{
	UpdateExpBar();
	UpdateStat();
}

void StatUiHud::Draw(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(strBack);
	window.draw(dexBack);
	window.draw(agiBack);
	window.draw(lukBack);

	window.draw(textLevel);

	//�÷��̾� ����
	window.draw(textStr);
	window.draw(textDex);
	window.draw(textAgi);
	window.draw(textLuk);

	window.draw(textValueStr);
	window.draw(textValueDex);
	window.draw(textValueAgi);
	window.draw(textValueLuk);

	window.draw(textLevelStr);
	window.draw(textLevelDex);
	window.draw(textLevelAgi);
	window.draw(textLevelLuk);

	//�÷��̾� exp
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

	std::stringstream tmp;
	tmp << std::fixed << std::setprecision(4) << player->GetExp();
	textExp.setString(tmp.str() + "%");
	textExp.setPosition(expBar.getPosition().x + expBarbg.getLocalBounds().width * 0.5f, expBar.getPosition().y - 5.f);
	textExp.setCharacterSize(20);
	textExp.setFillColor(sf::Color::White);

	Utils::SetOrigin(textExp, Origins::MC);
}

void StatUiHud::UpdateStat()
{
	// STR
	textValueStr.setString("Damage +" + std::to_string(player->GetDamage()));
	textValueStr.setPosition({ textStr.getPosition().x + textStr.getLocalBounds().width + 30.f, textStr.getPosition().y});
	textValueStr.setCharacterSize(20);
	textValueStr.setFillColor(sf::Color::White);
	Utils::SetOrigin(textValueStr, Origins::ML);

	textLevelStr.setString("Lv." + std::to_string(player->GetStr()));
	textLevelStr.setPosition({ strBack.getLocalBounds().width - 150.f, strBack.getPosition().y + 10.f });
	textLevelStr.setCharacterSize(20);
	textLevelStr.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLevelStr, Origins::ML);

	// DEX
	std::stringstream tmpdex;
	tmpdex << std::fixed << std::setprecision(2) << player->GetCriticalDamagePlus();
	textValueDex.setString("Critical Damage +" + tmpdex.str() + "%");
	textValueDex.setPosition({ textDex.getPosition().x + textDex.getLocalBounds().width + 30.f, textDex.getPosition().y });
	textValueDex.setCharacterSize(20);
	textValueDex.setFillColor(sf::Color::White);
	Utils::SetOrigin(textValueDex, Origins::ML);

	textLevelDex.setString("Lv." + std::to_string(player->GetDex()));
	textLevelDex.setPosition({ dexBack.getLocalBounds().width - 150.f, dexBack.getPosition().y + 10.f });
	textLevelDex.setCharacterSize(20);
	textLevelDex.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLevelDex, Origins::ML);

	// AGI
	std::stringstream tmpagi;
	tmpagi << std::fixed << std::setprecision(2) << player->GetCriticalChance();
	textValueAgi.setString("Critical +" + tmpagi.str() + "%");
	textValueAgi.setPosition({ textAgi.getPosition().x + textAgi.getLocalBounds().width + 30.f, textAgi.getPosition().y });
	textValueAgi.setCharacterSize(20);
	textValueAgi.setFillColor(sf::Color::White);
	Utils::SetOrigin(textValueAgi, Origins::ML);

	textLevelAgi.setString("Lv." + std::to_string(player->GetAgi()));
	textLevelAgi.setPosition({ agiBack.getLocalBounds().width - 150.f, agiBack.getPosition().y + 10.f });
	textLevelAgi.setCharacterSize(20);
	textLevelAgi.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLevelAgi, Origins::ML);

	// LUK
	std::stringstream tmpluk;
	tmpluk << std::fixed << std::setprecision(2) << player->GetRewardChance();
	textValueLuk.setString("Reward +" + tmpluk.str() + "%");
	textValueLuk.setPosition({ textLuk.getPosition().x + textLuk.getLocalBounds().width + 30.f, textLuk.getPosition().y });
	textValueLuk.setCharacterSize(20);
	textValueLuk.setFillColor(sf::Color::White);
	Utils::SetOrigin(textValueLuk, Origins::ML);

	textLevelLuk.setString("Lv." + std::to_string(player->GetLuk()));
	textLevelLuk.setPosition({ lukBack.getLocalBounds().width - 150.f, lukBack.getPosition().y + 10.f });
	textLevelLuk.setCharacterSize(20);
	textLevelLuk.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLevelLuk, Origins::ML);
}

void StatUiHud::SetStat()
{
	textStr.setString("STR");
	textStr.setPosition({ strBack.getPosition().x + 10.f, strBack.getPosition().y + strBack.getLocalBounds().height * 0.5f - 7.f});
	textStr.setCharacterSize(30);
	textStr.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textStr, Origins::ML);

	textDex.setString("DEX");
	textDex.setPosition({ dexBack.getPosition().x + 10.f, dexBack.getPosition().y + dexBack.getLocalBounds().height * 0.5f - 7.f });
	textDex.setCharacterSize(30);
	textDex.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textDex, Origins::ML);

	textAgi.setString("AGI");
	textAgi.setPosition({ agiBack.getPosition().x + 10.f, agiBack.getPosition().y + agiBack.getLocalBounds().height * 0.5f - 7.f });
	textAgi.setCharacterSize(30);
	textAgi.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textAgi, Origins::ML);

	textLuk.setString("LUK");
	textLuk.setPosition({ lukBack.getPosition().x + 10.f, lukBack.getPosition().y + lukBack.getLocalBounds().height * 0.5f - 7.f });
	textLuk.setCharacterSize(30);
	textLuk.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textLuk, Origins::ML);
}
