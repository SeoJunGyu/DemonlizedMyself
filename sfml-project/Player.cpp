#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Player::Init()
{
	animator.SetTarget(&body); //갱신할 스프라이트를 애니메이터에 설정

	//idle의 0번? 프레임에 호출된다.
	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);
}

void Player::Release()
{
}

void Player::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.Play("animations/warrior_Idle.csv"); //아이들 애이메이션 경로 넘겨서 플레이
	SetOrigin(Origins::BC);
	SetPosition({0.f, 0.f});
	SetRotation(0.f);
}

void Player::Update(float dt)
{
	//애니메이션 재생 + 이동
	animator.Update(dt); //애니메이터 호출

	velocity = direction * speed;
	position += velocity * dt;

	SetPosition(position);

	// Ani
	if (animator.GetCurrentClipId() == "Idle") //좌우키 안눌린 가만히 있는 자리 
	{
		if (!isBattle)
		{
			animator.Play("animations/warrior_Run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		
	}

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}