#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	//PingPong,
};

struct AnimationFrame
{
	std::string texId; //�ؽ�ó ������
	sf::IntRect texCoord; //��������Ʈ���� �߶� �׸� ����(��ǥ) 

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord) : texId(texId), texCoord(texCoord) {}
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
	int fps = 30;

	std::vector<AnimationFrame> frames; //0������ �ϳ��� �ٲٴ� ���̴�.

	bool loadFromFile(const std::string& filePath);
};

