#pragma once

#include "ofMain.h"
#include "Particle.h"

namespace tri{

  class Triangle{
    public:
      Triangle(){}

      Particle * getParticleA(){return mParticleA;}
      Particle * getParticleB(){return mParticleB;}
      Particle * getParticleC(){return mParticleC;}

      ofVec3f    getPositionA(){return mParticleA->getPosition();}
      ofVec3f    getPositionB(){return mParticleB->getPosition();}
      ofVec3f    getPositionC(){return mParticleC->getPosition();}

      int        getIndexA(){return mParticleA->getParticleId();}
      int        getIndexB(){return mParticleB->getParticleId();}
      int        getIndexC(){return mParticleC->getParticleId();}

      void       setParticleA( Particle * pa){mParticleA = pa;}
      void       setParticleB( Particle * pb){mParticleB = pb;}
      void       setParticleC( Particle * pc){mParticleC = pc;}


      float sign (ofVec3f p1, ofVec3f p2, ofVec3f p3){
         return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
       }

      bool isPointInTriangle (ofVec3f pt){

        if(pt == mParticleA->getPosition() ||
           pt == mParticleC->getPosition()  ||
           pt == mParticleB->getPosition())
          return false;

        bool b1, b2, b3;

        b1 = sign(pt, mParticleA->getPosition(),  mParticleB->getPosition()) < 0.0f;
        b2 = sign(pt, mParticleB->getPosition(),  mParticleC->getPosition()) < 0.0f;
        b3 = sign(pt, mParticleC->getPosition(),  mParticleA->getPosition()) < 0.0f;

        return ((b1 == b2) && (b2 == b3));
      }

    private:

        Particle * mParticleA;
        Particle * mParticleB;
        Particle * mParticleC;
  };

}
