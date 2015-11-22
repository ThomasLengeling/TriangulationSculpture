/*
Particle by Thomas Sanchez Lengeling
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
        mOriginPos = obj.mPos;
        mInsideTriangle = obj.mInsideTriangle;
      //  mTargetPos = obj.mTargetPos;

        mParticleIndex = obj.mParticleIndex;
        mTargetIndex   = obj.mTargetIndex;
        timerDir       = obj.timerDir;
     }

    Particle(){
        mParticleIndex = -1;
        mTargetIndex   = -1;
        mCol = ofColor(255);
        mInsideTriangle = false;
        timer = 0.0;
        timerDir =1;
    }

    static ParticleRef create(){
        return std::make_shared<Particle>();
    }

    void setPosition(const ofVec3f & pos){
        mPos = pos;
        mOriginPos = pos;
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

    void setTargetPos(ofVec3f pos){
        mTargetPos = pos;
    }

    ofVec3f getTargetPos(){
      return mTargetPos;
    }

    void setInsideTriangle(bool set){
      mInsideTriangle = set;
    }

    bool  isInsideTriangle(){
      return mInsideTriangle;
    }


    void update(){
      if(mTargetIndex != -1){
        mPos.x = (mTargetPos.x - mOriginPos.x)*timer + mOriginPos.x;
        mPos.y = (mTargetPos.y - mOriginPos.y)*timer + mOriginPos.y;
        timer += 0.002 * timerDir;

        if(timer >= 1.0){
          timerDir *=-1;
        }
        if(timer <= 0.0){
          timerDir *=-1;
        }

      }

    }

    float  getX(){return mPos.x;}
    float  getY(){return mPos.y;}
    float  getZ(){return mPos.z;}

    void drawPoint(){
        ofSetColor(mCol);
        ofEllipse(mPos.x, mPos.y, 10, 10);

        ofSetColor(255, 0, 0);
        ofEllipse(mTargetPos.x, mTargetPos.y, 10, 10);

        ofSetColor(0, 255, 0);
        ofEllipse(mOriginPos.x, mOriginPos.y, 10, 10);

        if(mTargetIndex != -1)
         ofLine(mOriginPos.x, mOriginPos.y, mTargetPos.x, mTargetPos.y);
    }

  private:
    ofVec3f     mPos;
    ofVec3f     mTargetPos;
    ofVec3f     mOriginPos;

    ofVec3f     mVel;
    ofColor     mCol;

    bool        mInsideTriangle;

    int         mParticleIndex;
    int         mTargetIndex;

    float       timer;
    int         timerDir;
  };
}
