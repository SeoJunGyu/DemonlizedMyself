#pragma once
#include "GameObject.h"

class ButtonGo :
    public GameObject
{
protected:
	sf::RectangleShape shape;
	sf::Text text;

	sf::Color normalColor = sf::Color(132, 153, 172);
	sf::Color hoverColor = sf::Color(150, 150, 150);
	sf::Color pressedColor = sf::Color(200, 200, 200);

	std::function<void()> onClick = nullptr;

	bool isHovered = false;
	bool isPressed = false;

	std::string fontId = "fonts/Maplestory_Light.ttf";

public:
	ButtonGo(const std::string& name = "");
	virtual ~ButtonGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetText(const std::string& str);
	void SetFontSize(unsigned int size);
	void SetSize(const sf::Vector2f& size);
	void SetFillColor(const sf::Color& color);
	void SetClick(std::function<void()> func) { onClick = func; }
	void SetFont(std::string fontId);

};

