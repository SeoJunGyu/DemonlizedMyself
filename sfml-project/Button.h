#pragma once
#include "TextGo.h"
#include "HitBox.h"

class SceneGame;

class Button 
	: public TextGo
{
protected:
	sf::RectangleShape mouse;
	sf::RectangleShape shape;
	std::string fontId;
	sf::Color color;

	HitBox shapeHitBox;
	HitBox textHitBox;
	HitBox mouseHitBox;

	std::function<void()> func = nullptr;
	bool isPressed = false;
public:


	Button(const std::string& fontId = "", const std::string& name = "");
	~Button() override = default;

	// 텍스트 설정 함수
	void setText(std::string text);
	void setCharacterSize(sf::RectangleShape rect);
	void setTextFillColor(sf::Color color);
	void setTextPosition(sf::RectangleShape rect);
	void setTextOrigin(Origins origin);
	
	void setButtonPtr(std::function<void()> func) { this->func = func; }

	// shape 설정 함수
	void setShapeSize(sf::Vector2f size);
	void setShapeFillColor(sf::Color color);
	void setShapePosition(sf::Vector2f pos);
	void setShapeOrigin();

	bool GetIsPressed() { return isPressed; }
	sf::RectangleShape GetShape() { return shape; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetGlobalBounds() const override
	{
		return shape.getGlobalBounds();
	}

	sf::FloatRect GetLocalBounds() const override
	{
		return shape.getLocalBounds();
	}
};

