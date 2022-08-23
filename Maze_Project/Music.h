//#pragma once
//#include "fmod.hpp"
//#include<iostream>
//
//class Music {
//private:
//	FMOD::System* system;
//	FMOD::Sound* sound;
//	FMOD::Channel* channel;		//채널도 여러개 가능 ( 복잡한 음향 )
//	FMOD_RESULT       result;
//	unsigned int      version;
//	void* extradriverdata;
//
//public:
//	Music() {
//		result = FMOD::System_Create(&system);
//		if (result != FMOD_OK) exit(0);		//에러 체크
//
//		result = system->getVersion(&version);
//		if (result != FMOD_OK) exit(0);
//
//		result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
//		if (result != FMOD_OK) exit(0);
//
//		//result = system->createSound("drumloop.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, 0, &sound);
//		result = system->createSound("congratulations.MP3", FMOD_LOOP_OFF | FMOD_DEFAULT, 0, &sound); // .mp3 files work!
//		if (result != FMOD_OK) exit(0);
//	}
//	~Music() {
//		system->release();
//	}
//	void Play() {
//		result = system->playSound(sound, 0, false, &channel);
//		if (result != FMOD_OK) exit(0);
//	}
//
//};