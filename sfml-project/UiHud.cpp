#include "stdafx.h"
#include "UiHud.h"
#include "Button.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::Init()
{
	auto size = FRAMEWORK.GetWindowSizeF();

	//최상단 : 46 69 85
	//상단 버튼 : 22 30 43
	//맨 밑 바탕 : 32 43 61
	//스텟 버튼 : 73 183 110
	back.setSize({ size.x, size.y * 0.5f });
	back.setPosition({ 0.f, size.y * 0.5f });
	back.setFillColor(sf::Color(32, 43, 61, 255));

	// 상단 UI 배치
	auto setupText = [&](sf::Text& text, const std::string& str, unsigned int size, sf::Vector2f pos, sf::Color color) {
		text.setFont(FONT_MGR.Get(fontId));
		text.setString(str);
		text.setCharacterSize(size);
		text.setFillColor(color);
		text.setPosition(pos);
		};

	setupText(textLevel, "Lv.10", 200, { 10.f, 10.f }, sf::Color::Black);
	setupText(textExp, "EXP: 50.0%", 20, { 120.f, 10.f }, sf::Color::White);
	setupText(textGold, "G: 1000", 20, { 300.f, 10.f }, sf::Color::Yellow);
	setupText(textGem, "Gem: 250", 20, { 420.f, 10.f }, sf::Color::Cyan);
	setupText(textDarkStone, "Dark: 50", 20, { 540.f, 10.f }, sf::Color(128, 0, 128));
	setupText(textHp, "HP: 130/130", 20, { 10.f, 40.f }, sf::Color::Red);

	// 플레이어 체력 표시
	float statStartY = size.y * 0.6f;
	float statX = 50.f;
	float spacingY = 50.f;
	setupText(statNameStr, "STR", 18, { statX, statStartY + 0 * spacingY }, sf::Color::White);
	setupText(statValueStr, "+76 ~ +114", 16, { statX + 60.f, statStartY + 0 * spacingY }, sf::Color::Green);
	setupText(statLevelStr, "Lv.19", 16, { statX + 200.f, statStartY + 0 * spacingY }, sf::Color::White);

	// 항복 버튼
	btnSurrender = new Button(fontId, "btnSurrender");
	btnSurrender->Init();
	btnSurrender->Reset();
	btnSurrender->setText("항복");
	btnSurrender->setShapeSize({ 80.f, 40.f });
	btnSurrender->setShapePosition({ size.x - 100.f, 60.f });
	btnSurrender->setShapeFillColor(sf::Color(128, 40, 40));
	btnSurrender->setTextPosition(btnSurrender->GetShape());
	btnSurrender->setTextOrigin(Origins::MC);

	// 하단 탭 버튼들 (스탯, 강화)
	btnStat = new Button(fontId, "btnStat");
	btnStat->Init();
	btnStat->Reset();
	btnStat->setText("스탯");
	btnStat->setShapeSize({ 80.f, 40.f });
	btnStat->setShapePosition({ 80.f, size.y - 60.f });
	btnStat->setShapeFillColor(sf::Color(73, 183, 110));
	btnStat->setTextPosition(btnStat->GetShape());
	btnStat->setTextOrigin(Origins::MC);

	btnEnhance = new Button(fontId, "btnEnhance");
	btnEnhance->Init();
	btnEnhance->Reset();
	btnEnhance->setText("강화");
	btnEnhance->setShapeSize({ 80.f, 40.f });
	btnEnhance->setShapePosition({ 180.f, size.y - 60.f });
	btnEnhance->setShapeFillColor(sf::Color(73, 183, 110));
	btnEnhance->setTextPosition(btnEnhance->GetShape());
	btnEnhance->setTextOrigin(Origins::MC);

	//하단
	btnStrUp = new Button(fontId, "btnStrUp");
	btnStrUp->Init();
	btnStrUp->Reset();
	btnStrUp->setText("+");
	btnStrUp->setShapeSize({ 30.f, 30.f });
	btnStrUp->setShapePosition({ 300.f, size.y * 0.6f + 0 * 50.f });
	btnStrUp->setShapeFillColor(sf::Color(100, 200, 100));
	btnStrUp->setTextPosition(btnStrUp->GetShape());
	btnStrUp->setTextOrigin(Origins::MC);
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
}

void UiHud::Update(float dt)
{
	std::cout << textLevel.getPosition().x << std::endl;
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(textLevel);
}