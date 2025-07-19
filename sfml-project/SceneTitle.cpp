#include "stdafx.h"
#include <iomanip>
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/TitleIcon.png");

	fontIds.push_back("fonts/Maplestory_Light.ttf");

	auto size = FRAMEWORK.GetWindowSizeF();

	background.setPosition({ 0.f, 0.f });
	

	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();
	background.setTexture(TEXTURE_MGR.Get(texId));
	text.setFont(FONT_MGR.Get(fontId));
	SOUNDBUFFER_MGR.Load("audios/TitleBGM.wav");

	titleBarbg.setFillColor(sf::Color(53, 53, 63, 255));
	titleBarbg.setSize({ 700.f, 25.f });
	Utils::SetOrigin(titleBarbg, Origins::ML);

	titleBar.setFillColor(sf::Color(255, 183, 0, 255));
	titleBar.setSize({ 700.f, 25.f });
	Utils::SetOrigin(titleBar, Origins::ML);

	Per = titleBar.getSize().x / 100.f;

	text.setPosition({ titleBarbg.getPosition().x + titleBarbg.getLocalBounds().width * 0.5f, titleBarbg.getPosition().y + titleBarbg.getLocalBounds().height * 0.5f });
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	Utils::SetOrigin(text, Origins::MC);

	SetupFadeEffect();

	SOUND_MGR.PlayBgm("audios/TitleBGM.wav");
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	UpdateTitleBar(dt);

	UpdateFade(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(background);
	window.draw(titleBarbg);
	window.draw(titleBar);
	window.draw(text);
	window.draw(fadeRect);
}

void SceneTitle::UpdateTitleBar(float dt)
{
	//time += dt * 10.f;
	time = 100.f;
	std::stringstream tmp;
	tmp << std::fixed << std::setprecision(2) << time;
	std::string str = tmp.str();

	if (time >= 100.f)
	{
		time = 100.f;
		fadeOut = true;
	}

	titleBar.setPosition({ 150.f, 950.f });
	titleBarbg.setPosition(titleBar.getPosition());

	float fill = Per * time;
	titleBar.setSize({ fill, titleBar.getSize().y });

	text.setString(tmp.str() + "%");
	text.setPosition({titleBarbg.getPosition().x + titleBarbg.getLocalBounds().width * 0.5f, titleBarbg.getPosition().y - 5.f});
	text.setCharacterSize(22);
	text.setFillColor(sf::Color::White);
	Utils::SetOrigin(text, Origins::MC);
}

void SceneTitle::SetupFadeEffect()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	fadeRect.setSize({ 1000.f ,size.y });
	fadeRect.setPosition(0.f, 0.f);
	fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

	fadeAlpha = 255.0f;
	fadeIn = true;
	fadeOut = false;
	fadeTimer = 0.0f;
}

void SceneTitle::UpdateFade(float dt)
{
	if (fadeIn)
	{
		FadeIn(dt);
	}
	else if (fadeOut)
	{
		FadeOut(dt);
	}
}

void SceneTitle::FadeIn(float dt)
{
	fadeTimer += dt;

	float progress = fadeTimer / fadeInterval;
	if (progress > 1.0f)
	{
		progress = 1.0f; //진행률이 더 올라가지 않도록 고정
	}

	fadeAlpha = 255.0f * (1.0f - progress); //255에서 0으로 감소

	if (progress >= 1.0f)
	{
		fadeAlpha = 0.0f;
		fadeIn = false;
		fadeTimer = 0.0f;
	}

	UpdateFadeColor();
}

void SceneTitle::FadeOut(float dt)
{
	fadeTimer += dt * 2.7f;

	float progress = fadeTimer / fadeInterval;
	if (progress > 1.0f)
	{
		progress = 1.0f; //진행률이 더 올라가지 않도록 고정
	}

	fadeAlpha = 255.0f * progress; //0에서 255로 증가

	if (progress >= 1.0f)
	{
		fadeAlpha = 255.0f;
		fadeTimer = 0.0f;
		SOUND_MGR.StopBgm();
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	UpdateFadeColor();
}

void SceneTitle::UpdateFadeColor()
{
	int alphaInt = static_cast<int>(fadeAlpha + 0.5f);
	fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alphaInt)));
}
