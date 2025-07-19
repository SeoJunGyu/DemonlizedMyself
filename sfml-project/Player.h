#pragma once
#include "GameObject.h"

class SceneGame;
class Monster;
class Skill;

class Player :
    public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f direction = {1.f, 0.f};

	HitBox hitBox;
	sf::FloatRect bound; //히트박스 크기설정용

	SceneGame* sceneGame;
	Monster* monster;
	Skill* skill;

	//플래그 변수
	bool isBattle = false;
	bool isAlive = true;
	bool isHit = false;
	bool drawSkill = false;

	//배틀 설정 변수
	float speed = 300.f;
	int damage = 20;
	int hp = 0;
	int maxHp = 100;
	float attackInterval = 0.f;
	float attackTimer = 0.f;

	float exp = 0.f;
	float baseExp = 40.f;
	float maxExp = 100.f; //100.f : 1레벨 최소 경험치

	int level = 1;
	int gold = 0;
	int gem = 0;
	int statPoints = 0;

	int strLevel = 0;
	int dexLevel = 0;
	int agiLevel = 0;
	int lukLevel = 0;

	float critChance = 0.f;
	float critDamagePlus = 1.f;
	float rewardChance = 0.f;

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
	void OnDie();

	bool GetAlive() const { return isAlive; }
	void SetAlive(bool live) { isAlive = live; }

	// Data Getter / Setter
	int GetHp() const { return hp; }
	int GetMaxHp() const { return maxHp; }

	float GetExp() const { return exp; }
	float GetMaxExp() const { return maxExp; }
	void AddExp(float amount);

	int GetLevel() const { return level; }

	int GetGold() const { return gold; }
	int GetGem() const { return gem; }

	void SetStr(int str);
	int GetStr() const { return strLevel; }
	void SetDex(float dex);
	int GetDex() const { return dexLevel; }
	void SetAgi(float agi);
	int GetAgi() const { return agiLevel; }
	void SetLuk(int luk);
	int GetLuk() const { return lukLevel; }

	int GetDamage() const { return damage; }
	float GetCriticalChance() const { return critChance; }
	float GetCriticalDamagePlus() const { return critDamagePlus; }
	float GetRewardChance() const { return rewardChance; }

	void SetStatPoint(int minusPoint) { statPoints -= minusPoint; }
	int GetStatPoint() const { return statPoints; }
	void StatReset();
};

