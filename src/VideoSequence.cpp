#include "VideoSequence.h"

namespace video{

  VideoSequence::VideoSequence() :
    mLooping(false),
    mPlaying(false),
    mComplete(false),
    mCurrentFrame(0),
    mFrameRate(30),
    mDoneLoading( false ),
    mLoadFlag( true )
  {}

  VideoSequence::~VideoSequence(){
    mImageSeq.clear();
  }

  //load files from a specific directory
  //load number of frames only works in release mode
  void VideoSequence::loadSequenceFromDir(std::string folderName )
  {
    mImageSeq.clear();
    //std::string path = "movies/movie0"+ofToString(i+1);

    std::string path = "movies/"+folderName;
    ofLogVerbose("Path sequence:")<<path<<std::endl;
    ofDirectory dir(path);
    dir.allowExt("png");

    dir.listDir();

    int istep = 0;

    for(int j = 0; j < dir.numFiles(); j++){
      ofImage img;
      img.loadImage(dir.getPath(j));
      ofLogNotice(dir.getPath(j));
      mImageSeq.push_back(img);

      //load only 5 seconds if in debug mode
      #ifdef _DEBUG
      if (istep == 30 * 5){
        break;
      }
      istep++;
      #else

     #endif

    }

    ofLogVerbose("number of Images loaded: ")<<mImageSeq.size()<<std::endl;
    mNumFrames = mImageSeq.size();
  }

  void VideoSequence::play()
  {
    if (!mPlaying){
      mTimeStart = ofGetElapsedTimef();
      mPlaying = true;
      mComplete = false;
      mCurrentFrame = 0;
      ofLogVerbose("Start playing") <<std::endl;
    }
    
  }

  void VideoSequence::pause()
  {
    mPlaying = false;
  }

  //loop the video from the elapsed time
  void VideoSequence::update()
  {
    if (mPlaying && ! mComplete){
      double elapsed = ofGetElapsedTimef() - mTimeStart;

      mCurrentFrame = int(floor(elapsed *  mFrameRate)) % mNumFrames;

      if( mCurrentFrame == mNumFrames - 1 )
      {
        mPlaying = false;
        mComplete = true;
        ofLogVerbose("done playing video") <<std::endl;
        mCurrentFrame = mNumFrames - 1;
      }
    }

  }


  void VideoSequence::loopVideo()
  {
    if (mPlaying){
      double elapsed = ofGetElapsedTimef() - mTimeStart;
      mCurrentFrame =  int(floor(elapsed *  mFrameRate)) % mNumFrames;
    }
  }

  bool VideoSequence::isMovieDone(){
    return mComplete;
  }


  ofImage VideoSequence::getCurrentFrame()
  {
    if (mCurrentFrame >= 0 && mCurrentFrame < mImageSeq.size()){
      return mImageSeq[mCurrentFrame];
    }else{ //return a dommy video?
      return mImageSeq[0];
    }
  }

  void VideoSequence::reset()
  {
    if (mImageSeq.size() > 0){
      mTimeStart = ofGetElapsedTimef();
      mComplete = false;
      mPlaying = false;
    }

  }

  //needs implementation
  void VideoSequence::setLooping(bool doLoop)
  {
    mLooping = doLoop;
  }

  bool VideoSequence::isPlaying()
  {
    return mPlaying;
  }

  void VideoSequence::setFrameRate(const double & frameRate)
  {
    mFrameRate = frameRate;
  }

}
