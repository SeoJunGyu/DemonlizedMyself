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

	// 하단 배경
	back.setPosition({ 0.f, size.y * 0.5f });

	strBack.setPosition({ 15.f, back.getPosition().y + 130.f });
	dexBack.setPosition({ 15.f, back.getPosition().y + 220.f });
	agiBack.setPosition({ 15.f, back.getPosition().y + 310.f });
	lukBack.setPosition({ 15.f, back.getPosition().y + 400.f });

	// 스킬창 배경
	slotBack.setSize({ size.x, 63.f });
	slotBack.setFillColor(sf::Color::Black);
	slotBack.setPosition({ 0.f, back.getPosition().y - slotBack.getLocalBounds().height });
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

	textNameStatPoint.setFont(FONT_MGR.Get(fontId));
	textStatPoint.setFont(FONT_MGR.Get(fontId));

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

	playerIcon.setTexture(TEXTURE_MGR.Get(playerIcontexId));
	iconFrame.setTexture(TEXTURE_MGR.Get(texIdFrame));
	back.setTexture(TEXTURE_MGR.Get(texIdBack));
	strBack.setTexture(TEXTURE_MGR.Get(texIdstatBack));
	dexBack.setTexture(TEXTURE_MGR.Get(texIdstatBack));
	agiBack.setTexture(TEXTURE_MGR.Get(texIdstatBack));
	lukBack.setTexture(TEXTURE_MGR.Get(texIdstatBack));

	// Player ExpBar
	expBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	expBarbg.setSize({ 300.f, 20.f });
	Utils::SetOrigin(expBarbg, Origins::ML);

	expBar.setFillColor(sf::Color(255, 183, 0, 255));
	expBar.setSize({ 300.f, 20.f });
	Utils::SetOrigin(expBar, Origins::ML);

	expPer = expBar.getSize().x / player->GetMaxExp();

	SetStat();

	// 스킬창 배치
	if (skillSlots.empty())
	{
		for (int i = 0; i < slotCount; i++)
		{
			SkillSlot slot;
			slot.texId = texIdSlot;
			slot.spriteFrame.setTexture(TEXTURE_MGR.Get(texIdSlot));
			slot.spriteFrame.setPosition({ 80.f + i * 60.f, back.getPosition().y - slot.spriteFrame.getLocalBounds().height + 30.f });
			Utils::SetOrigin(slot.spriteFrame, Origins::MC);

			slot.sprite.setTexture(TEXTURE_MGR.Get(texIdSlot));
			slot.sprite.setPosition({ 80.f + i * 60.f, back.getPosition().y - slot.spriteFrame.getLocalBounds().height + 30.f });
			Utils::SetOrigin(slot.sprite, Origins::MC);

			skillSlots.push_back(slot);
		}
	}
	else
	{
		for (int i = 0; i < slotCount; i++)
		{
			skillSlots[i].spriteFrame.setTexture(TEXTURE_MGR.Get(texIdSlot));
			skillSlots[i].spriteFrame.setPosition({ 80.f + i * 60.f, back.getPosition().y - skillSlots[i].spriteFrame.getLocalBounds().height + 30.f });
			Utils::SetOrigin(skillSlots[i].spriteFrame, Origins::MC);

			skillSlots[i].sprite.setTexture(TEXTURE_MGR.Get(skillSlots[i].texId));
			skillSlots[i].sprite.setPosition({ 80.f + i * 60.f, back.getPosition().y - skillSlots[0].spriteFrame.getLocalBounds().height + 30.f });
			Utils::SetOrigin(skillSlots[i].sprite, Origins::MC);
		}
	}

	/*
	
	*/

	int rowCount = 9;
	float spaceX = 70.f;
	float spaceY = 70.f;
	sf::Vector2f startPos = { 50.f, back.getPosition().y + 100.f };
	if (skillIcons.empty())
	{
		for (int i = 0; i < slotCount; i++)
		{
			int row = i / rowCount;
			int col = i % rowCount;

			SkillIcon icon;
			icon.texId = "graphics/Explode.png";
			icon.sprite.setTexture(TEXTURE_MGR.Get(icon.texId));
			icon.sprite.setPosition({ startPos.x + col * spaceX, startPos.y + row * spaceY });

			skillIcons.push_back(icon);
		}
	}
	else
	{
		for (int i = 0; i < slotCount; i++)
		{
			int row = i / rowCount;
			int col = i % rowCount;

			skillIcons[i].sprite.setTexture(TEXTURE_MGR.Get(skillIcons[i].texId));
			skillIcons[i].sprite.setPosition({ startPos.x + col * spaceX, startPos.y + row * spaceY });
		}
	}
	
}

void StatUiHud::Update(float dt)
{
	UpdateExpBar();
	UpdateStat();

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)InputMgr::GetMousePosition();

		for (auto& icon : skillIcons)
		{
			if (icon.sprite.getGlobalBounds().contains(mousePos))
			{
				selectedSkillIcon = &icon;
				break;
			}
		}

		if (selectedSkillIcon != nullptr)
		{
			for (auto& slot : skillSlots)
			{
				if (slot.sprite.getGlobalBounds().contains(mousePos))
				{

					slot.SetIcon(selectedSkillIcon->texId);
					selectedSkillIcon = nullptr; //선택 해체
					break;
				}
			}
		}
		else
		{
			for (auto& slot : skillSlots)
			{
				if (slot.sprite.getGlobalBounds().contains(mousePos))
				{
					slot.SetIcon(texIdSlot);
					break;
				}
			}
		}
	}
}

