#include "Masker.h"

//--------------------------------------------------------------
void Masker::setup(){
    particleAddedL = false;
    particleAddedR = false;
    left.push_back(ofVec3f(0, 768, 0));
    left.push_back(ofVec3f(0, 0, 0));
    left.push_back(ofVec3f(512, 0, 0));

    right.push_back(ofVec3f(1024, 768, 0));
    right.push_back(ofVec3f(1024, 0, 0));
    right.push_back(ofVec3f(512, 0, 0));
}

//--------------------------------------------------------------
void Masker::update(){
}

//--------------------------------------------------------------
void Masker::draw(){
    ofPushStyle();
    ofSetColor(255, 255, 255);
    //ofSetPolyMode(OF_POLY_WINDING_ABS_GEQ_TWO);
    ofBeginShape();
    for(int i = 0; i < left.size(); i ++){
        ofVertex(left[i].x, left[i].y);
    }
    ofEndShape();

    ofBeginShape();
    for(int i = 0; i < right.size(); i ++){
        ofVertex(right[i].x, right[i].y);
    }
    ofEndShape();

    ofPopStyle();
}

//--------------------------------------------------------------
void Masker::addParticleL(ofVec3f posL){
    if(particleAddedL){
	left.pop_back();
	//left.pop_back();
    }
    left.push_back(posL);
    left.push_back(ofVec3f(512, 768, 0));
    //left.push_back(ofVec3f(0, 768, 0));
    particleAddedL = true;
}

//--------------------------------------------------------------
void Masker::addParticleR(ofVec3f posR){
    if(particleAddedR){
	right.pop_back();
    }
    right.push_back(posR);
    left.push_back(ofVec3f(512, 768, 0));
    particleAddedR = true;
}
