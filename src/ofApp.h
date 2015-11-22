#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxJSON.h"

#include "ParticleManager.h"
#include "TriangleManager.h"
#include "Triangle.h"
#include "Particle.h"

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

    ofxButton            mButtonXMLSave;
    ofxButton			 			 mButtonOSC;
    ofxButton			 			 mButtonSaveJSON;
    ofxButton            mButtonResetMesh;

    ofxToggle			 		   mDebugMesh;

    ofxToggle						 mDrawMesh;
	  ofxToggle						 mWireFrameMesh;

	  ofxSlider<int>       mWireFrameWidth;

    //OSC send msg
    ofxOscSender 		 		 sender;
    ofxSlider<int>       mPortSlider;

    ofxSlider<int>       mHostSlider01;
    ofxSlider<int>       mHostSlider02;
    ofxSlider<int>       mHostSlider03;
    ofxSlider<int>       mHostSlider04;

    std::string				   mHost;
    void                 setupOSC();

    //Serial
    ofSerial	           serial;

		//JSON for writing and reading points
    ofxJSONElement 		    mJSON;

    void                  loadJSON();
    void 				          saveJSON();


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

};
