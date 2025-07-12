#include "stdafx.h"
#include "Button.h"
#include "HitBox.h"
#include "SceneGame.h"

Button::Button(const std::string& fontId, const std::string& name) : TextGo("fonts/zombiecontrol.ttf" ,name)
{

}
void Button::setText(std::string text)
{
	SetString(text);
	shape.setSize({ this->text.getString().getSize() * ((float)this->text.getCharacterSize() * 0.5f) , (float)this->text.getCharacterSize() * 2.f});
	Utils::SetOrigin(shape, Origins::MC);

}
void Button::setCharacterSize(sf::RectangleShape rect)
{
	int size = (rect.getSize().x * 0.3f);
	SetCharacterSize(size);
}
void Button::setTextFillColor(sf::Color color)
{
	SetFillColor(color);
}
void Button::setTextPosition(sf::RectangleShape rect)
{
	SetPosition(rect.getPosition());
	
}
void Button::setTextOrigin(Origins origin)
{
	SetOrigin(origin);
}

void Button::setShapeSize(sf::Vector2f size)
{
	shape.setSize(size);
}

void Button::setShapeFillColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Button::setShapePosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
}

void Button::setShapeOrigin()
{
	shape.setOrigin(shape.getSize() * 0.5f);
}

void Button::Init()
{
	TextGo::Init();

}
void Button::Release()
{
}

void Button::Reset()
{
	TextGo::Reset();
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	
	mouse.setFillColor(sf::Color::Transparent);
	mouse.setOutlineColor(sf::Color::Transparent);
	mouse.setOutlineThickness(0.5f);
	mouse.setSize({ 50.f,50.f });
	mouse.setOrigin(mouse.getSize() * 0.5f);

	shapeHitBox.UpdateTransform(shape, shape.getLocalBounds());
	textHitBox.UpdateTransform(text, text.getGlobalBounds());
	color = shape.getFillColor();
}

void Button::Update(float dt)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
	sf::Vector2f worldPos = FRAMEWORK.GetWindow().mapPixelToCoords(pixelPos);
	mouse.setPosition(worldPos);
	mouseHitBox.UpdateTransform(mouse, mouse.getLocalBounds());
	

	if (Utils::CheckCollision(mouseHitBox.rect, textHitBox.rect))
	{
		text.setFillColor(sf::Color::Red);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			if (func != nullptr)
				func();
		}
	}
	else
	{
		text.setFillColor(sf::Color::White);
		isPressed = false;
	}

	if (Utils::CheckCollision(mouseHitBox.rect, shapeHitBox.rect))
	{
		text.setFillColor(sf::Color::Red);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			isPressed = true;
		}
	}
	else
	{
		text.setFillColor(sf::Color::White);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Transparent);
		isPressed = false;
	}
	
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(mouse);

	shapeHitBox.Draw(window);
	textHitBox.Draw(window);
	mouseHitBox.Draw(window);
	TextGo::Draw(window);
}
