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

    ofxButton            mButtonXMLSave;
    ofxButton			 mButtonOSC;
    ofxButton			 mButtonSaveJSON;
    ofxButton            mButtonResetMesh;

    ofxToggle			 mDebugMesh;

    ofxToggle			 mDrawMesh;
    ofxToggle			 mWireFrameMesh;

	ofxToggle 		     mButtonGenerateTriangles;
    ofxToggle		     mButtonMoveTriangles;

    ofxSlider<int>       mBlendMode;

    ofxSlider<int>       mWireFrameWidth;

    //OSC send msg
    ofxOscSender 		 mSender;
    ofxOscReceiver		 mReceiver;
    ofxSlider<int>       mPortSlider;

    ofxSlider<int>       mHostSlider01;
    ofxSlider<int>       mHostSlider02;
    ofxSlider<int>       mHostSlider03;
    ofxSlider<int>       mHostSlider04;

    ofxSlider<float> 	 mSpeedColorSlider;
	ofxSlider<float>     mSpeedTargetSlider;

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

    //-----------MASK-----------------------------------
    Masker mask;
    bool enableAddPartMaskL;
    bool enableAddPartMaskR;

    bool enableViewFoto;
    ofImage foto;

    bool    mDrawMask;


};
