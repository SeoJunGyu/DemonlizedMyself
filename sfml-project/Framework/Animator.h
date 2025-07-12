#pragma once
#include "AnimationClip.h"

struct AnimationEvent
{
	std::string id;
	int frame = 0;

	std::vector<std::function<void()>> actions;

	bool operator==(const AnimationEvent& other) const
	{
		//아이디와 프레임이 같으면 같다고 판단한다.
		return (id == other.id) && (frame == other.frame);
	}
};

struct AnimationEventHash
{
	//펑터
	std::size_t operator()(const std::pair<std::string, int>& pair) const
	{
		//해쉬함수 구현되어있는 페어의 값을 반환한다.
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
	//std::string, int : 어떤 매니메이션의 프레임, 인덱스
	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events; //<키, 벨류, 카운터 클래스> / 헤시 테이블 : 해시 함수가 리턴하는 값으로 데이터가 어디 있는지 반환하는 자료구조다.
	std::queue<std::string> playQueue; //다음에 재생할 클립들

	AnimationClip* currentClip; //현재 재싱 중인 애니메이션 
	sf::Sprite* sprite; //애니메이션 적용 대상

	bool isPlaying = false; 
	int currentFrame = 0; //현재 프레임 인덱스
	int totalFrame = 0; //전체 프레임 수
	int checkFrame = 0;

	float frameDuration = 0.f; //각 프레임 지속시간
	float accumTime = 0.f; //누적 시간
	float speed = 1.f; //재생 속도(음수면 역재생)

public:
	Animator() = default;
	~Animator() = default;

	void SetTarget(sf::Sprite* target) { sprite = target; } //애니메이터를 가진 애니메이션을 설정
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

	//둘다 동일하게 현재 애니메이션 객체에 세팅된 것을 바꾼다.
	void Play(const std::string& clipId, bool clearQueue = true);
	void Play(AnimationClip* clip, bool clearQueue = true);

	void PlayQueue(const std::string& clipId); //재생끝난 애니메이션을 담는다.

	void Stop();

	//void Pause(bool pause);

	void SetFrame(const AnimationFrame& frame);

	//재생중인 애니메이션 가져오기
	const std::string& GetCurrentClipId() const
	{
		if (currentClip == nullptr)
			return emptyString;
		return currentClip->id;
	}
};

