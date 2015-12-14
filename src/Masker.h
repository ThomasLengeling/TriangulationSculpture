#pragma once

#include "ofMain.h"
#include "Particle.h"
 
 class Masker{
    public:
	
	vector<ofVec3f> leftU;
	vector<ofVec3f> rightU;
	vector<ofVec3f> leftD;
        vector<ofVec3f> rightD;

	bool particleAddedLU;
	bool particleAddedRU;
        bool particleAddedLD;
        bool particleAddedRD;
	void setup();
	void update();
	void draw(bool);  
	void addParticleLU(ofVec3f);
	void addParticleRU(ofVec3f);
	void addParticleLD(ofVec3f);
        void addParticleRD(ofVec3f);

	int getNumParticlesLU();
	int getNumParticlesLD();
	int getNumParticlesRU();
	int getNumParticlesRD();

	ofVec3f getPosLU(int);
	ofVec3f getPosLD(int);
	ofVec3f getPosRU(int);
	ofVec3f getPosRD(int);

        void clear();
};

