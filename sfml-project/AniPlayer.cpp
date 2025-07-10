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
	animator.SetTarget(&body); //갱신할 스프라이트를 애니메이터에 설정

	//idle의 0번? 프레임에 호출된다.
	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);

	//점프의 0번째 프레임에 호출된다.
	//특정 프레임에 어떤 함수를 호출할때 사용한다.
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

	animator.Play("animations/idle.csv"); //아이들 애이메이션 경로 넘겨서 플레이
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	//애니메이션 재생 + 이동
	animator.Update(dt); //애니메이터 호출

	float h = 0.f;
	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal); //가로입력 검사
		velocity.x = h * speed; //velocity : 속도
	}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		//점프 코드
		isGrounded = false;
		velocity.y = -250.f; //공중으로 띄운다.
		animator.Play("animations/jump.csv");
	}
	if (!isGrounded)
	{
		velocity += gravity * dt; //아래로 가속도 적용
	}
	position += velocity * dt;
	if (position.y > 0.f) //바닥에 내려갈 경우
	{
		//바닥에 있다고 설정 / 속도 초기화
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position);

	//h 양수 : 오른쪽 방향 , h 음수 : 왼쪽 방향
	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(-1.f, 1.0f));
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle") //좌우키 안눌린 가만히 있는 자리 
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
