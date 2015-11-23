#include "TriangleManager.h"

namespace tri{

    TriangleManager::TriangleManager(){
        mMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        mMesh.enableColors();
        mMesh.enableIndices();
    }

    void TriangleManager::addTriangle(Triangle * tri){
        mTriangles.push_back(tri);
    }

    void TriangleManager::loadImages(){
      //5 sequence files
      for(int i  = 0; i < 4; i++){
        std::string path = "images/sequence0"+ofToString(i+1);
        ofLogVerbose("Path sequence:")<<path<<std::endl;
        ofDirectory dir(path);
        dir.allowExt("jpg");

        dir.listDir();

        ImageCollectionRef mImaSq = ImageCollection::create();
        for(int j = 0; j < dir.numFiles(); j++){
          ofImage img;
          img.loadImage(dir.getPath(j));
          ofLogNotice(dir.getPath(j));
          mImaSq->addImage(img);
        }
        mImagesSequences.push_back(mImaSq);
        ofLogVerbose("number of Images loaded: ")<<mImaSq->getNumberImgs();
      }
      ofLogVerbose("number of Sequences loaded: ")<<mImagesSequences.size();
    }

    void TriangleManager::drawMesh(){
        mMesh.draw();
    }

    void TriangleManager::drawWireFrameMesh(){
       ofSetColor(255);
       mMesh.drawWireframe();
     }

     void TriangleManager::generateTriangles(){
       for(auto & particle : mParticles){
         for(auto & tri : mTriangles){

            if(tri->isPointInTriangle(particle->getPosition())){
              particle->setColor(ofColor(255, 255, 0));
              particle->setInsideTriangle(true);
            }
          }
        }

     }

    void TriangleManager::updateColorMesh(){

      mImagesSequences.at(0)->update();

      for(auto & particle : mParticles){
        float posx = particle->getPosition().x;
        float posy = particle->getPosition().y;
        int   id   = particle->getParticleId();

        int mapX =  int(ofMap(posx, 0.0, ofGetWidth(), 0.0, 512.0));
        int mapY =  int(ofMap(posy, 0.0, ofGetHeight(), 0.0, 512.0));

        //ofFloatColor col = mImagesSequences.at(0)->getNextColor(mapX, mapY);

        //mMesh.setColor(id, col);
        if(particle->isInsideTriangle()){
          particle->update();
          ofVec3f movingParticle = particle->getMovingPos();
          mMesh.setVertex(id, ofPoint(movingParticle.x, movingParticle.y, 0));
        }
      }


      for(auto & tri : mTriangles){
        int idA = tri->getParticleA()->getParticleId();
        int idB = tri->getParticleB()->getParticleId();
        int idC = tri->getParticleC()->getParticleId();

        float centerX = (tri->getParticleA()->getX() + tri->getParticleB()->getX() + tri->getParticleC()->getX() )/3.0;
        float centerY = (tri->getParticleA()->getY() + tri->getParticleB()->getY() + tri->getParticleC()->getY() )/3.0;

        int mapX =  int(ofMap(centerX, 0.0, ofGetWidth(), 0.0, 512.0));
        int mapY =  int(ofMap(centerY, 0.0, ofGetHeight(), 0.0, 512.0));

      //  ofFloatColor col = mImagesSequences.at(0)->getNextColor(mapX, mapY);

      //  mMesh.setColor(idA, col);
      ///  mMesh.setColor(idB, col);
      //  mMesh.setColor(idC, col);
      }

    }


    void TriangleManager::renderMesh(){

      //  ofLogVerbose("Render Mesh: ")<<std::endl;
        mMesh.clear();


        mImagesSequences.at(0)->update();

       for(auto & tri : mTriangles){
            float posAX = tri->getParticleA()->getX();
            float posAY = tri->getParticleA()->getY();

            float posBX = tri->getParticleB()->getX();
            float posBY = tri->getParticleB()->getY();

            float posCX = tri->getParticleC()->getX();
            float posCY = tri->getParticleC()->getY();


            //ofFloatColor col = mImagesSequences.at(0)->getNextColor(mapX, mapY);
            float centerX = (tri->getParticleA()->getX() +  tri->getParticleB()->getX() +  tri->getParticleC()->getY())/3.0;
            float centerY = (tri->getParticleA()->getY() +  tri->getParticleB()->getY() +  tri->getParticleC()->getY())/3.0;

            int mapX = ofMap(centerX, 0.0, ofGetWidth(), 0.0, 512.0);
            int mapY = ofMap(centerY, 0.0, ofGetHeight(), 0.0, 512.0);


            if( tri->getParticleA()->isInsideTriangle()){
                tri->getParticleA()->update();
                ofVec3f targetPos =  tri->getParticleA()->getPosition();

                if( tri->getParticleA()->isTargetPoint()){
                  targetPos =  tri->getParticleA()->getMovingPos();
                }

                mMesh.addVertex(ofPoint(targetPos.x, targetPos.y, 0));
            }else{
                mMesh.addVertex(ofPoint(posAX, posAY));
            }
            mMesh.addColor( mImagesSequences.at(0)->getNextColor( mapX, mapY));
            //mMesh.addColor( mImagesSequences.at(0)->getNextColor( (posAX/ofGetWidth())*512, (posAY/ofGetHeight())*512));

             if( tri->getParticleB()->isInsideTriangle()){
                tri->getParticleB()->update();
                ofVec3f targetPos =  tri->getParticleB()->getPosition();

                if( tri->getParticleB()->isTargetPoint()){
                  targetPos =  tri->getParticleB()->getMovingPos();
                }

                mMesh.addVertex(ofPoint(targetPos.x, targetPos.y, 0));
            }else{
                mMesh.addVertex(ofPoint(posBX, posBY));
            }
             mMesh.addColor( mImagesSequences.at(0)->getNextColor( mapX, mapY));
           // mMesh.addColor( mImagesSequences.at(0)->getNextColor( (posBX/ofGetWidth())*512, (posBY/ofGetHeight())*512));

            if( tri->getParticleC()->isInsideTriangle()){
                tri->getParticleC()->update();
                ofVec3f targetPos =  tri->getParticleC()->getPosition();

                if( tri->getParticleC()->isTargetPoint()){
                  targetPos =  tri->getParticleC()->getMovingPos();
                }

                mMesh.addVertex(ofPoint(targetPos.x, targetPos.y, 0));
            }else{
                mMesh.addVertex(ofPoint(posCX, posCY));
            }
            mMesh.addColor( mImagesSequences.at(0)->getNextColor( mapX, mapY));
           // mMesh.addColor( mImagesSequences.at(0)->getNextColor( (posCX/ofGetWidth())*512, (posCY/ofGetHeight())*512));

            mMesh.addTriangle(mMesh.getNumVertices() -3, mMesh.getNumVertices() - 2, mMesh.getNumVertices()-1);//tri->getParticleA()->getParticleId(), tri->getParticleB()->getParticleId(), tri->getParticleC()->getParticleId());
        }

    //    ofLogVerbose("Node Mesh: ")<<std::endl;
    }

}
