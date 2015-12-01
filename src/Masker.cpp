#include "Masker.h"

//--------------------------------------------------------------
void Masker::setup(){

    leftU.push_back(ofVec3f(10, 10, 0));
    leftU.push_back(ofVec3f(0, 500, 0));
    leftU.push_back(ofVec3f(0, 0, 0));
    leftU.push_back(ofVec3f(512, 0, 0));

    leftD.push_back(ofVec3f(10, 758, 0));
    leftD.push_back(ofVec3f(0, 500, 0));
    leftD.push_back(ofVec3f(0, 768, 0));
    leftD.push_back(ofVec3f(512, 768, 0));

    rightU.push_back(ofVec3f(1014, 10, 0));
    rightU.push_back(ofVec3f(1024, 500, 0));
    rightU.push_back(ofVec3f(1024, 0, 0));
    rightU.push_back(ofVec3f(512, 0, 0));

    rightD.push_back(ofVec3f(1014, 758, 0));
    rightD.push_back(ofVec3f(1024, 500, 0));
    rightD.push_back(ofVec3f(1024, 768, 0));
    rightD.push_back(ofVec3f(512, 768, 0));

    particleAddedLU = false;
    particleAddedLD = false;
    particleAddedRU = false;
    particleAddedRD = false;

}

//--------------------------------------------------------------
void Masker::update(){
}

//--------------------------------------------------------------
void Masker::draw(bool maskFinished){
    ofPushStyle();
    if(maskFinished){
	ofSetColor(0, 0, 0, 255);
	ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    }
    ofSetLineWidth(3);
   
    if(!maskFinished){
	ofSetColor(255, 0, 0, 150);
    }
    glBegin(GL_POLYGON);
    for(int i = 0; i < leftU.size(); i ++){
        glVertex3f(leftU[i].x, leftU[i].y, 0.0f);
    }
    glEnd();

    if(!maskFinished){
        ofSetColor(0, 255, 0, 150);
    }
    glBegin(GL_POLYGON);
    for(int i = 0; i < leftD.size(); i ++){
        glVertex3f(leftD[i].x, leftD[i].y, 0.0f);
    }
    glEnd();

    if(!maskFinished){
        ofSetColor(0, 0, 255, 150);
    }
    glBegin(GL_POLYGON);
    for(int i = 0; i < rightU.size(); i ++){
        glVertex3f(rightU[i].x, rightU[i].y, 0.0f);
    }
    glEnd();

    if(!maskFinished){
        ofSetColor(200, 200, 0, 150);
    }
    glBegin(GL_POLYGON);
    for(int i = 0; i < rightD.size(); i ++){
        glVertex3f(rightD[i].x, rightD[i].y, 0.0f);
    }
    glEnd();

    ofPopStyle();
}

//--------------------------------------------------------------
void Masker::addParticleLU(ofVec3f posL){
    if(particleAddedLU){
	leftU.pop_back();
    }
    leftU.push_back(posL);
    leftU.push_back(ofVec3f(0, 500, 0));
    particleAddedLU = true;
}

//--------------------------------------------------------------
void Masker::addParticleLD(ofVec3f posL){
    if(particleAddedLD){
        leftD.pop_back();
    }
    leftD.push_back(posL);
    leftD.push_back(ofVec3f(0, 500, 0));
    particleAddedLD = true;
}

//--------------------------------------------------------------
void Masker::addParticleRU(ofVec3f posR){
    if(particleAddedRU){
        rightU.pop_back();
    }
    rightU.push_back(posR);
    rightU.push_back(ofVec3f(1024, 500, 0));
    particleAddedRU = true;
}

//--------------------------------------------------------------
void Masker::addParticleRD(ofVec3f posR){
    if(particleAddedRD){
        rightD.pop_back();
    }
    rightD.push_back(posR);
    rightD.push_back(ofVec3f(1024, 500, 0));
    particleAddedRD = true;
}

//--------------------------------------------------------------
int Masker::getNumParticlesLU(){
   return leftU.size(); 
}

//--------------------------------------------------------------
int Masker::getNumParticlesLD(){
   return leftD.size();
}

//--------------------------------------------------------------
int Masker::getNumParticlesRU(){
   return rightU.size();
}

//--------------------------------------------------------------
int Masker::getNumParticlesRD(){
   return rightD.size();
}

//--------------------------------------------------------------
ofVec3f Masker::getPosLU(int i){
   return leftU[i];
}

//--------------------------------------------------------------
ofVec3f Masker::getPosLD(int i){
   return leftD[i];
}

//--------------------------------------------------------------
ofVec3f Masker::getPosRU(int i){
   return rightU[i];
}

//--------------------------------------------------------------
ofVec3f Masker::getPosRD(int i){
   return rightD[i];
}

//--------------------------------------------------------------
void Masker::clear(){
   leftU.clear();
   leftU.clear();
   leftU.clear();
   leftU.clear();
   setup();
}
