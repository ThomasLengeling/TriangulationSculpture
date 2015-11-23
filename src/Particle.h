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
        mOriginalPos = obj.mPos;
        mInsideTriangle = obj.mInsideTriangle;
      //  mTargetPos = obj.mTargetPos;

        mParticleIndex = obj.mParticleIndex;
        mTargetIndex   = obj.mTargetIndex;
        timerDir       = obj.timerDir;

        mTargetPoint = false;

        timer = 0.0;
        timerDir =1;
     }

    Particle(){
        mParticleIndex = -1;
        mTargetIndex   = -1;
        mCol = ofColor(255);
        mInsideTriangle = false;
        timer = 0.0;
        timerDir = 1;

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


    void update(){
      if(mTargetIndex != -1){
        mMovingPos.x = (mTargetPos.x - mOriginalPos.x)*timer + mOriginalPos.x;
        mMovingPos.y = (mTargetPos.y - mOriginalPos.y)*timer + mOriginalPos.y;

        timer += 0.02 * timerDir;

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

    float       timer;
    int         timerDir;
  };
}
