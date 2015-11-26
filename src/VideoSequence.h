/*
 Copyright (c) 2015, Thomas Sanchez Lengeling - All rights reserved.
 This code is intended for use with the C++ openFrameworks library
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

namespace video{

	class VideoSequence;
	typedef std::shared_ptr<VideoSequence> VideoSequenceRef;

	class VideoSequence{
	public:

		VideoSequence();
		~VideoSequence();

		static VideoSequenceRef create(){
			return  std::make_shared<VideoSequence>();
		}

		//load files from a specific directory
		//load number of frames only works in release mode
		void loadSequenceFromDir( std::string folderName );

		void loadNextFrame();

		void play();

		void pause();

		ofImage getCurrentFrame();

		//loop the video from the elapsed time
		void update();

		void loopVideo();

		bool isMovieDone();

		void reset();

		//needs implementation
		void setLooping(bool doLoop);

		bool isPlaying();

		void setFrameRate(const double & frameRate);

	private:

		std::vector<ofImage> mImageSeq;

		int									mNumFrames; //max number of frames
	  int									mTotalNumFrames; //max number of frames

		double							mTimeStart;

		bool								mLooping;
		bool						  	mPlaying;
		bool								mComplete;
	  bool              	mDoneLoading;
	  bool             	  mLoadFlag;

		double							mFrameRate;

	  int							  	mLoadedFrames;   //  frame up until which we have loaded the sequence
		int									mCurrentFrame;  //  current frame the squence is on
	  int							  	mLoadOnStart;   //  how many frames shoudl be loaded on startup
	};

}
