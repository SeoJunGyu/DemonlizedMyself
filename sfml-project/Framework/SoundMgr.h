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

	std::list<sf::Sound*> playing; //재생중 사운드 객체 리스트
	std::list<sf::Sound*> waiting; //비 재생 사운드 객체 리스트

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

	//bgm 플레이 / bool loop : 루프 여부
	void PlayBgm(std::string id, bool loop = true);
	void PlayBgm(sf::SoundBuffer& buffer, bool loop = true);
	void StopBgm();

	//사운드 효과 / bool loop : 루프 여부
	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx(); //사운드효과 일괄정지
};

#define SOUND_MGR (SoundMgr::Instance())

