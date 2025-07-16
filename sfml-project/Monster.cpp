#include "stdafx.h"
#include "Monster.h"
#include "Player.h"
#include "SceneGame.h"

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

	switch (type)
	{
	case Monster::HeroKnight:
		animator.AddEvent("Attack", 2,
			[this]()
			{
				SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
				if (!scene)
				{
					return;
				}

				if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
				{
					if (!(player->GetHp() == 0))
					{
						SOUND_MGR.PlaySfx(buffer);
						player->OnDamage(damage);
					}
				}
			}
		);

		animator.AddEvent("Attack", 7,
			[this]()
			{
				SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
				if (!scene)
				{
					return;
				}

				if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
				{
					if (!(player->GetHp() == 0))
					{
						SOUND_MGR.PlaySfx(buffer);
						player->OnDamage(damage);
					}
				}
			}
		);
		break;
	case Monster::Worrior:
		animator.AddEvent("Attack", 5,
			[this]()
			{
				SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
				if (!scene)
				{
					return;
				}

				if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
				{
					player->OnDamage(damage);
				}
			}
		);

		animator.AddEvent("Attack", 9,
			[this]()
			{
				SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
				if (!scene)
				{
					return;
				}

				if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
				{
					player->OnDamage(damage);
				}
			}
		);
		break;
	}

	animator.AddEvent("Death", 10,
		[this]()
		{
			hp = 0;
			isAlive = false;
			SetActive(false);
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

	hpBarbg.setFillColor(sf::Color::White);
	hpBarbg.setSize({ 30.f, 5.f });
	Utils::SetOrigin(hpBarbg, Origins::ML);

	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize({ 30.f, 5.f });
	Utils::SetOrigin(hpBar, Origins::ML);

	per = hpBar.getSize().x / hp;
}

void Monster::Update(float dt)
{
	animator.Update(dt); //애니메이터 호출

	if (hp != 0 && animator.GetCurrentClipId() == "Attack")
	{

	}

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

	UpdateHpBar();

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
	if (hp != maxHp && isAlive)
	{
		window.draw(hpBarbg);
		window.draw(hpBar);
	}
}

void Monster::OnDamage(int damage)
{
	if (!isAlive)
	{
		return;
	}

	SOUND_MGR.PlaySfx("audios/hit.wav");
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		animator.Play(aniIdDeath);
	}
	//std::cout << hp << std::endl;
}

void Monster::UpdateHpBar()
{
	hpBarbg.setPosition(hpBar.getPosition());
	hpBar.setPosition(position.x, GetGlobalBounds().top + GetGlobalBounds().height + hpBarOffset.y);

	float fill = per * hp;
	hpBar.setSize({ fill, 5 });
}

void Monster::SetType(Type type)
{
	this->type = type;

	switch (type)
	{
	case Monster::HeroKnight:
		animator.Play("animations/HeroKnight_Idle.csv");
		damage = 3;
		maxHp = 120;
		buffer = SOUNDBUFFER_MGR.Get("audios/Hero_whoosh.wav");
		aniIdDeath = "animations/HeroKnight_Death.csv";
		aniIdIdle = "animations/HeroKnight_Idle.csv";
		aniIdAttack = "animations/HeroKnight_Attack.csv";
		break;
	case Monster::Worrior:
		animator.Play("animations/warrior_Idle.csv");
		damage = 3;
		maxHp = 100;
		buffer = SOUNDBUFFER_MGR.Get("audios/Worrior_whoosh.wav");
		aniIdDeath = "animations/warrior_Death.csv";
		aniIdIdle = "animations/warrior_Idle.csv";
		aniIdAttack = "animations/warrior_Attack.csv";
		break;
	}

}
