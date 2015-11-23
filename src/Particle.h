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

     Particle( const Particle & obj){
        mPos = obj.mPos;
        mTargetPos = obj.mTargetPos;
        mVel = obj.mVel;
        mCol = obj.mCol;
        mOriginalPos = obj.mPos;
        mInsideTriangle = obj.mInsideTriangle;
      //  mTargetPos = obj.mTargetPos;

        mParticleIndex = obj.mParticleIndex;
        mTargetIndex   = obj.mTargetIndex;

        mTargetPoint = false;
     }

    Particle(){
        mParticleIndex = -1;
        mTargetIndex   = -1;
        mCol = ofColor(255);
        mInsideTriangle = false;
        mTargetPoint = false;
    }

    static ParticleRef create(){
        return std::make_shared<Particle>();
    }

    void addVelocity(const ofVec3f & vel){
        mVel = vel;
    }

    void setColor(ofColor col){
        mCol = col;
    }

    void setParticleId(int index){
        mParticleIndex = index;
    }

    int getParticleId(){
      return mParticleIndex;
    }

    void setTargetId(int index){
      mTargetIndex = index;
    }

    int getTargetId(){
      return mTargetIndex;
    }


    ofVec3f getPosition(){
        return mPos;
    }

    ofVec3f getTargetPos(){
      return mTargetPos;
    }

    ofVec3f getOrignalPos(){
      return mOriginalPos;
    }

    ofVec3f getMovingPos(){
      return mMovingPos;
    }

    void setPosition(ofVec3f pos){
        mPos = pos;
    }

    void setOriginalPos(ofVec3f pos){
      mOriginalPos = pos;
    }

    void setTargetPos(ofVec3f pos){
        mTargetPos = pos;
    }

    void setInsideTriangle(bool set){
      mInsideTriangle = set;
    }

    bool  isInsideTriangle(){
      return mInsideTriangle;
    }

    bool isTargetPoint(){
      return mTargetPoint;
    }

    void enableTargetPoint(bool target){
      mTargetPoint = target;
    }


    void update(float time){
      if(mTargetIndex != -1){
        mMovingPos.x = (mTargetPos.x - mOriginalPos.x) * time + mOriginalPos.x;
        mMovingPos.y = (mTargetPos.y - mOriginalPos.y) * time + mOriginalPos.y;
      }

    }

    float  getX(){return mPos.x;}
    float  getY(){return mPos.y;}
    float  getZ(){return mPos.z;}

    void drawPoint(){
        if(mTargetIndex != -1){
          ofSetColor(0, 0, 255);
          ofEllipse(mTargetPos.x, mTargetPos.y, 10, 10);
          ofEllipse(mOriginalPos.x, mOriginalPos.y, 10, 10);


          ofEllipse(mMovingPos.x, mMovingPos.y, 14, 14);

          ofSetColor(0, 255, 0);
          ofLine(mOriginalPos.x, mOriginalPos.y, mTargetPos.x, mTargetPos.y);
       }else{
         ofSetColor(mCol);
         ofEllipse(mPos.x, mPos.y, 10, 10);
       }

       if(mTargetPoint){
         ofSetColor(0, 255, 255);
         ofEllipse(mTargetPos.x, mTargetPos.y, 10, 10);
         ofEllipse(mOriginalPos.x, mOriginalPos.y, 10, 10);
       }

    }



  private:
    ofVec3f     mPos;  //original

    ofVec3f     mTargetPos;
    ofVec3f     mOriginalPos;

    ofVec3f     mMovingPos;

    ofVec3f     mVel;
    ofColor     mCol;

    bool        mInsideTriangle;

    bool        mTargetPoint;

    int         mParticleIndex;
    int         mTargetIndex;

  };
}
