/**
Particle Manger by Thomas Sanchez Lengeling
*/

#pragma once


#include "ofMain.h"
#include <vector>
#include "Particle.h"

namespace tri{
  class ParticleManager;

  typedef std::shared_ptr<ParticleManager> ParticleManagerRef;

  class ParticleManager{
    public:
      ParticleManager(){}

      static ParticleManagerRef create(){
  			return std::make_shared<ParticleManager>();
  		}

      Particle * getNearestParticle(ofVec3f pos);

      Particle * getParticle(int index);
      int        getNumberOfParticles(){return mParticles.size();}

      void drawPoints();
      void drawTriangleMesh();

      void updateMesh();


      void addParticle(Particle * particle);

      void updateTargetPositions();


      void updateParticlePos(int index, ofVec3f pos);
      void updateTargetPos(int index, ofVec3f pos);
      void updateTargetId(int index, int targetId);
      void updateTriangleId(int index, int triId);
      void updateParticleColor(int index, ofColor col);


   protected:
        std::vector<Particle *> mParticles;
  };
}
