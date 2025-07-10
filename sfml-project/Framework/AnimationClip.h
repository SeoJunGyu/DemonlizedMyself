#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	//PingPong,
};

struct AnimationFrame
{
	std::string texId; //텍스처 아이이
	sf::IntRect texCoord; //스프라이트에서 잘라서 그릴 영역(좌표) 

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord) : texId(texId), texCoord(texCoord) {}
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
	int fps = 30;

	std::vector<AnimationFrame> frames; //0번부터 하나씩 바꾸는 것이다.

	bool loadFromFile(const std::string& filePath);
};

