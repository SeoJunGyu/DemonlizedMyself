#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "SceneGame.h"

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
			
		}
	);

	animator.AddEvent("Attack", 5,
		[this]()
		{
			SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
			//Monster* monster = (Monster*)SCENE_MGR.GetCurrentScene()->FindGameObject("Monster");
			if (!scene)
			{
				return;
			}

			for (Monster* monster : scene->GetMonsters())
			{
				if (!monster->GetActive())
				{
					continue;
				}

				if (Utils::CheckCollision(hitBox.rect, monster->GetHitBox().rect))
				{
					monster->OnDamage(damage);
					//std::cout << monster->GetHp() << std::endl;
				}
			}
		}
	);

	animator.AddEvent("Attack", 9,
		[this]()
		{
			SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
			//Monster* monster = (Monster*)SCENE_MGR.GetCurrentScene()->FindGameObject("Monster");
			if (!scene)
			{
				return;
			}

			for (Monster* monster : scene->GetMonsters())
			{
				if (!monster->GetActive())
				{
					continue;
				}

				if (Utils::CheckCollision(hitBox.rect, monster->GetHitBox().rect))
				{
					monster->OnDamage(damage);
					//std::cout << monster->GetHp() << std::endl;
				}
			}
		}
	);
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else
	{
		sceneGame = nullptr;
	}

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.Play("animations/warrior_Run.csv"); //아이들 애이메이션 경로 넘겨서 플레이
	SetOrigin(Origins::BC);
	SetPosition({0.f, 0.f});
	SetRotation(0.f);

	speed = 300.f;
	hp = maxHp;
}

void Player::Update(float dt)
{
	//애니메이션 재생 + 이동
	animator.Update(dt); //애니메이터 호출

	velocity = direction * speed;
	position += velocity * dt;

	SetPosition(position);

	//Monster* monster = (Monster*)SCENE_MGR.GetCurrentScene()->FindGameObject("Monster");
	const auto list = sceneGame->GetMonsters();
	isBattle = false;

	// Ani
	for (auto monster : list)
	{
		if (monster->GetActive() && Utils::CheckCollision(hitBox.rect, monster->GetHitBox().rect))
		{
			isBattle = true;
			if (animator.GetCurrentClipId() == "Run")
			{
				animator.Play("animations/warrior_Attack.csv");
				speed = 0.f;
			}
			
			break;
		}
	}

	if (!isBattle && animator.GetCurrentClipId() == "Attack")
	{
		animator.Play("animations/warrior_Run.csv");
		speed = 300.f;
	}

	bound = GetLocalBounds();
	bound.width *= 0.5f;
	hitBox.UpdateTransform(body, bound);

	//std::cout << animator.GetCurrentClipId() << std::endl;
	//std::cout << animator.IsPlaying() << std::endl;
	std::cout << GetPosition().x << std::endl;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::OnDamage(int damage)
{
	if (!isAlive)
	{
		return;
	}

	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		hp = 0;
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}