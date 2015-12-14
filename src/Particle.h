/*
 Copyright (c) 2015, Thomas Sanchez Lengeling - All rights reserved.
 This code is intended for use with the C++ openFrameworks library
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:
	* Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include "ofMain.h"

namespace tri{
  class Particle;

  typedef std::shared_ptr<Particle> ParticleRef;

  class Particle{
  public:

    Particle( const Particle & obj);
    Particle();

    static ParticleRef create(){
        return std::make_shared<Particle>();
    }

    void setTweenType(int type);

    void addVelocity(const ofVec3f & vel);

    void setColor(ofColor col);

    void setParticleId(int index);

    int getParticleId();

    void setTargetId(int index);

    int getTargetId();

    ofVec3f getPosition();

    ofVec3f getTargetPos();

    ofVec3f getOrignalPos();

    ofVec3f getMovingPos();

    void setPosition(ofVec3f pos);

    void setOriginalPos(ofVec3f pos);

    void setTargetPos(ofVec3f pos);

    void setInsideTriangle(bool set);

    bool  isInsideTriangle();

    bool isTargetPoint();

    void enableTargetPoint(bool target);

    void update(float time);

    float  getX();
    float  getY();
    float  getZ();

    void drawPoint();
void updateTimers(float);
float mTimer;
float mTimeInc;
float mult;
int mTimerDir;
bool mStopTimer;

  private:
    ofVec3f     mPos;  //original

    ofVec3f     mTargetPos;
    ofVec3f     mOriginalPos;

    ofVec3f     mMovingPos;

    ofVec3f     mVel;
    ofColor     mCol;

    //Tween type
    int         mIncType;
    float timerMulti;
    bool        mInsideTriangle;

    bool        mTargetPoint;

    int         mParticleIndex;
    int         mTargetIndex;

    float       mTime;


  };

}
