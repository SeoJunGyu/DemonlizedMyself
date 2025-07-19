#pragma once
#include "GameObject.h"
#include "Skill.h"

class Player;

class StatUiHud :
    public GameObject
{
	struct SkillSlot
	{
		sf::Sprite spriteFrame;
		sf::Sprite sprite;
		std::string texId;
		sf::FloatRect Bounds;
		bool isFilled = false; //초기화 : 비어있는 상태
		
		void SetIcon(std::string& newTexId)
		{
			texId = newTexId;
			sprite.setTexture(TEXTURE_MGR.Get(newTexId));
			isFilled = true; //아이콘이 배치된 상태
		}

		bool InIcon() const
		{
			return !(texId == "graphics/skillSlot.png");
		}
	};

	struct SkillIcon
	{
		sf::Sprite sprite;
		std::string texId;
		sf::FloatRect Bounds;
		std::function<void()> onClick;

		
	};

protected:
	std::string fontId = "fonts/Maplestory_Light.ttf";

	Player* player = nullptr;

	sf::Sprite playerIcon;
	sf::Sprite iconFrame;
	std::string playerIcontexId = "graphics/Worrior_Icon.png";
	std::string texIdFrame = "graphics/Icon_frame.png";

	//sf::RectangleShape back;
	sf::Sprite back;
	std::string texIdBack = "graphics/big_bar.png";

	//레벨, 경험치, 경험치바, 스탯 포인트, 스탯 텍스트, 스탯 레벨, 스탯 업 버튼
	//스탯 < - > 강화 전환 버튼
	sf::Text textLevel;
	sf::Text textNameStatPoint;
	sf::Text textStatPoint;

	// 경험치
	sf::RectangleShape expBar;
	sf::RectangleShape expBarbg; //53 53 63
	sf::Text textExp;
	float expPer = 0.f;

	// 스탯 창
	//sf::RectangleShape strBack;
	sf::Sprite strBack;
	sf::Sprite dexBack;
	sf::Sprite agiBack;
	sf::Sprite lukBack;

	std::string texIdstatBack = "graphics/basic_bar.png";

	sf::Text textStr;
	sf::Text textValueStr;
	sf::Text textLevelStr;

	sf::Text textDex;
	sf::Text textValueDex;
	sf::Text textLevelDex;

	sf::Text textAgi;
	sf::Text textValueAgi;
	sf::Text textLevelAgi;

	sf::Text textLuk;
	sf::Text textValueLuk;
	sf::Text textLevelLuk;

	// Skill
	int slotCount = 10;
	sf::RectangleShape slotBack;

	std::vector<SkillIcon> skillIcons; //하단 스킬 아이콘
	std::vector<SkillSlot> skillSlots; //스킬 슬롯
	std::vector<sf::Sprite> iconInSlot; //스킬 슬롯과 동일한 위치에 스프라이트

	SkillIcon* selectedSkillIcon = nullptr;
	std::string texIdSlot = "graphics/skillSlot.png";



	// UI 전환 플래그
	bool isStat = true;
	bool isSkill = false;

public:
	StatUiHud(const std::string& name = "");
	virtual ~StatUiHud() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::Sprite GetBack() const { return back; }
	sf::Sprite GetStrBack() const { return strBack; }
	sf::Sprite GetDexBack() const { return dexBack; }
	sf::Sprite GetAgiBack() const { return agiBack; }
	sf::Sprite GetLukBack() const { return lukBack; }

	// Update
	void UpdateExpBar();
	void UpdateStat();

	// Set
	void SetStat();
	void SetIsStat(bool isStat) { this->isStat = isStat; }
	void SetIsSkill(bool isSkill) { this->isSkill = isSkill; }
	void SetUiChange();

	// Skill
	std::vector<SkillSlot> GetSkillSlot() const { return skillSlots; }
};

