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
		bool isFilled = false; //�ʱ�ȭ : ����ִ� ����
		
		void SetIcon(std::string& newTexId)
		{
			texId = newTexId;
			sprite.setTexture(TEXTURE_MGR.Get(newTexId));
			isFilled = true; //�������� ��ġ�� ����
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

	//����, ����ġ, ����ġ��, ���� ����Ʈ, ���� �ؽ�Ʈ, ���� ����, ���� �� ��ư
	//���� < - > ��ȭ ��ȯ ��ư
	sf::Text textLevel;
	sf::Text textNameStatPoint;
	sf::Text textStatPoint;

	// ����ġ
	sf::RectangleShape expBar;
	sf::RectangleShape expBarbg; //53 53 63
	sf::Text textExp;
	float expPer = 0.f;

	// ���� â
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

	std::vector<SkillIcon> skillIcons; //�ϴ� ��ų ������
	std::vector<SkillSlot> skillSlots; //��ų ����
	std::vector<sf::Sprite> iconInSlot; //��ų ���԰� ������ ��ġ�� ��������Ʈ

	SkillIcon* selectedSkillIcon = nullptr;
	std::string texIdSlot = "graphics/skillSlot.png";



	// UI ��ȯ �÷���
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

