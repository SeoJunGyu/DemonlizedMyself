#pragma once

class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;

protected:
	SoundMgr() = default;
	virtual ~SoundMgr() = default;

	SoundMgr(const SoundMgr& other) = delete;
	SoundMgr& operator=(const SoundMgr& other) = delete;

	sf::Sound bgm;

	std::list<sf::Sound*> playing; //����� ���� ��ü ����Ʈ
	std::list<sf::Sound*> waiting; //�� ��� ���� ��ü ����Ʈ

	float sfxVolume = 10.f;
	float bgmVolume = 100.f;

public:

	void SetBgmVolume(float v)
	{
		bgmVolume = v;
		bgm.setVolume(bgmVolume);
	}

	void SetSfxVolume(float v);

	void Init(int totalChannels = 64);
	void Release();
	void Update(float dt);

	//bgm �÷��� / bool loop : ���� ����
	void PlayBgm(std::string id, bool loop = true);
	void PlayBgm(sf::SoundBuffer& buffer, bool loop = true);
	void StopBgm();

	//���� ȿ�� / bool loop : ���� ����
	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx(); //����ȿ�� �ϰ�����
};

#define SOUND_MGR (SoundMgr::Instance())

