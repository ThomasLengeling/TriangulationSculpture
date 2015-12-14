#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class Pelos{
	public:
	
	
		// --------------------------------
		void setup()
		{
			//fontSmall.loadFont("Fonts/DIN.otf", 8 );
			
			//ofxGuiSetFont( "Fonts/DIN.otf", 8 );
			ofxGuiSetDefaultWidth( 260 );
			
			string xmlSettingsPath = "Settings/NoiseGrid.xml";
			gui.setup( "Noise Grid", xmlSettingsPath );

			gui.add( frequency.set("Frequency",  1.0f,  0.01f,  2.0f) );
			gui.add( timeFrequency.set("Time Frequency",  0.3f,  0.001f,  3.0f) );
			gui.add( magnitude.set("Magnitude",  0.5f,  0.0f,  5.0f) );

			gui.add( gridSize.set("Grid Size",  6.0f,  0.01f,  20.0f) );
			gui.add( gridResolution.set("Grid Resolution",  20,  3,  100) );
			
			gui.loadFromFile( xmlSettingsPath );
			
			drawGui = true;
		}


		// --------------------------------
		void update(vector<ofVec3f> positions)
		{
			float time = ofGetElapsedTimef();
			float noiseTime = time * timeFrequency;
			
			ofVec3f extentMin( gridSize * -0.5, 0,		  gridSize * -0.5 );
			ofVec3f extentMax( gridSize *  0.5, gridSize, gridSize *  0.5 );
			

			
			mesh.clear();
			mesh.setMode( OF_PRIMITIVE_LINES );
			
		   for(int i = 0; i < positions.size(); i ++){
			ofVec3f noisePos = positions[i] * frequency ;
			ofVec3f vel;
			vel.x = ofSignedNoise(noisePos.x, noisePos.y, noisePos.z, noiseTime);
			vel.y = ofSignedNoise(noiseTime, noisePos.z, noisePos.y, noisePos.x);
			vel.z = ofSignedNoise(noisePos.z, noiseTime, noisePos.y, noisePos.x);

//			ofVec3f normVel = vel.getNormalized();
			ofVec3f velAsCol = (vel + ofVec3f(1))* 0.5;

			ofFloatColor tmpCol(velAsCol.x/20, velAsCol.y, velAsCol.z/20);

			mesh.addVertex(positions[i]);
			mesh.addColor(tmpCol);

			mesh.addVertex(positions[i] + (vel * magnitude*200));
			mesh.addColor(ofFloatColor(tmpCol, 0.0));	
		   }
		}
	
		// --------------------------------
		void draw()
		{
//			ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);

			
			ofEnableDepthTest();
/*			
			
				// draw a grid on the floor
				ofSetColor( ofColor(60) );
					ofPushMatrix();
					ofRotate(90, 0, 0, -1);
					ofDrawGridPlane( 10, 10, false );
				ofPopMatrix();
			
				ofSetColor( ofColor::white );
*/				//ofDrawBox( 1.0f );
				mesh.draw();
			


			ofDisableDepthTest();
			if( drawGui ) { gui.draw(); }
/*			
			ofSetColor( ofColor::black );
			fontSmall.drawString( ofToString(ofGetFrameRate(), 1), ofGetWidth() - 25, ofGetHeight() - 5 );
	*/	}
	
		// --------------------------------
		void keyPressed( int _key )
		{
			if( _key == ' ' )			  { }
			else if( _key == OF_KEY_TAB ) { drawGui = !drawGui; }
			else if( _key == 'f' )		  { ofToggleFullscreen(); }
		
		}


		ofMesh				mesh;
	
		ofxPanel			gui;
	
		ofParameter<float>	frequency;
		ofParameter<float>	timeFrequency;

		ofParameter<float>	magnitude;
	
		ofParameter<float>	gridSize;
		ofParameter<int>	gridResolution;
	
		bool				drawGui;
	
		ofTrueTypeFont		fontSmall;
};
