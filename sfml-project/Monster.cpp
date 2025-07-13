#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

Monster::Monster(const std::string& name)
	: GameObject(name)
{
}

void Monster::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Monster::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Monster::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Monster::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Monster::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Monster::Init()
{
	animator.SetTarget(&body); //갱신할 스프라이트를 애니메이터에 설정

	//idle의 0번? 프레임에 호출된다.
	animator.AddEvent("Idle", 0,
		[]()
		{
			
		}
	);
}

void Monster::Release()
{
}

void Monster::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	SetType(type);

	SetOrigin(Origins::BC);
	SetPosition({ 500.f, 0.f });
	SetRotation(0.f);

	hp = maxHp;
}

void Monster::Update(float dt)
{
	animator.Update(dt); //애니메이터 호출

	if (animator.GetCurrentClipId() == "Attack") //좌우키 안눌린 가만히 있는 자리 
	{
		if (!isBattle)
		{
			switch (type)
			{
			case Monster::HeroKnight:
				animator.Play("animations/HeroKnight_Idle.csv");
				break;
			case Monster::Worrior:
				animator.Play("animations/warrior_Idle.csv");
				break;
			default:
				break;
			}
		}
	}

	attackTimer += dt;
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
		{
			isBattle = true;
			switch (type)
			{
			case Monster::HeroKnight:
				animator.Play("animations/HeroKnight_Attack.csv");
				break;
			case Monster::Worrior:
				animator.Play("animations/warrior_Attack.csv");
				break;
			default:
				break;
			}
			//player->OnDamage(damage);
			attackTimer = 0.f;
		}

	}

	bound = player->GetLocalBounds();
	//bound.width = GetLocalBounds().width * 0.5f;
	//bound.height = GetLocalBounds().height * 0.5f;
	
	hitBox.UpdateTransform(body, bound);
	
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Monster::OnDamage(int damage)
{
	if (!isAlive)
	{
		return;
	}

	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		hp = 0;
		isAlive = false;
		SetActive(false);
	}
	//std::cout << hp << std::endl;
}

void Monster::SetType(Type type)
{
	this->type = type;

	switch (type)
	{
	case Monster::HeroKnight:
		animator.Play("animations/HeroKnight_Idle.csv");
		damage = 20;
		maxHp = 100;
		break;
	case Monster::Worrior:
		animator.Play("animations/warrior_Idle.csv");
		damage = 20;
		maxHp = 100;
		break;
	}

}
