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
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxJSON.h"

#include "ParticleManager.h"
#include "TriangleManager.h"
#include "Triangle.h"
#include "Particle.h"
#include "Masker.h"
#include "VideoSequence.h"


#define PORT 12345
#define NUM_MSG_STRINGS 3

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    //GUI
    ofxPanel             gui;
    bool                 mHideGUI;

    void                 setupGUI();
    void                 saveGUIValues();

    ofxButton      mButtonXMLSave;
    ofxButton			 mButtonOSC;
    ofxButton			 mButtonSaveJSON;
    ofxButton      mButtonResetMesh;

    ofxToggle			 mDebugMesh;

    ofxToggle			 mDrawMesh;
    ofxToggle			 mWireFrameMesh;

		ofxToggle 		     	mButtonGenerateTriangles;
    ofxToggle		     	  mButtonMoveTriangles;

		ofxToggle						 mStopTargetTimer;

    ofxSlider<int>       mBlendMode;

    ofxSlider<int>       mWireFrameWidth;

    //OSC send msg
    ofxOscSender 		 		 mSender;
    ofxOscReceiver		 	 mReceiver;

    ofxSlider<int>       mPortSlider;

    ofxSlider<int>       mHostSlider01;
    ofxSlider<int>       mHostSlider02;
    ofxSlider<int>       mHostSlider03;
    ofxSlider<int>       mHostSlider04;

    ofxSlider<float> 	 	 mSpeedColorSlider;
	  ofxSlider<float>     mSpeedTargetSlider;

	  //Image changers
	  ofxSlider<float>  		mTimeColorSlider;
	  ofxSlider<int>   			mImgIndexSlider;

    //Blend
    void                 switchBlendMode();

    std::string		      mHost;
    void                 setupOSC();

    //OSC Receiver
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    int mouseX, mouseY;
    int messages[9];
    //Serial
    ofSerial	           serial;

		//JSON for writing and reading points
    ofxJSONElement 		    mJSON;

    void                  loadJSON();
    void 				  saveJSON();


    //tri::ParticleManagerRef mParticleManager;
    tri::TriangleManagerRef mTriangleManager;
    void                    clearMesh();

    bool enableCreateTriangle;
    bool enableMoveParticles;
    bool enableNewParticle;
	bool enableTargetParticle;

    int  mTempParticleId;

    int  mTargetCounter;
	int  mParticleTargetIdA;
	int  mParticleTargetIdB;

    int triangleCounter;
    int mtempTriA;
    int mtempTriB;
    int mtempTriC;


    //---Video
    video::VideoSequenceRef  mVideoSequence;
    bool                     mDrawVideo;




    //-----------MASK-----------------------------------
    Masker mask;
    bool enableAddPartMaskL;
    bool enableAddPartMaskR;

    bool enableViewFoto;
    ofImage foto;

    bool    mDrawMask;


};
