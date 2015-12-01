#include "Particle.h"

namespace tri{

     Particle::Particle( const Particle & obj){
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

        mIncType = 0;
     }

    Particle::Particle(){
        mParticleIndex = -1;
        mTargetIndex   = -1;
        mCol = ofColor(255);
        mInsideTriangle = false;
        mTargetPoint = false;
        mIncType = 0;

//      timerMulti = ofRandom(0, 1);
	mTimer = ofRandom(0,1);
        mTimeInc = ofRandom(0, 0.02);
        mTimerDir = 1;
        mStopTimer = false;
    }

    void Particle::setTweenType(int type){
      mIncType = type;
    }


    void Particle::addVelocity(const ofVec3f & vel){
        mVel = vel;
    }

    void Particle::setColor(ofColor col){
        mCol = col;
    }

    void Particle::setParticleId(int index){
        mParticleIndex = index;
    }

    int Particle::getParticleId(){
      return mParticleIndex;
    }

    void Particle::setTargetId(int index){
      mTargetIndex = index;
    }

    int Particle::getTargetId(){
      return mTargetIndex;
    }


    ofVec3f Particle::getPosition(){
        return mPos;
    }

    ofVec3f Particle::getTargetPos(){
      return mTargetPos;
    }

    ofVec3f Particle::getOrignalPos(){
      return mOriginalPos;
    }

    ofVec3f Particle::getMovingPos(){
      return mMovingPos;
    }

    void Particle::setPosition(ofVec3f pos){
        mPos = pos;
    }

    void Particle::setOriginalPos(ofVec3f pos){
      mOriginalPos = pos;
    }

    void Particle::setTargetPos(ofVec3f pos){
        mTargetPos = pos;
    }

    void Particle::setInsideTriangle(bool set){
      mInsideTriangle = set;
    }

    bool  Particle::isInsideTriangle(){
      return mInsideTriangle;
    }

    bool Particle::isTargetPoint(){
      return mTargetPoint;
    }

    void Particle::enableTargetPoint(bool target){
      mTargetPoint = target;
    }


    void Particle::update(float time){
//	time = time * timerMulti;
//        mTime = mTime * timerMulti;
      if(mTargetIndex != -1){
        switch(mIncType){
          case 0:
            mMovingPos.x = (mTargetPos.x - mOriginalPos.x) * (mTimer) + mOriginalPos.x;
            mMovingPos.y = (mTargetPos.y - mOriginalPos.y) * (mTimer) + mOriginalPos.y;
          break;
          case 1:
          {
            float mTime = mTimer*mTimer + mTimer;
            if(mTime < 1.0){
              mMovingPos.x = (mTargetPos.x - mOriginalPos.x) * (mTime) + mOriginalPos.x;
              mMovingPos.y = (mTargetPos.y - mOriginalPos.y) * (mTime) + mOriginalPos.y;
            }
          }
          break;
          case 2:
          {
            float mTime = time*time*time;
            if(mTime < 1.0){
              mMovingPos.x = (mTargetPos.x - mOriginalPos.x) * (mTime) + mOriginalPos.x;
              mMovingPos.y = (mTargetPos.y - mOriginalPos.y) * (mTime) + mOriginalPos.y;
            }
          }
          break;
          case 3:
          {
           float mTime = time*time + time*log(time*time +0.0001);
            if(mTime < 1.0){
                mMovingPos.x = (mTargetPos.x - mOriginalPos.x) * (mTime) + mOriginalPos.x;
                mMovingPos.y = (mTargetPos.y - mOriginalPos.y) * (mTime) + mOriginalPos.y;
            }
          }
          break;
       }
      }
    }

    float  Particle::getX(){return mPos.x;}
    float  Particle::getY(){return mPos.y;}
    float  Particle::getZ(){return mPos.z;}

    void Particle::drawPoint(){
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


void Particle::updateTimers(float newTime){

      mTimer += newTime * mTimerDir;

      if(mTimer >= 1.0){
        mTimerDir *=-1;
      }
      if(mTimer <= 0.0){
        mTimerDir *=-1;
      }

    }





  }
