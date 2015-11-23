/*
 Copyright (c) 2015, Thomas Sanchez Lengeling - All rights reserved.
 This code is intended for use with the C++ openFrameWork library
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
