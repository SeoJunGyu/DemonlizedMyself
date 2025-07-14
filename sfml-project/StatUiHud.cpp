#include "stdafx.h"
#include "StatUiHud.h"

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
}

void StatUiHud::Update(float dt)
{
}

void StatUiHud::Draw(sf::RenderWindow& window)
{
	window.draw(back);
}
