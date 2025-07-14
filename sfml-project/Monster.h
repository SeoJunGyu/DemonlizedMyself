#pragma once
#include "GameObject.h"

class Player;

class Monster :
    public GameObject
{
public:
	enum Type
	{
		HeroKnight,
		Worrior,
	};
	static const int TotalType = 2;

protected:
	sf::Sprite body;
	Animator animator;

	Player* player = nullptr;
	HitBox hitBox;
	sf::FloatRect bound;

	Type type = Type::HeroKnight;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarbg;
	sf::Vector2f hpBarOffset = { 0.f, 5.f };
	float per = 0.f;

	//플래그 변수
	bool isBattle = false;
	bool isAlive = true;

	//배틀 설정 변수
	int damage = 10;
	int hp = 0;
	int maxHp = 100;
	float attackInterval = 0.f;
	float attackTimer = 0.f;

public:
	Monster(const std::string& name = "");
	virtual ~Monster() = default;

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

	int GetHp() const { return hp; }
	void UpdateHpBar();

	Animator GetAnimator() const { return animator; }

	void SetType(Type type);
};

