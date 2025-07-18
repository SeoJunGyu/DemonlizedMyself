#pragma once
#include "GameObject.h"

class SceneGame;
class Monster;
class Player;

class Skill :
    public GameObject
{
protected:
	sf::Sprite body;
	sf::String texId = "graphics/Explode.png";
	Animator animator;

	float lifeTime = 0.f;
	float duration = 1.f;
	float damage = 0.f;
	bool isActive = false;

	SceneGame* sceneGame;
	Monster* monster;
	Player* player;
	HitBox hitbox;

	//test
	bool isDraw = false;

public:
	Skill(const std::string& name = "");
	virtual ~Skill() = default;

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
		return { 0.f, 0.f, 0.f, 0.f };
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return { 0.f, 0.f, 0.f, 0.f };
	}

	HitBox& GetHitbox() { return hitbox; }

	//test
	void SetDraw(bool draw) { isDraw = draw; }
};

