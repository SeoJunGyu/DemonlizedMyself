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
	Animator animator;

	float lifeTime = 0.f;
	float duration = 1.f;
	float damage = 0.f;
	bool isActive = false;

	SceneGame* sceneGame;
	Monster* monster;
	Monster* targetMonster = nullptr; //한 몬스터만 타겟으로 삼기
	Player* player;
	HitBox hitbox;

	//test
	bool isDraw = false;

	float coolDown = 2.f;
	float coolDownTimer = 0.f;
	bool skillReady = false;

	float attackInterval = 0.f;
	float attackTimer = 0.f;

	bool isEquipped = false;

	int count = 0;

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
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	HitBox& GetHitbox() { return hitbox; }

	//test
	//void SetDraw(bool draw) { isDraw = draw; }
	void SetLifeTime(float lifeTime) { this->lifeTime = lifeTime; }

	float GetLifeTime() const { return lifeTime; }
	float GetDuration() const { return duration; }

	bool IsReady() const { return skillReady; }
	void TryUse();

	void SetEquipped(bool value) { isEquipped = value; }
	bool IsEquipeed() const { return isEquipped; }

	void Use();

};

