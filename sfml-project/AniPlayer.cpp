#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body); //������ ��������Ʈ�� �ִϸ����Ϳ� ����

	//idle�� 0��? �����ӿ� ȣ��ȴ�.
	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);

	//������ 0��° �����ӿ� ȣ��ȴ�.
	//Ư�� �����ӿ� � �Լ��� ȣ���Ҷ� ����Ѵ�.
	animator.AddEvent("Jump", 0,
		[]()
		{
			std::cout << "??" << std::endl;
		}
	);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.Play("animations/idle.csv"); //���̵� ���̸��̼� ��� �Ѱܼ� �÷���
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	//�ִϸ��̼� ��� + �̵�
	animator.Update(dt); //�ִϸ����� ȣ��

	float h = 0.f;
	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal); //�����Է� �˻�
		velocity.x = h * speed; //velocity : �ӵ�
	}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		//���� �ڵ�
		isGrounded = false;
		velocity.y = -250.f; //�������� ����.
		animator.Play("animations/jump.csv");
	}
	if (!isGrounded)
	{
		velocity += gravity * dt; //�Ʒ��� ���ӵ� ����
	}
	position += velocity * dt;
	if (position.y > 0.f) //�ٴڿ� ������ ���
	{
		//�ٴڿ� �ִٰ� ���� / �ӵ� �ʱ�ȭ
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position);

	//h ��� : ������ ���� , h ���� : ���� ����
	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(-1.f, 1.0f));
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle") //�¿�Ű �ȴ��� ������ �ִ� �ڸ� 
	{
		if (h != 0.f)
		{
			animator.Play("animations/run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
		else
		{
			animator.Play("animations/run.csv");
		}
	}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
