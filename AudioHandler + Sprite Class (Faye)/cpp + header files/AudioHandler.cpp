#include "AudioHandler.h"

// Initialize an AudioHandler object, initialize SDL_Mixer
AudioHandler::AudioHandler()
{
	AudioHandler::init = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}


// Destroys allocated audio resources
AudioHandler::~AudioHandler()
{
	for (std::map<int, AudioHandler::SFX>::iterator it = AudioHandler::soundEffects.begin();
		it != AudioHandler::soundEffects.end();
		++it)
	{
		AudioHandler::eraseSFX(it->first);
	}
	AudioHandler::eraseSFX(0);
}


// Checks whether or not the initialization was successful
bool AudioHandler::initialized()
{
	return !(AudioHandler::init < 0);
}


// Checks by track number if the file path is valid
bool AudioHandler::checkAudio(int trackNo)
{
	if (trackNo < 0)
	{
		return false;
	}
	if (trackNo == 0)
	{
		return (AudioHandler::music != NULL);
	}
	return (AudioHandler::soundEffects[trackNo].sound != NULL);
}


// Adds a new sound effect and return its track number
int AudioHandler::addSFX(int _trackNo, char* _fileName)
{
	int officialTrackNo = _trackNo;
	while (true)
	{
		if ((AudioHandler::soundEffects.find(officialTrackNo) == AudioHandler::soundEffects.end())
			&& (officialTrackNo > 0))
		{
			break;
		}
		officialTrackNo++;
	}
	AudioHandler::soundEffects[officialTrackNo].sound = Mix_LoadWAV_RW(SDL_RWFromFile(_fileName, "rb"), 1);
	return officialTrackNo;
}
int AudioHandler::addSFX(int _trackNo, std::string _fileName)
{
	return AudioHandler::addSFX(_trackNo, &(_fileName[0u]));
}


// Erases sound effect and free the resource
void AudioHandler::eraseSFX(int trackNo)
{
	if (trackNo == 0)
	{
		Mix_FreeMusic(AudioHandler::music);
		return;
	}
	Mix_FreeChunk(AudioHandler::soundEffects[trackNo].sound);
}


// Sets a music track, its track number will always be 0
void AudioHandler::setMusic(char* _fileName, bool _loop)
{
	AudioHandler::music = Mix_LoadMUS(_fileName);
	AudioHandler::loop = _loop;
}
void AudioHandler::setMusic(std::string _fileName, bool _loop)
{
	AudioHandler::setMusic(&(_fileName[0u]), _loop);
}


// Sets muting value for the music
void AudioHandler::setMuting(bool value)
{
	AudioHandler::mute = value;
	if (!value)
	{
		Mix_VolumeMusic(128);
		return;
	}
	Mix_VolumeMusic(0);
}


// Returns whether or not music is muted
bool AudioHandler::muted()
{
	return AudioHandler::mute;
}


// Returns whether or not the music is playing
bool AudioHandler::playing()
{
	return Mix_PlayingMusic();
}


// Turns on/off looping for a certain track
void AudioHandler::looping(int trackNo, bool value)
{
	if (trackNo < 0)
	{
		return;
	}
	if (trackNo == 0)
	{
		AudioHandler::loop = value;
		return;
	}
	AudioHandler::soundEffects[trackNo].loop = value;
}


// Plays a certain track n number of times, 0 to turn loop on and loop play
void AudioHandler::play(int trackNo, int n)
{
	if (n == 0)
	{
		AudioHandler::looping(trackNo, true);
	}
	if (!AudioHandler::checkAudio(trackNo))
	{
		return;
	}
	if (trackNo == 0)
	{
		Mix_PlayMusic(AudioHandler::music, n - 1);
		return;
	}
	Mix_PlayChannel(-1, AudioHandler::soundEffects[trackNo].sound, n - 1);
}


// Pauses music, if play() was not called, return false
bool AudioHandler::pause()
{
	if (!Mix_PlayingMusic())
	{
		return false;
	}
	if (!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
	return true;
}


// Resumes playing, if play() was not called, return false
bool AudioHandler::resume()
{
	if (!Mix_PlayingMusic())
	{
		return false;
	}
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	return true;
}


// Pauses music if playing, resume if pausing, return false if play() not called
bool AudioHandler::switch_pause_resume()
{
	if (!Mix_PlayingMusic())
	{
		return false;
	}
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
	return true;
}

// Stops music
void AudioHandler::stop()
{
	Mix_HaltMusic();
}



// AUDIO CLASS
/*
Audio::Audio(Audio::AudioType _type, char* fileName)
{
Audio::type = _type;
switch (Audio::type)
{
case Audio::CHUNK:
Audio::c = new AudioChunk(fileName);
Audio::m = NULL;
break;
case Audio::MUSIC:
Audio::m = new AudioMusic(fileName);
Audio::c = NULL;
break;
}
}

Audio::~Audio()
{
if (Audio::m != NULL)
{
delete Audio::m;
}
if (Audio::c != NULL)
{
delete Audio::c;
}
}

bool Audio::checkAudio()
{
return ((Audio::m != NULL) || (Audio::c != NULL));
}

void Audio::play(int n)
{
if (Audio::checkAudio())
{
switch (Audio::type)
{
case Audio::AudioType::CHUNK:
if ((Audio::loop) || (n == 0))
{
Audio::looping(true);
Mix_PlayChannel(-1, Audio::c->sound, -1);
break;
}
Mix_PlayChannel(-1, Audio::c->sound, n - 1);
break;
case Audio::AudioType::MUSIC:
if ((Audio::loop) || (n == 0))
{
Audio::looping(true);
Mix_PlayMusic(Audio::m->sound, -1);
break;
}
Mix_PlayMusic(Audio::m->sound, n - 1);
break;
}
}
}

void Audio::looping(bool value)
{
Audio::loop = value;
}

// AUDIOCHUNK CLASS

AudioChunk::AudioChunk(char* fileName)
{
AudioChunk::sound = Mix_LoadWAV_RW(SDL_RWFromFile(fileName, "rb"), 1);
}

// AUDIOMUSIC CLASS

AudioMusic::AudioMusic(char* fileName)
{
AudioMusic::sound = Mix_LoadMUS(fileName);
}

*/