void StatUiHud::Draw(sf::RenderWindow& window)
{
	window.draw(back);

	//스킬창 및 스킬
	window.draw(slotBack);
	for (int i = 0; i < slotCount; i++)
	{
		window.draw(skillSlots[i].sprite);
		window.draw(skillSlots[i].spriteFrame);
	}

	/*
	
	*/
	if (isSkill)
	{
		for (int i = 0; i < slotCount; i++)
		{
			window.draw(skillIcons[i].sprite);
		}
	}

	//스탯 UI
	if (isStat)
	{
		window.draw(strBack);
		window.draw(dexBack);
		window.draw(agiBack);
		window.draw(lukBack);

		window.draw(playerIcon);
		window.draw(iconFrame);

		window.draw(textLevel);

		//플레이어 스탯
		window.draw(textNameStatPoint);
		window.draw(textStatPoint);

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

		//플레이어 exp
		window.draw(expBarbg);
		window.draw(expBar);
		window.draw(textExp);
	}
	
}

void StatUiHud::UpdateExpBar()
{
	// Exp Bar
	expBarbg.setPosition(expBar.getPosition());
	expBar.setPosition({ 110.f, back.getPosition().y + 100.f });

	float fill = expPer * player->GetExp();
	expBar.setSize({ fill, expBar.getSize().y });

	// TextLevel
	textLevel.setString("Lv. " + std::to_string(player->GetLevel()) + " " + player->GetName());
	textLevel.setPosition(expBar.getPosition().x + 10.f, expBar.getPosition().y - 40);
	textLevel.setCharacterSize(20);
	textLevel.setFillColor(sf::Color::White);

	Utils::SetOrigin(textLevel, Origins::TL);

	// TextExp
	std::stringstream tmp;
	tmp << std::fixed << std::setprecision(4) << player->GetExp() / player->GetMaxExp() * 100.f;
	textExp.setString(tmp.str() + "%");
	textExp.setPosition(expBar.getPosition().x + expBarbg.getLocalBounds().width * 0.5f, expBar.getPosition().y - 5.f);
	textExp.setCharacterSize(20);
	textExp.setFillColor(sf::Color::White);

	Utils::SetOrigin(textExp, Origins::MC);

	// PlayerIcon
	playerIcon.setPosition({ textLevel.getPosition().x - 70.f , textLevel.getPosition().y + 8.f });
	playerIcon.setScale({ 2.5f, 2.5f });

	iconFrame.setPosition({ playerIcon.getPosition().x - 7.f , playerIcon.getPosition().y - 7.f });
}

void StatUiHud::UpdateStat()
{
	auto size = FRAMEWORK.GetWindowSizeF();

	textNameStatPoint.setString("StatPoint");
	textNameStatPoint.setPosition({ size.x - 130.f, expBarbg.getPosition().y + expBarbg.getLocalBounds().height - 50.f});
	textNameStatPoint.setCharacterSize(20);
	textNameStatPoint.setFillColor(sf::Color::White);
	Utils::SetOrigin(textNameStatPoint, Origins::BR);

	textStatPoint.setString(std::to_string(player->GetStatPoint()));
	textStatPoint.setPosition({ size.x - 130.f, expBarbg.getPosition().y + expBarbg.getLocalBounds().height - 20.f });
	textStatPoint.setCharacterSize(20);
	textStatPoint.setFillColor(sf::Color::White);
	Utils::SetOrigin(textStatPoint, Origins::BR);

	// STR
	textValueStr.setString("Damage +" + std::to_string(player->GetDamage()));
	textValueStr.setPosition({ textStr.getPosition().x + textStr.getLocalBounds().width + 30.f, textStr.getPosition().y});
	textValueStr.setCharacterSize(20);
	textValueStr.setFillColor(sf::Color::White);
	Utils::SetOrigin(textValueStr, Origins::ML);

	textLevelStr.setString("Lv." + std::to_string(player->GetStr()));
	textLevelStr.setPosition({ strBack.getLocalBounds().width - 145.f, strBack.getPosition().y + 10.f });
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
	textLevelDex.setPosition({ dexBack.getLocalBounds().width - 145.f, dexBack.getPosition().y + 10.f });
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
	textLevelAgi.setPosition({ agiBack.getLocalBounds().width - 145.f, agiBack.getPosition().y + 10.f });
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
	textLevelLuk.setPosition({ lukBack.getLocalBounds().width - 145.f, lukBack.getPosition().y + 10.f });
	textLevelLuk.setCharacterSize(20);
	textLevelLuk.setFillColor(sf::Color::White);
	Utils::SetOrigin(textLevelLuk, Origins::ML);
}

void StatUiHud::SetStat()
{
	textStr.setString("STR");
	textStr.setPosition({ strBack.getPosition().x + 20.f, strBack.getPosition().y + strBack.getLocalBounds().height * 0.5f - 7.f});
	textStr.setCharacterSize(30);
	textStr.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textStr, Origins::ML);

	textDex.setString("DEX");
	textDex.setPosition({ dexBack.getPosition().x + 20.f, dexBack.getPosition().y + dexBack.getLocalBounds().height * 0.5f - 7.f });
	textDex.setCharacterSize(30);
	textDex.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textDex, Origins::ML);

	textAgi.setString("AGI");
	textAgi.setPosition({ agiBack.getPosition().x + 20.f, agiBack.getPosition().y + agiBack.getLocalBounds().height * 0.5f - 7.f });
	textAgi.setCharacterSize(30);
	textAgi.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textAgi, Origins::ML);

	textLuk.setString("LUK");
	textLuk.setPosition({ lukBack.getPosition().x + 20.f, lukBack.getPosition().y + lukBack.getLocalBounds().height * 0.5f - 7.f });
	textLuk.setCharacterSize(30);
	textLuk.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textLuk, Origins::ML);
}

void StatUiHud::SetUiChange()
{
	isStat = !isStat;
	isSkill = !isSkill;
}
