#pragma once
#include "AnimationClip.h"

struct AnimationEvent
{
	std::string id;
	int frame = 0;

	std::vector<std::function<void()>> actions;

	bool operator==(const AnimationEvent& other) const
	{
		//���̵�� �������� ������ ���ٰ� �Ǵ��Ѵ�.
		return (id == other.id) && (frame == other.frame);
	}
};

struct AnimationEventHash
{
	//����
	std::size_t operator()(const std::pair<std::string, int>& pair) const
	{
		//�ؽ��Լ� �����Ǿ��ִ� ����� ���� ��ȯ�Ѵ�.
		//
		std::size_t h1 = std::hash<std::string>()(pair.first);
		std::size_t h2 = std::hash<int>()(pair.second);
		return h1 ^ (h2 << 1);
	}
};

class Animator
{
protected:
	static const std::string emptyString;
	//std::string, int : � �Ŵϸ��̼��� ������, �ε���
	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events; //<Ű, ����, ī���� Ŭ����> / ��� ���̺� : �ؽ� �Լ��� �����ϴ� ������ �����Ͱ� ��� �ִ��� ��ȯ�ϴ� �ڷᱸ����.
	std::queue<std::string> playQueue; //������ ����� Ŭ����

	AnimationClip* currentClip; //���� ��� ���� �ִϸ��̼� 
	sf::Sprite* sprite; //�ִϸ��̼� ���� ���

	bool isPlaying = false; 
	int currentFrame = 0; //���� ������ �ε���
	int totalFrame = 0; //��ü ������ ��
	int checkFrame = 0;

	float frameDuration = 0.f; //�� ������ ���ӽð�
	float accumTime = 0.f; //���� �ð�
	float speed = 1.f; //��� �ӵ�(������ �����)

public:
	Animator() = default;
	~Animator() = default;

	void SetTarget(sf::Sprite* target) { sprite = target; } //�ִϸ����͸� ���� �ִϸ��̼��� ����
	void AddEvent(const std::string& id, int frame, std::function<void()> action);
	void ClearEvent() { events.clear(); }

	//void AddEvent(const AnimationEvent& ev)
	//{ 
	//	if (events.find(ev) != events.end())
	//	{
	//		// Error
	//		return;
	//	}
	//	events.insert(ev);
	//}

	void Update(float dt);

	bool IsPlaying() const { return isPlaying; }
	void SetSpeed(float speed)
	{
		this->speed = speed;
		checkFrame = this->speed > 0.f ? totalFrame : -1;
	}

	//�Ѵ� �����ϰ� ���� �ִϸ��̼� ��ü�� ���õ� ���� �ٲ۴�.
	void Play(const std::string& clipId, bool clearQueue = true);
	void Play(AnimationClip* clip, bool clearQueue = true);

	void PlayQueue(const std::string& clipId); //������� �ִϸ��̼��� ��´�.

	void Stop();

	//void Pause(bool pause);

	void SetFrame(const AnimationFrame& frame);

	//������� �ִϸ��̼� ��������
	const std::string& GetCurrentClipId() const
	{
		if (currentClip == nullptr)
			return emptyString;
		return currentClip->id;
	}
};

