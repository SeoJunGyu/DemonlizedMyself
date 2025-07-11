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
			std::cout << "??" << std::endl;
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

	animator.Play("animations/warrior_Idle.csv"); //아이들 애이메이션 경로 넘겨서 플레이
	SetOrigin(Origins::BC);
	SetPosition({ 500.f, 0.f });
	SetRotation(0.f);
}

void Monster::Update(float dt)
{
	if (animator.GetCurrentClipId() == "Idle") //좌우키 안눌린 가만히 있는 자리 
	{
		if (!isBattle)
		{
			animator.Play("animations/warrior_Run.csv");
		}
	}

	attackTimer += dt;
	if (animator.GetCurrentClipId() == "Run")
	{
		if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
		{
			isBattle = true;
			animator.Play("animations/warrior_Attack.csv");
			//player->OnDamage(damage);
			attackTimer = 0.f;
		}
		
	}

	hitBox.UpdateTransform(body, GetLocalBounds());
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
	}
}
