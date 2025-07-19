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
	animator.SetTarget(&body);

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
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);

	SetPosition({ 0.f, 0.f });
	SetScale({ 3.f, 3.f });

	damage = 0;
	lifeTime = 0.f;
	SetActive(false);

	targetMonster = nullptr;

	animator.SetTarget(&body);
	//animator.Play("animations/skill_Explode.csv");
	
}

void Skill::Update(float dt)
{
	hitbox.UpdateTransform(body, GetLocalBounds());

	lifeTime += dt;
	animator.Update(dt);

	if (targetMonster && !targetMonster->GetActive())
	{
		if (lifeTime > duration)
		{
			SetActive(false);
		}
		return;
	}
	
	if (!targetMonster)
	{
		for (auto monster : sceneGame->GetMonsters())
		{
			if (!monster->GetActive())
			{
				return;
			}

			bool skillHit = Utils::CheckCollision(hitbox.rect, monster->GetHitBox().rect);
			bool playerHit = Utils::CheckCollision(player->GetHitBox().rect, monster->GetHitBox().rect);

			if (skillHit && playerHit)
			{
				targetMonster = monster;
				SetPosition({ monster->GetPosition().x, -60.f });
				//monster->OnDamage(damage);
				break;
			}
		}
	}
	
	if (targetMonster)
	{
		//targetMonster->OnDamage(damage);
		SetPosition({ targetMonster->GetPosition().x, -60.f });
	}
	
	if (lifeTime > duration)
	{
		SetActive(false);
	}

	std::cout << "스킬 위치: " << player->GetPosition().x << ", " << player->GetPosition().y << "\n";
}

void Skill::Draw(sf::RenderWindow& window)
{
	if (isDraw)
	{
		window.draw(body);
		hitbox.Draw(window);
	}

	
}
