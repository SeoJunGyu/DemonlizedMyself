#include "stdafx.h"
#include "Animator.h"

const std::string Animator::emptyString = "";

void Animator::AddEvent(const std::string& id, int frame, std::function<void()> action)
{
	auto key = std::pair<std::string, int>(id, frame);
	auto it = events.find(key);
	if (it == events.end())
	{
		//������ �̺�Ʈ�� ����� �ȵǼ� ���� ����Ѵ�.
		//�̺�Ʈ�� �Ҵ�
		events.insert({ key, {id, frame} });
	}

	//�̺�Ʈ�� ��ϵǾ��־ ����ϴ� ���̴�.
	//�迭 �ε����� ����
	events[key].actions.push_back(action);
}

void Animator::Update(float dt)
{
	if (!isPlaying)
		return;

	//std::fabs : ���� ���
	accumTime += dt * std::fabs(speed);
	if (accumTime < frameDuration)
		return;

	currentFrame += speed > 0.f ? 1 : -1; //����� +1, ������ -1 / ���� ������ �ִϸ��̼��� ������ �ӵ�
	accumTime = 0.f;

	//���� ����ϰ� �ִ� �ִϸ��̼� ����
	if (currentFrame == checkFrame)
	{
		//ť�� ������� �ʴٸ�?
		if (!playQueue.empty())
		{
			//ť�� �ٿ��.
			std::string clipId = playQueue.front();
			Play(clipId, false); //���� ���ϸ޴ϼ� ����
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

	//�ٸ� �ִϸ��̼� �Ҵ�
	SetFrame(currentClip->frames[currentFrame]);
	auto find = events.find({ currentClip->id, currentFrame }); //���̵�� �������� ������ Ȯ���Ѵ�.
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
	//Get �Լ��� �÷��� ��Ű�� �Լ� 
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
	checkFrame = this->speed > 0.f ? totalFrame : -1; //����� ���� : �Ѱ� �� 
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
