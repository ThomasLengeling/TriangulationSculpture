#pragma once

#include "ofMain.h"
#include "Particle.h"
 
 class Masker{
    public:
	
	vector<ofVec3f> left;
	vector<ofVec3f> right;

	bool particleAddedL;
	bool particleAddedR;
	void setup();
	void update();
	void draw();  
	void addParticleL(ofVec3f);
	void addParticleR(ofVec3f);
};

