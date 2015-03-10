==================
|   ReadMe.txt   |
==================

Last updated: 3/8/2015
By: Faye Jao


CONFIGURING SDL_MIXER:
The AudioHandler engine is written based on LazyFoo's tutorial, and the SDL(2) Mixer library files are required.
To obtain the files, follow this link: http://www.libsdl.org/projects/SDL_mixer/
To see the tutorial, follow this link: http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
After installing the SDL_Mixer files, make sure to add 'SDL2_mixer.lib' to your independencies path.
You can configure this under project properties->Linker->Input->Additional Independencies.

This package contains two working classes: AudioHandler, and Sprite (improved).
The AudioHandler.h file should be very clear on what each of the AudioHandler function does.
Although, Sprite.h may not be as clear as AudioHandler.h (since the former isn't as important).
If anything is unclear, please let me know.


AUDIOHANDLER CLASS:
Only one AudioHandler object should be created & used throughout the whole program's duration.
It will clean up after itself, unless you initialized with 'new', then you will need to delete it yourself when done.
The AudioHandler does not take any constructors.

A bit about Mix_chunk and Mix_music:

Mix_chunk is the equivalent of a sound effect. In AudioHandler, they are stored in a struct, then mapped with an integer.
Mix_chunk is played on separate channels, SDL takes care of most channel management unless specified.
AudioHandler automatically sets all sound effects to be played on the first available channel (indicated by the value -1).

Mix_music is the equivalent of a sound track/music. In SDL_mixer and AudioHandler, there can only be one music file.
Most of the controls in AudioHandler deals with this music file.

Every sound effect is to be added into a map called soundEffects, using the function called addSFX(desired track number).
If you use any negative number (preferably not too big), the function will increment it until a free positive number is available.
All track numbers are unique from each other. The number 0 is reserved (but not used) because it is used to indicate the music track.

Because there is only one music allowed in the AudioHandler, its "track number" is 0.
Although there is only one music allowed in the AudioHandler, it can be switched using setMusic(filename).
You can try calling different functions such as pause(), resume(), stop(), and so on.

Note that there are some functions, such as play(), looping(), and etc, that requires track numbers.
This means that this function works both for sound effects and the music. Again, please use track number 0 for the latter.

Unfortunately, the AudioHandler isn't very advanced, so it currently lacks controls such as:
multiple sound tracks, playlists, volume control, fading in/out, and etc.


SPRITE CLASS:
This is an improved Sprite class, extracted from Homework6.
Its main feature/improvement is its ability to play a certain frame for a set duration of time.
To accommodate for this change, the data structure of/relationship between the frames and sequences are modified.
Each sequence includes non-unique sequence frames (seqFrame); each sequence frame includes a non-unique graphic frame (graFrame).
More information about this could be seen under the Sprite.h file.
It also has frame-bound audio, which means when a certain frame plays, certain set sounds will play.
This means that a reference to the AudioHandler object will have to be passed in through the constructor.
It also means that this specific Sprite class isn't independent from the AudioHandler class, unless some codes are commented out.


MAIN.CPP:
In the main.cpp file, you will find a demo of the AudioHandler + Sprite class working together.
To set the resource path, change the variable resPath where it is initialized right when main() starts.
