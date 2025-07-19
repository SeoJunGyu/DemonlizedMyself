#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{
protected:
	sf::Sprite background;
	std::string texId = "graphics/TitleIcon.png";
	std::string fontId = "fonts/Maplestory_Light.ttf";

	sf::RectangleShape titleBar;
	sf::RectangleShape titleBarbg; //53 53 63
	sf::Text text;
	float Per = 0.f;

	float time = 0.f;

	sf::RectangleShape fadeRect;
	float fadeAlpha = 100.f;
	bool fadeIn = false;
	bool fadeOut = false;
	float fadeInterval = 3.0f;
	float fadeTimer = 0.0f;

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateTitleBar(float dt);

	void SetupFadeEffect();

	void UpdateFade(float dt);
	void FadeIn(float dt);
	void FadeOut(float dt);
	void UpdateFadeColor();

	float GetFadeAlpha() const { return fadeAlpha; }
};

