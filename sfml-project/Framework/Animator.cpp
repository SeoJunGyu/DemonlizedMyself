#include "stdafx.h"
#include "Animator.h"

const std::string Animator::emptyString = "";

void Animator::AddEvent(const std::string& id, int frame, std::function<void()> action)
{
	auto key = std::pair<std::string, int>(id, frame);
	auto it = events.find(key);
	if (it == events.end())
	{
		//기존에 이벤트가 등록이 안되서 새로 등록한다.
		//이벤트에 할당
		events.insert({ key, {id, frame} });
	}

	//이벤트가 등록되어있어서 사용하는 것이다.
	//배열 인덱스로 접근
	events[key].actions.push_back(action);
}

void Animator::Update(float dt)
{
	if (!isPlaying)
		return;

	//std::fabs : 절댓값 사용
	accumTime += dt * std::fabs(speed);
	if (accumTime < frameDuration)
		return;

	currentFrame += speed > 0.f ? 1 : -1; //양수면 +1, 음수면 -1 / 다음 실행할 애니메이션의 프레임 속도
	accumTime = 0.f;

	//현재 재생하고 있는 애니메이션 종료
	if (currentFrame == checkFrame)
	{
		//큐가 비어있지 않다면?
		if (!playQueue.empty())
		{
			//큐를 바운다.
			std::string clipId = playQueue.front();
			Play(clipId, false); //다음 에니메니션 서러
			playQueue.pop();
			return;
		}

		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = speed > 0.f ? totalFrame - 1 : 0;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = speed > 0.f ? 0 : totalFrame - 1;
			break;
		}
	}

	//다른 애니메이션 할당
	SetFrame(currentClip->frames[currentFrame]);
	auto find = events.find({ currentClip->id, currentFrame }); //아이디와 프레임이 같은지 확인한다.
	if (find != events.end())
	{
		auto& ev = find->second;
		for (auto& action : ev.actions)
		{
			if (action)
			{
				action();
			}
		}
	}
}

void Animator::Play(const std::string& clipId, bool clearQueue)
{
	//Get 함수로 플레이 시키는 함수 
	Play(&ANI_CLIP_MGR.Get(clipId), clearQueue);
}

void Animator::Play(AnimationClip* clip, bool clearQueue)
{
	if (clearQueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}
	}

	isPlaying = true;

	currentClip = clip;
	totalFrame = clip->frames.size();
	checkFrame = this->speed > 0.f ? totalFrame : -1; //양수인 경유 : 한개 벼 
	currentFrame = speed > 0.f ? 0 : totalFrame - 1;
	
	frameDuration = 1.f / clip->fps;
	accumTime = 0.f;
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::PlayQueue(const std::string& clipId)
{
	playQueue.push(clipId);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	sprite->setTexture(TEXTURE_MGR.Get(frame.texId));
	sprite->setTextureRect(frame.texCoord);
	//sprite->
}
