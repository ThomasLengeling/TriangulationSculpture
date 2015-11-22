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
        time = 1.0;
        mCurrentImgIdx = -1;
        mNextImgIdx    = 0;
        mNextColor     = ofFloatColor(1, 1, 1);
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
          time += 0.001;

          if(time >= 1.0){
            time = 0;
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

    protected:
        std::vector<ofImage> mImages;

        ofFloatColor  mCurrentColor;
        ofFloatColor  mNextColor;

        int           mCurrentImgIdx;
        int           mNextImgIdx;

        float         time;
  };


  class TriangleManager : public ParticleManager{
    public:
      TriangleManager();

      static  TriangleManagerRef create(){
          return std::make_shared<TriangleManager>();
      }

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

    private:

      std::vector<Triangle *>         mTriangles;
      std::vector<ImageCollectionRef> mImagesSequences;
      ofMesh                          mMesh;
  };

}
