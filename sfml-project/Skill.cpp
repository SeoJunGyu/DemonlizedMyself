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
	sortingOrder = 1;
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

}

void Skill::Update(float dt)
{
	lifeTime += dt;
	
	for (auto monster : sceneGame->GetMonsters())
	{
		if (monster->GetActive() && Utils::CheckCollision(hitbox.rect, monster->GetHitBox().rect))
		{
			SetPosition(monster->GetPosition());
			monster->OnDamage(damage);
			return;
		}
	}
	if (lifeTime > duration)
	{
		SetActive(false);
	}
}

void Skill::Draw(sf::RenderWindow& window)
{
	if (isDraw)
	{
		window.draw(body);
		hitbox.Draw(window);
	}
}