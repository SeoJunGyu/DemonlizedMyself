#include "stdafx.h"
#include "ButtonGo.h"

ButtonGo::ButtonGo(const std::string& name)
	: GameObject(name), fontId("fonts/Maplestory_Light.ttf")
{
    shape.setSize({ 100.f, 40.f });
    shape.setFillColor(normalColor);
    shape.setOrigin(shape.getSize() * 0.5f);

    text.setFont(FONT_MGR.Get(fontId));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setOrigin(0.5f, 0.5f);
}

void ButtonGo::SetPosition(const sf::Vector2f& pos)
{
    GameObject::SetPosition(pos);
    shape.setPosition(pos);
    text.setPosition(pos);
}

void ButtonGo::SetOrigin(const sf::Vector2f& o)
{
    GameObject::SetOrigin(o);
    shape.setOrigin(o);
}

void ButtonGo::SetOrigin(Origins preset)
{
    GameObject::SetOrigin(preset);
    if (preset != Origins::Custom)
    {
        Utils::SetOrigin(shape, preset);
    }
}

void ButtonGo::Init()
{
}

void ButtonGo::Release()
{
}

void ButtonGo::Reset()
{
}

void ButtonGo::Update(float dt)
{
    sf::Vector2i mousePixel = InputMgr::GetMousePosition();
    sf::Vector2f mouseWorld = FRAMEWORK.GetWindow().mapPixelToCoords(mousePixel);

    isHovered = shape.getGlobalBounds().contains(mouseWorld);

    if (isHovered)
    {
        shape.setFillColor(hoverColor);

        if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
        {
            isPressed = true;
        }

        if (isPressed && InputMgr::GetMouseButtonUp(sf::Mouse::Left))
        {
            isPressed = false;
            if (onClick)
            {
                onClick();
            }
        }
    }
    else
    {
        isPressed = false;
        shape.setFillColor(normalColor);
    }
}

void ButtonGo::Draw(sf::RenderWindow& window)
{
    if (!active)
    {
        return;
    }
    if (!text.getFont()) return;
    window.draw(shape);
    window.draw(text);
}

void ButtonGo::SetText(const std::string& str)
{
    text.setString(str);
    Utils::SetOrigin(text, Origins::MC);
}

void ButtonGo::SetFontSize(unsigned int size)
{
    text.setCharacterSize(size);
    Utils::SetOrigin(text, Origins::MC);
}

void ButtonGo::SetSize(const sf::Vector2f& size)
{
    shape.setSize(size);
    SetOrigin(Origins::MC);
}

void ButtonGo::SetFillColor(const sf::Color& color)
{
    normalColor = color;
    shape.setFillColor(color);
}

void ButtonGo::SetClick(std::function<void()> func)
{
    onClick = func;
}
