#pragma once
#include "GameObject.h"

class Player :
    public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	sf::Vector2f gravity = { 0.f, 500.f }; //ม฿ทย
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f direction = {1.f, 0.f};

	HitBox hitBox;
	sf::FloatRect bound;

	bool isBattle = false;
	bool isAlive = true;

	float speed = 300.f;
	int damage;
	int hp;
	int maxHp;
	float attackInterval = 0.f;
	float attackTimer = 0.f;

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

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	const HitBox& GetHitBox() { return hitBox; }
	void OnDamage(int damage);

	bool GetAlive() const { return isAlive; }
	void SetAlive(bool live) { isAlive = live; }
};

