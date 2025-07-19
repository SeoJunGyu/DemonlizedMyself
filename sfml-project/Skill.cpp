#include "stdafx.h"
#include "Skill.h"
#include "SceneGame.h"
#include "Monster.h"
#include "Player.h"

Skill::Skill(const std::string& name)
	: GameObject(name)
{
}

void Skill::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Skill::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Skill::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Skill::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Skill::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Skill::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 10;

	animator.AddEvent("Skill", 10, [this]()
		{
			SetActive(false);
		}
	);
}

void Skill::Release()
{
}

void Skill::Reset()
{
	animator.SetTarget(&body);
	animator.SetSpeed(0.5f);

	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	//body.setTexture(TEXTURE_MGR.Get(texId), true);

	damage = 5;
	lifeTime = 0.f;
	SetActive(false);

	targetMonster = nullptr;

	animator.Play("animations/skill_Explode.csv");

	SetPosition({ 0.f, 0.f });
	SetScale({ 3.f, 3.f });
	SetOrigin(Origins::MC);

	skillReady = true;
	coolDown = 2.f;
	coolDownTimer = 0.f;

	attackInterval = 2.f;
	attackTimer = 0.f;
}

void Skill::Update(float dt)
{
	/*
	
	*/
	

	//std::cout << GetActive() << std::endl;
	animator.Update(dt);
	hitbox.UpdateTransform(body, GetLocalBounds());

	if (!GetActive())
	{
		if (!skillReady)
		{
			//std::cout << "쿨다운 진행중: " << coolDownTimer << " / " << coolDown << std::endl;
			coolDownTimer += dt;
			if (coolDownTimer >= coolDown)
			{
				skillReady = true;
				coolDownTimer = 0.f;
				//std::cout << "쿨다운 완료!" << std::endl;
			}
		}
		else
		{
			//std::cout << "스킬 준비 완료!" << count++ << std::endl;
		}
		return;
	}

	lifeTime += dt;

	if (!isEquipped)
	{
		SetActive(false);
		return;
	}

	if (targetMonster && !targetMonster->GetActive())
	{
		if (lifeTime > duration)
		{
			SetActive(false);
		}
		targetMonster = nullptr;
		return;
	}
	
	if (!targetMonster && sceneGame)
	{
		for (auto monster : sceneGame->GetMonsters())
		{
			if (!monster->GetActive())
			{
				continue;
			}

			//bool skillHit = Utils::CheckCollision(hitbox.rect, monster->GetHitBox().rect);
			bool playerHit = Utils::CheckCollision(player->GetHitBox().rect, monster->GetHitBox().rect);

			if (playerHit)
			{
				targetMonster = monster;
				SetPosition({ monster->GetPosition().x, -60.f });

				animator.Play("animations/skill_Explode.csv");
				//monster->OnDamage(damage);
				break;
			}
		}
	}
	
	if (targetMonster && !(targetMonster->GetHp() == 0))
	{
		attackTimer += dt;
		if (attackTimer > attackInterval)
		{
			targetMonster->OnDamage(damage);
			attackTimer = 0.f;
		}
		
		SetPosition({ targetMonster->GetPosition().x, -60.f });
	}

	if (lifeTime > duration)
	{
		//std::cout << "lifeTime 종료, SetActive(false) 호출됨\n";
		SetActive(false);
	}

	//std::cout << "스킬 위치: " << player->GetPosition().x << ", " << player->GetPosition().y << "\n";
}

void Skill::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Skill::TryUse()
{
	
	lifeTime = 0.f;

	if (!skillReady)
	{
		return;
	}
	SetActive(true);
	skillReady = false;
	coolDownTimer = 0.f;
	isEquipped = true;
	targetMonster = nullptr;

	animator.Play("animations/skill_Explode.csv");
}
