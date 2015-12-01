#pragma once

#include "ofMain.h"
 
 class VideoManager{
    public:

	void setup();
	void play(int);
	void update();
	void stop();
	void draw();
	vector<ofVideoPlayer> players;
	vector<bool> isPlaying;

};

