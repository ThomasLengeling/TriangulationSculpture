#include "ParticleManager.h"


namespace tri{

  void ParticleManager::drawPoints()
  {
    for(auto & particle : mParticles){
      particle->drawPoint();
      ofSetColor(ofColor(255, 0, 0));
      ofDrawBitmapString(" "+ofToString(particle->getParticleId()), particle->getPosition().x + 5, particle->getPosition().y );
    }
  }

  void ParticleManager::drawTriangleMesh()
  {


  }

  void ParticleManager::updateMesh()
  {

  }

  Particle * ParticleManager::getNearestParticle(ofVec3f pos)
  {
    Particle * mTempP = NULL;
    int index = -1;
    for(auto & particle : mParticles){
     if(particle->getPosition().distance(pos) < 15){
       index = particle->getParticleId();
       return particle;
     }
    }
    return mTempP;
  }

    void ParticleManager::updateTargetPositions(){
        for(auto & particle : mParticles){
          if(particle->isInsideTriangle()){
            int targetId = particle->getTargetId();
            if(targetId != -1){

              //__always_inline  std::cout<<particle->getParticleId()<<" "<<targetId<<std::endl;
              //  std::cout<<particle->getTargetPos().x<<" "<<particle->getTargetPos().y<<std::endl;
              //  std::cout<<mParticles.at(targetId)->getPosition().x<<" "<<mParticles.at(targetId)->getPosition().y<<std::endl;
                particle->setTargetPos( mParticles.at(targetId)->getPosition());
              }
          }
        }
    }

    Particle * ParticleManager::getParticle(int index){
      return mParticles.at(index);
    }

    void ParticleManager::updateParticlePos(int index, ofVec3f pos){

      if(mParticles.at(index)->isInsideTriangle() && mParticles.at(index)->isTargetPoint()){
        mParticles.at(index)->setPosition(pos);
        mParticles.at(index)->setOriginalPos(pos);
      }

      if( !mParticles.at(index)->isTargetPoint()){
            mParticles.at(index)->setPosition(pos);
      }

    }

    void ParticleManager::updateTargetPos(int index, ofVec3f pos){
        mParticles.at(index)->setOriginalPos(mParticles.at(index)->getPosition());
        mParticles.at(index)->setTargetPos(pos);
    }

    void ParticleManager::updateTargetId(int index, int targetId){
      mParticles.at(index)->enableTargetPoint(true);
      mParticles.at(index)->setTargetId(targetId);
    }

    void ParticleManager::updateParticleColor(int index, ofColor col){
        mParticles.at(index)->setColor(col);
    }

  void ParticleManager::addParticle(Particle * particle)
  {
    particle->setParticleId(mParticles.size());
    mParticles.push_back(particle);
  }



}
