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
	animator.SetTarget(&body); //������ ��������Ʈ�� �ִϸ����Ϳ� ����

	//idle�� 0��? �����ӿ� ȣ��ȴ�.
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

	animator.Play("animations/HeroKnight_Idle.csv"); //���̵� ���̸��̼� ��� �Ѱܼ� �÷���

	SetOrigin(Origins::BC);
	SetPosition({ 500.f, 0.f });
	SetRotation(0.f);

	hp = maxHp;
}

void Monster::Update(float dt)
{
	animator.Update(dt); //�ִϸ����� ȣ��

	if (animator.GetCurrentClipId() == "Attack") //�¿�Ű �ȴ��� ������ �ִ� �ڸ� 
	{
		if (!isBattle)
		{
			animator.Play("animations/HeroKnight_Idle.csv");
		}
	}

	attackTimer += dt;
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
		{
			isBattle = true;
			animator.Play("animations/HeroKnight_Attack.csv");
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
		std::cout << hp << std::endl;
	}
	std::cout << hp << std::endl;
}
