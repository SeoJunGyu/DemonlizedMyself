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
				float baseDamage = damage;
				if (!monster->GetActive())
				{
					continue;
				}

				if (Utils::CheckCollision(hitBox.rect, monster->GetHitBox().rect))
				{
					if (!(monster->GetHp() == 0))
					{
						if (Utils::RandomRange(0.f, 1.f) < critChance)
						{
							SOUND_MGR.PlaySfx("audios/Player_whoosh.wav");
							damage *= critDamagePlus;
							sceneGame->StartSceenShake(0.3f, 20.f); //0.3초, 15강도
							monster->OnDamage(damage);
						}
						else
						{
							SOUND_MGR.PlaySfx("audios/Player_whoosh.wav");
							sceneGame->StartSceenShake(0.3f, 15.f); //0.3초, 15강도
							monster->OnDamage(damage);
						}
					}
					
					//std::cout << damage << std::endl;
				}
				damage = baseDamage;
			}
		}
	);

	animator.AddEvent("Attack", 8,
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
					if (!(monster->GetHp() == 0))
					{
						if (Utils::RandomRange(0.f, 1.f) < critChance)
						{
							SOUND_MGR.PlaySfx("audios/Player_whoosh.wav");
							damage *= critDamagePlus;
							sceneGame->StartSceenShake(0.3f, 20.f); //0.3초, 15강도
							monster->OnDamage(damage);
						}
						else
						{
							SOUND_MGR.PlaySfx("audios/Player_whoosh.wav");
							sceneGame->StartSceenShake(0.3f, 15.f); //0.3초, 15강도
							monster->OnDamage(damage);
						}
					}
					
					//std::cout << monster->GetHp() << std::endl;
				}
			}
		}
	);

	animator.AddEvent("Death", 10, [this]()
		{
			SOUNDBUFFER_MGR.Get("audios/Death.wav");
			hp = 0;
			Reset();
			SCENE_MGR.ChangeScene(SceneIds::Game);
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
	if (hp != 0 && animator.GetCurrentClipId() == "Death")
	{
		animator.Play("animations/warrior_Attack.csv");
		speed = 300.f;
	}

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
		
		AddExp(baseExp);

		if (Utils::RandomRange(0.f, 1.f) < rewardChance)
		{
			gold += lukLevel * 0.5f;
			gem += lukLevel * 0.3;
		}
		else
		{
			gold += 10;
			gem += 1;
		}
	}

	bound = GetLocalBounds();
	bound.width *= 0.5f;
	hitBox.UpdateTransform(body, bound);

	//std::cout << animator.GetCurrentClipId() << std::endl;
	//std::cout << animator.IsPlaying() << std::endl;
	//std::cout << maxExp << std::endl;
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

	//SOUND_MGR.PlaySfx("audios/hit.wav");
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		animator.Play("animations/warrior_Death.csv");
		sceneGame->SetFadeOut(true);
	}
}

void Player::OnDie()
{
	OnDamage(maxHp);
}

void Player::AddExp(float amount)
{
	float getExp = std::max(1.0f - level * 0.05f, 0.1f);
	exp += amount * getExp;

	if (exp >= maxExp)
	{
		exp = 0.f;
		maxExp = 100 + (level - 1) * 50 + std::pow(level, 2) * 2;
		level++;
		statPoints += 10;
		SOUND_MGR.PlaySfx("audios/LevelUp.wav");
	}
}

void Player::SetStr(int str)
{
	strLevel += str;
	damage += str;
}

void Player::SetDex(float dex)
{
	dexLevel += dex;
	critDamagePlus += dex * 0.01f;
}

void Player::SetAgi(float agi)
{
	agiLevel += agi;
	critChance += agi * 0.01f;
}

void Player::SetLuk(int luk)
{
	lukLevel += luk;
	rewardChance += luk * 0.01f;
	maxHp += lukLevel * 0.01f * 10.f;
}

void Player::StatReset()
{
	statPoints += strLevel + dexLevel + agiLevel + lukLevel;
	strLevel = 0;
	dexLevel = 0;
	agiLevel = 0;
	lukLevel = 0;

	maxHp = 100;
	damage = 10;
	critChance = 0.f;
	critDamagePlus = 1.f;
	rewardChance = 0.f;
}
