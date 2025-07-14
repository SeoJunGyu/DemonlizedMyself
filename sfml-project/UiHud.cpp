#include "stdafx.h"
#include "UiHud.h"
#include "Button.h"

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
	topBack.setFillColor(sf::Color(32, 43, 61, 200));

	back.setSize({ size.x, size.y * 0.5f });
	back.setPosition({ 0.f, size.y * 0.5f });
	back.setFillColor(sf::Color(32, 43, 61, 255));

	// 상단 UI 배치
	
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	second = 0;
	time = 0.f;

	textLevel.setFont(FONT_MGR.Get(fontId));
	textTime.setFont(FONT_MGR.Get(fontId));
}

void UiHud::Update(float dt)
{
	UpdateTextTime(dt);
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(topBack);
	window.draw(back);
	window.draw(textTime);
	window.draw(textLevel);
}

void UiHud::UpdateTextTime(float time)
{
	if (time / 60.f == 1)
	{
		second++;
		time = 0;
	}
	textTime.setString(std::to_string(second) + "초" + std::to_string(time));
}

void UiHud::SetTextTime(float time)
{
	textTime.setString(std::to_string(second) + "초" + std::to_string(time));
	textTime.setPosition(topBack.getLocalBounds().width, topBack.getLocalBounds().height + 30);
	textTime.setCharacterSize(20);
	textTime.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(textTime, Origins::TR);
}

void UiHud::SetTextLevel(int level)
{
	textLevel.setString("Lv " + std::to_string(level));
	textLevel.setPosition(topBack.getPosition().x + 10, topBack.getPosition().y + 30);
	textLevel.setCharacterSize(10);
	textLevel.setFillColor(sf::Color::White);

	Utils::SetOrigin(textLevel, Origins::TL);
}
