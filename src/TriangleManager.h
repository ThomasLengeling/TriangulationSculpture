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

#include "Triangle.h"
#include  "ParticleManager.h"

namespace tri{

  class TriangleManager;
  class ImageCollection;

  typedef std::shared_ptr<TriangleManager> TriangleManagerRef;
  typedef std::shared_ptr<ImageCollection> ImageCollectionRef;

  class ImageCollection{
    public:

      ImageCollection(){
        mTime = 1.0;
        mTransitionInc = 0.005;

        mCurrentImgIdx = -1;
        mNextImgIdx    =  0;
        mNextColor     =  ofFloatColor(1, 1, 1);
      }

       static ImageCollectionRef create(){
         return make_shared<ImageCollection>();
       }

        void addImage(ofImage img){
          mImages.push_back(img);
        }

        ofColor getColor(int i, int x, int y){
          return mImages.at(i).getColor(x, y);
        }

        int getNumberImgs(){
          return mImages.size();
        }

        ofFloatColor  getNextColor(int x, int y){
          ofFloatColor mNewColor;
          if(mImages.size() > 0){
            ofColor currColor = getColor(mCurrentImgIdx, x, y);
            ofColor nextColor = getColor(mNextImgIdx, x, y);

            mCurrentColor = ofFloatColor( currColor.r/255.0, currColor.g/255.0, currColor.b/255.0, currColor.a/255.0 );
            mNextColor    = ofFloatColor( nextColor.r/255.0, nextColor.g/255.0, nextColor.b/255.0, nextColor.a/255.0 );

            mNewColor.r = (mNextColor.r - mCurrentColor.r) * time + mCurrentColor.r;
            mNewColor.g = (mNextColor.g - mCurrentColor.g) * time + mCurrentColor.g;
            mNewColor.b = (mNextColor.b - mCurrentColor.b) * time + mCurrentColor.b;
          }

          return mNewColor;
        }

        void update(){
          mTime += mTransitionInc;

          if(mTime >= 1.0){
            mTime = 0;
            if(mImages.size() > 0){
                mCurrentImgIdx++;

                if(mCurrentImgIdx >= mImages.size() ){
                  mCurrentImgIdx = 0;
                  mNextImgIdx =   mCurrentImgIdx + 1;
                }else{
                  if(mCurrentImgIdx == mImages.size() - 1)
                    mNextImgIdx = 0;
                  else
                    mNextImgIdx =  mCurrentImgIdx + 1;
                }

                ofLogVerbose("Update Image Coll: ")<<mCurrentImgIdx<<" "<<mNextImgIdx<<std::endl;
              }
           }

        }

        void setTransitionInc(float val){
          mTransitionInc = val;
        }

    protected:
        std::vector<ofImage> mImages;

        ofFloatColor  mCurrentColor;
        ofFloatColor  mNextColor;

        int           mCurrentImgIdx;
        int           mNextImgIdx;

        float         mTime;
        float         mTransitionInc;
  };


  class TriangleManager : public ParticleManager{
    public:
      TriangleManager();

      static  TriangleManagerRef create(){ return std::make_shared<TriangleManager>(); }

      void loadImages();

      void generateTriangles();

      void drawMesh();

      void drawWireFrameMesh();

      void renderMesh();
      void updateColorMesh();

      void cleanMesh(){mTriangles.clear(); mParticles.clear(); mMesh.clear(); }

      void addTriangle(Triangle * tri);

      int        getNumberOfTriangles(){return mTriangles.size();}
      Triangle * getTriangle(int index){return mTriangles.at(index);}


      void setIncrementTimeColors(float val){ mImagesSequences->setTransitionInc(val); }
      void setImageSequence(int val){ mCurrentImgSeq = val; }

    private:

      std::vector<Triangle *>         mTriangles;

      std::vector<ImageCollectionRef> mImagesSequences;
      int                             mCurrentImgSeq;

      ofMesh                          mMesh;
  };

}
