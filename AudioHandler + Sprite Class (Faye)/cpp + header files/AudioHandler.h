#ifndef AUDIO_H
#define AUDIO_H

#include "SDL.h"
#include <iostream>
#include <map>
#include <SDL_mixer.h>

// SDL_mixer tutorial and download link here:
// http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
// http://www.libsdl.org/projects/SDL_mixer/
// Make sure to add 'SDL2_mixer.lib' under project properties->Linker->Input->Additional Independencies

class AudioHandler
{
public:
	// Initialize an AudioHandler object, initialize SDL_Mixer
	AudioHandler();
	// Destroys allocated audio resources
	~AudioHandler();
	// Checks whether or not the initialization was successful
	bool initialized();
	// Checks by track number if the file path is valid
	bool checkAudio(int trackNo);

	// Adds a new sound effect and return its track number
	int addSFX(int _trackNo, char* _fileName);
	int addSFX(int _trackNo, std::string _fileName);
	// Erases sound effect and free the resource
	void eraseSFX(int trackNo);

	// Sets a music track, its track number will always be 0
	void setMusic(char* _fileName, bool _loop);
	void setMusic(std::string _fileName, bool _loop);

	// Sets muting value for the music
	void setMuting(bool value);
	// Returns whether or not music is muted
	bool AudioHandler::muted();
	// Returns whether or not the music is playing
	bool playing();
	// Turns on/off looping for a certain track
	void looping(int trackNo, bool value);

	// Plays a certain track n number of times, 0 to turn loop on and loop play
	void play(int trackNo, int n);
	// Pauses music, if play() was not called, return false
	bool pause();
	// Resumes playing, if play() was not called, return false
	bool resume();
	// Pauses music if playing, resume if pausing, return false if play() not called
	bool switch_pause_resume();
	// Stops music
	void stop();

private:
	// Type struct for sound effects
	struct SFX
	{
		Mix_Chunk *sound = NULL;
		bool loop = false;
	};
	// Collection of sound effects
	std::map<int, SFX> soundEffects;
	
	// Music soundtrack; there can only be one
	Mix_Music *music = NULL;
	// Whether or not the music is set to loop
	bool loop = true;
	// Whether or not a current music play is in session
	bool playSession = false;
	// Whether or not the music is muted
	bool mute = false;

	// Initialization of SDL_Mixer, failed if < 0
	int init;
};

#endif //AUDIO_H