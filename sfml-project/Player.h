#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	sf::Vector2f gravity = { 0.f, 500.f }; //중력
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true; //바닥 충돌 체크
	float speed = 500.f;

public:
	Player(const std::string& name = "");
	virtual ~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

