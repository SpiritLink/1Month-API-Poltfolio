#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:_system(NULL)
	, _sound(NULL)
	, _channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//사운드 시스템 생성한다
	System_Create(&_system);

	//시스템 초기화
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

	//채널 수 만큼 메모리 버퍼 및 사운드를 생성한다
	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//메모리 깔끔하게 한 번 밀어준다
	ZeroMemory(_sound, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	ZeroMemory(_channel, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

	return S_OK;
}

void soundManager::release()
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; ++i)
		{
			if (_channel != NULL)
				_channel[i]->stop();
			if (_sound != NULL)
				_sound[i]->release();
		}
	}

	//메모리 지운다
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 해제
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

	_mTotalSounds.clear();
}

void soundManager::update()
{
	//사운드 시스템을 계속적으로 업데이트 해준다
	_system->update();

	//볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는 등
	//다양한 작업을 자동으로 해준다.
}

void soundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL,
				0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL,
				0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
		_system->createSound(soundName.c_str(), FMOD_DEFAULT,
			0, &_sound[_mTotalSounds.size()]);
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
	_mTotalSoundNames.insert(make_pair(keyName, soundName));
}

void soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	bool isPlay = true;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			if (_channel[count]->isPlaying(&isPlay))
			{
				_system->playSound(FMOD_CHANNEL_FREE, *(iter->second), false, &_channel[count]);
				_channel[count]->setVolume(volume);
				break;
			}

			else if (!(_channel[count]->isPlaying(&isPlay)))
			{
				_system->playSound(FMOD_CHANNEL_FREE, *(iter->second), false, &_channel[count]);
				_channel[count]->setVolume(volume);
				break;
			}
		}
	}
}

void soundManager::playSound(string keyName, POINT position)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	bool isPlay = true;
	
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			if (_channel[count]->isPlaying(&isPlay))
			{
				_system->playSound(FMOD_CHANNEL_FREE, *(iter->second), false, &_channel[count]);
				_channel[count]->setVolume(0.5f);
				break;
			}
			else if (!(_channel[count]->isPlaying(&isPlay)))
			{
				_system->playSound(FMOD_CHANNEL_FREE, *(iter->second), false, &_channel[count]);
				_channel[count]->setVolume(0.5f);
				break;
			}
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::stopAllSound()
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		_channel[count]->stop();
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void soundManager::next(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			if (count + 1 == _mTotalSounds.size())
			{
				iter = _mTotalSounds.begin();
				play(iter->first, volume);
				break;
			}
			else
			{
				++iter;
				play(iter->first, volume);
				break;
			}
		}
	}
}

void soundManager::prev(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			if (count == 0)
			{
				iter = _mTotalSounds.end();
				--iter;
				play(iter->first, volume);
				break;
			}
			else
			{
				--iter;
				play(iter->first, volume);
				break;
			}
		}
	}
}

void soundManager::setTime(string keyName, DWORD32 time)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(time * 1000, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

int soundManager::getTime(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	DWORD32 time = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&time, FMOD_TIMEUNIT_MS);
			return time;
		}
	}
	return NULL;

}

int soundManager::getMaxTime(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	DWORD32 maxTime = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_sound[count]->getLength(&maxTime, FMOD_TIMEUNIT_MS);
			return maxTime;
		}
	}
	return NULL;
}

void soundManager::setVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
		}
	}

}

//char * soundManager::getName(string keyName)
//{
//	arrSoundsIter iter = _mTotalSounds.begin();
//	int count = 0;
//	char str[256];
//	//const char* soundName;
//	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
//	{
//		if (keyName == iter->first)
//		{
//			_sound[count]->getName(str, sizeof(str));
//			return str;
//		}
//	}
//	return NULL;
//}

const char * soundManager::getName(string keyName)
{
	arrSoundNamesIter iter = _mTotalSoundNames.begin();
	int count = 0;
	const char* soundName;
	for (iter; iter != _mTotalSoundNames.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			soundName = iter->second.c_str();
			return soundName;
		}
	}
	return NULL;
}
