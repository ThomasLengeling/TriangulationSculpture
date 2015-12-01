#include "ofApp.h"

using namespace tri;

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetVerticalSync(true);

  ofSetFrameRate(30);

  ofSetLogLevel(OF_LOG_VERBOSE);

  //SMOOTH
  ofEnableAntiAliasing();

  ofEnableSmoothing();

  //ofEnableAlphaBlending();

  //ofEnableBlendMode(OF_BLENDMODE_ADD);

  //mParticleManager = ParticleManager::create();
  mTriangleManager = TriangleManager::create();
  enableCreateTriangle = false;
  enableMoveParticles  = false;
  enableNewParticle    = false;
  enableTargetParticle = false;

  triangleCounter      = 0;

  mTargetCounter       = 0;

  mTriangleManager->loadImages();

  setupGUI();

  setupOSC();
  
   //MASK
    mask.setup();

  loadJSON(setWhiteWire);

  mTriangleManager->generateTriangles();

  foto.loadImage("foto.jpg");
  enableViewFoto = false;
  mDrawMask = false;
  mFinishMask = false;

  enableAddPartMaskLU = false;
  enableAddPartMaskLD = false;
  enableAddPartMaskRU = false;
  enableAddPartMaskLU = false;


  //-----------VIDEO-----------------------------------
  player.setup();
  enabledVideo = false;

  //----------MOOD------------------------------------
  setWhiteWire = false;
  startDelay = 0;
  enableStartDelay = false;

  enableLineDelay = false;
  for(int i = 0; i < 3; i++){
	lineDelay.push_back(0);
  }
  numTriangles = 0;
  for(int i = 0; i < NUM_RAND - 1; i ++){
 	lineStep.push_back(1.0/(300.0 - i*2*20));
  }
  lineGoesUp = true;

  enableFacetas = false;
}

void ofApp::setupGUI(){

    mButtonXMLSave.addListener(this,&ofApp::saveGUIValues);
    mButtonOSC.addListener(this, &ofApp::setupOSC);
    mButtonSaveJSON.addListener(this, &ofApp::saveJSON);
    mButtonResetMesh.addListener(this, &ofApp::clearMesh);

    gui.setup("GUI");


    gui.add(mPortSlider.setup("Port", 36000, 12000, 90000));
    gui.add(mHostSlider01.setup("Host 01", 192, 0, 255));
    gui.add(mHostSlider02.setup("Host 02", 168, 0, 255));
    gui.add(mHostSlider03.setup("Host 03", 1, 0, 255));
    gui.add(mHostSlider04.setup("Host 04", 1, 0, 255));

    gui.add(mDrawMesh.setup("Draw Mesh", true));
    gui.add(mDebugMesh.setup("Debug Mesh", false));

    gui.add(mBlendMode.setup("Alpha Mode", 0, 0, 5));

    gui.add(mButtonXMLSave.setup("Save Console Values"));
    gui.add(mButtonOSC.setup("Setup OSC"));
    gui.add(mButtonSaveJSON.setup("Save Mesh"));
    gui.add(mButtonResetMesh.setup("Reset Mesh"));

    gui.add(mWireFrameMesh.setup("WireFrame Mesh", true));
    gui.add(mWireFrameWidth.setup("Line Width", 3, 1, 6));
    gui.add(mButtonGenerateTriangles.setup("Generate Inside"));
    gui.add(mButtonMoveTriangles.setup("Enable Move"));
    gui.add(mTimeColorSlider.setup("Color Inc", 0.001, 0.0, 0.1));
    gui.add(mImgIndexSlider.setup("Img Sequence", 0, 0, 4));
    gui.add(mSpeedTargetSlider.setup("Target Transition", 0.001, 0, 0.1));
    gui.add(mStopTargetTimer.setup("Target Stop", false));

    mHideGUI = true;

    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::clearMesh(){
    mTriangleManager->cleanMesh();
    mTriangleManager->renderMesh();
    mask.clear();
}

void ofApp::saveGUIValues(){
    std::cout<<"saving file"<<std::endl;
    gui.saveToFile("settings.xml");
}

void ofApp::setupOSC()
{
    try{
    std::string host = ofToString((int)mHostSlider01)+"."+ofToString((int)mHostSlider02)+"."+ofToString((int)mHostSlider03)+"."+ofToString((int)mHostSlider04);
    std::cout<<"setup OSC: "<<host<<" "<<mPortSlider<<std::endl;
	  mSender.setup(host, mPortSlider);
    }catch(std::exception & e){
        std::cout<<e.what()<<std::endl;
    }

	//RECEIVER
    for (int i = 0; i <= 8; i++)
		messages[i] = 0;
	cout << "listening for osc messages on port " << PORT << "\n";
	 mReceiver.setup(PORT);
	current_msg_string = 0;
}

void ofApp::loadJSON(bool white){
    std::string file;
    if(white){
	file = "white.json";
    }else{
        file = "mesh.json";
    }
    bool parsingSuccessful = mJSON.open(file);
    if(parsingSuccessful){
         ofLogNotice("ofApp::setup") << "successfully read: "<<file<<std::endl;
    }else{
         ofLogError("ofApp::setup")  << "Failed to parse JSON" << std::endl;
    }

    for (const Json::Value & points : mJSON["Particles"])  // iterate over "points"
    {
        float px   = points["x"].asFloat();
        float py   = points["y"].asFloat();
        float ptx  = points["tx"].asFloat();
        float pty  = points["ty"].asFloat();
        int   ptid = points["tid"].asInt();
        int   ptida = points["tida"].asInt();

        Particle * tmpParticles = new Particle();
        tmpParticles->setTargetId(ptid);
        tmpParticles->setPosition(ofVec3f(px, py, 0));

        tmpParticles->enableTargetPoint( (ptida) ? true : false);
        tmpParticles->setOriginalPos(ofVec3f(px, py, 0));
        tmpParticles->setTargetPos(ofVec3f(ptx, pty, 0));
        mTriangleManager->addParticle(tmpParticles);
    }

    for (const Json::Value & triangles : mJSON["Triangles"])  // iterate over "points"
    {
        int idA = triangles["idA"].asInt();
        int idB = triangles["idB"].asInt();
        int idC = triangles["idC"].asInt();

        Triangle * tri = new Triangle();
        tri->setParticleA( mTriangleManager->getParticle(idA) );
        tri->setParticleB( mTriangleManager->getParticle(idB) );
        tri->setParticleC( mTriangleManager->getParticle(idC) );

        mTriangleManager->addTriangle(tri);
    }

    for (const Json::Value & particlesLU : mJSON["ParticlesLU"])  // iterate over "points"
    {
        int px = particlesLU["px"].asFloat();
        int py = particlesLU["py"].asFloat();

        ofVec3f tempLU;
	tempLU.set(px, py, 0);

        mask.addParticleLU(tempLU);
    }

    for (const Json::Value & particlesLD : mJSON["ParticlesLD"])  // iterate over "points"
    {
        int px = particlesLD["px"].asFloat();
        int py = particlesLD["py"].asFloat();

        ofVec3f tempLD;
        tempLD.set(px, py, 0);

        mask.addParticleLD(tempLD);
    }

    for (const Json::Value & particlesRU : mJSON["ParticlesRU"])  // iterate over "points"
    {
        int px = particlesRU["px"].asFloat();
        int py = particlesRU["py"].asFloat();

        ofVec3f tempRU;
        tempRU.set(px, py, 0);

        mask.addParticleRU(tempRU);
    }

    for (const Json::Value & particlesRD : mJSON["ParticlesRD"])  // iterate over "points"
    {
        int px = particlesRD["px"].asFloat();
        int py = particlesRD["py"].asFloat();

        ofVec3f tempRD;
        tempRD.set(px, py, 0);

        mask.addParticleRD(tempRD);
    }

    mTriangleManager->renderMesh();
    //mTriangleManager->updateColorMesh();
    mTriangleManager->updateTargetPositions();
}

void ofApp::saveJSON(){

   mJSON.clear();
  //Json::Value root(Json::arrayValue);
  if(mTriangleManager->getNumberOfParticles()){
        Json::Value points(Json::arrayValue);
        for (int j = 0; j < mTriangleManager->getNumberOfParticles(); j++){
            Json::Value pos(Json::objectValue);
            pos["x"] = mTriangleManager->getParticle(j)->getPosition().x;
            pos["y"] = mTriangleManager->getParticle(j)->getPosition().y;
            pos["tx"] = mTriangleManager->getParticle(j)->getTargetPos().x;
            pos["ty"] = mTriangleManager->getParticle(j)->getTargetPos().y;
            pos["tid"] =  mTriangleManager->getParticle(j)->getTargetId();
            pos["tida"] =  (mTriangleManager->getParticle(j)->isTargetPoint() == true) ? 1 : 0;
            points.append(pos);
        }
        mJSON["Particles"]  = points;
  }
  if( mTriangleManager->getNumberOfTriangles() > 0){
      std::cout<<"num Tri"<<mTriangleManager->getNumberOfTriangles()<<std::endl;
      Json::Value triangles(Json::arrayValue);
      for (int j = 0; j < mTriangleManager->getNumberOfTriangles(); j++){
            Json::Value ids(Json::objectValue);
            ids["idA"] = mTriangleManager->getTriangle(j)->getIndexA();
            ids["idB"] = mTriangleManager->getTriangle(j)->getIndexB();
            ids["idC"] = mTriangleManager->getTriangle(j)->getIndexC();
            triangles.append(ids);
      }
     mJSON["Triangles"] = triangles;
  }

if( mask.getNumParticlesLU() > 4){
      std::cout<<"num PartLU"<<mask.getNumParticlesLU()<<std::endl;
      Json::Value particlesLU(Json::arrayValue);
      ofVec3f tempLU;
      for (int j = 4; j < mask.getNumParticlesLU() -1; j++){
            Json::Value ids(Json::objectValue);
            tempLU.set(mask.getPosLU(j));
            ids["px"] = tempLU.x;
            ids["py"] = tempLU.y;
            particlesLU.append(ids);
      }
     mJSON["ParticlesLU"] = particlesLU;
  }

if( mask.getNumParticlesLD() > 4){
      std::cout<<"num PartLD"<<mask.getNumParticlesLD()<<std::endl;
      Json::Value particlesLD(Json::arrayValue);
      ofVec3f tempLD;
      for (int j = 4; j < mask.getNumParticlesLD() -1; j++){
            Json::Value ids(Json::objectValue);
            tempLD.set(mask.getPosLD(j));
            ids["px"] = tempLD.x;
            ids["py"] = tempLD.y;
            particlesLD.append(ids);
      }
     mJSON["ParticlesLD"] = particlesLD;
  }

if( mask.getNumParticlesRU() > 4){
      std::cout<<"num PartRU"<<mask.getNumParticlesRU()<<std::endl;
      Json::Value particlesRU(Json::arrayValue);
      ofVec3f tempRU;
      for (int j = 4; j < mask.getNumParticlesRU() -1; j++){
            Json::Value ids(Json::objectValue);
            tempRU.set(mask.getPosRU(j));
            ids["px"] = tempRU.x;
            ids["py"] = tempRU.y;
            particlesRU.append(ids);
      }
     mJSON["ParticlesRU"] = particlesRU;
  }

if( mask.getNumParticlesRD() > 4){
      std::cout<<"num PartRD"<<mask.getNumParticlesRD()<<std::endl;
      Json::Value particlesRD(Json::arrayValue);
      ofVec3f tempRD;
      for (int j = 4; j < mask.getNumParticlesRD() -1; j++){
            Json::Value ids(Json::objectValue);
            tempRD.set(mask.getPosRD(j));
            ids["px"] = tempRD.x;
            ids["py"] = tempRD.y;
            particlesRD.append(ids);
      }
     mJSON["ParticlesRD"] = particlesRD;
  }

  if (!mJSON.save("mesh.json", true)){
    ofLogNotice("ofApp::setup") << "mesh.json written unsuccessfully.";
  }
  else{
    ofLogNotice("ofApp::setup") << "mesh.json written successfully.";
  }
}


//--------------------------------------------------------------
void ofApp::update(){
//  mTriangleManager->updateColorMesh();
    mTriangleManager->renderMesh();

    mTriangleManager->setIncrColorTimer(mTimeColorSlider);
    mTriangleManager->setImageSeq(mImgIndexSlider);
    mTriangleManager->setIncrTargetTimer(mSpeedTargetSlider);
    mTriangleManager->toggleTimer(mStopTargetTimer);

    if(mButtonMoveTriangles){
         mTriangleManager->generateTriangles();
    }

    // Osc Receiver
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
      if(timers[i] < ofGetElapsedTimef()){
			     msg_strings[i] = "";
      }
    }

	// check for waiting messages
	while(mReceiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		mReceiver.getNextMessage(&m);
		string msg_string;
		msg_string = m.getAddress();
		if(m.getAddress() == "mood"){
		    int arg1 = m.getArgAsInt32(0);
       		    if(arg1 >= 0 && arg1 < 4){
			setVideo(arg1);
		    }
		    if(arg1 >= 4 && arg1 < 9){
			setMood(arg1);
		    }
		}
		msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
					messages[i] = m.getArgAsInt32(i);
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
				}
				else{
				}
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}

    //-----------VIDEO-----------------------------------
    player.update();

    //----------LineUpdate-----------------------------
/*
    if(lineDelay[0] < 300){
	lineDelay[0] ++;
    }
    if(lineDelay[0] == 300 && lineDelay[1] < 300){
	lineDelay[1] ++;
    }
    if(lineDelay[1] == 300 && lineDelay[2] < 300){
	lineDelay[2] ++;
    }
*/

    if(enableFacetas){
	man.update();
	man.checkAll();
    }
}

//--------------------------------------------------------------
void ofApp::switchBlendMode()
{
    switch(mBlendMode){
        case 0:
            ofEnableAlphaBlending();
        break;
        case 1:
            ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        break;
        case 2:
            ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        break;
        case 3:
            ofEnableBlendMode(OF_BLENDMODE_ADD);
        break;
        case 4:
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        break;
        case 5:
            ofDisableAlphaBlending();
            ofDisableBlendMode();
        break;
    }

}


void ofApp::draw(){

   ofBackground(ofColor(0));

   switchBlendMode();

    if(enableViewFoto){
        ofPushStyle();
	      ofSetColor(255, 255, 255);
	      foto.draw(250, 20, 520, 730);
        ofPopStyle();
    }
    if(mDrawMesh){
      mTriangleManager->drawMesh();
    }

    if(mWireFrameMesh){
      ofSetLineWidth(int(mWireFrameWidth));
      mTriangleManager->drawWireFrameMesh(setWhiteWire);
    }

    if(mDebugMesh){
      mTriangleManager->drawPoints();
    }


    if( !mHideGUI ){
        gui.draw();
    }

//OSC Receiver

	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 400, 20);
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 400, 40 + 15 * i);
	}

	for (int i = 0; i < 4; i++) {
		ofDrawBitmapString(ofToString(messages[0]), messages[i+1], messages[i+2]);
	}
	
	//VIDEO
    if(enabledVideo){
	player.draw();
    }
    if(enableStartDelay){
	drawStartDelay();
    }
    if(enableLineDelay){
        drawLineDelay();
    }
    if(enableFacetas){
        drawFacetas();
    }
	//MASK

    if(mDrawMask){
        mask.draw(mFinishMask);
    }
	/*ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(mask.getNumParticlesLU()), 300, 20);
	ofDrawBitmapString(ofToString(mask.getNumParticlesLD()), 300, 30);
	ofDrawBitmapString(ofToString(mask.getNumParticlesRU()), 300, 40);
	ofDrawBitmapString(ofToString(mask.getNumParticlesRD()), 300, 50);

	for(int i = 0; i < mask.getNumParticlesLU(); i ++){
	     ofDrawBitmapString(ofToString(mask.getPosLU(i).x), 300, 70 + (i * 10));
	     ofDrawBitmapString(ofToString(mask.getPosLU(i).y), 350, 70 + (i * 10));
	}
*/
        //GUI
    if( !mHideGUI ){
        gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::exit()
{

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 't'){
        enableCreateTriangle = true;
    }
    else if(key == 'm'){
        enableMoveParticles  = true;
    }
    else if(key == 'n'){
        enableNewParticle = true;
    }
    else if(key == 'g'){
        mHideGUI = !mHideGUI;
    }else if(key == '2'){
        gui.loadFromFile("settings.xml");
    }else if( key == 'y'){
      enableTargetParticle = true;
    }else if(key == 'l'){
        enableAddPartMaskLU = true;
    }else if(key == 'L'){
        enableAddPartMaskLD = true;
    }else if(key == 'r'){
        enableAddPartMaskRU = true;
    }else if(key == 'R'){
        enableAddPartMaskRD = true;
    }else if(key == '1'){
        mDrawMask = !mDrawMask;
    }else if(key == 'f'){
        enableViewFoto = !enableViewFoto;
    }else if(key == '0'){
	mFinishMask = !mFinishMask;
    }else if(key == '6'){
        enabledVideo = !enabledVideo;
 	player.play(0);
    }else if(key == '7'){
        enabledVideo = !enabledVideo;
        player.play(1);
    }else if(key == '8'){
        enabledVideo = !enabledVideo;
        player.play(2);
    }else if(key == '9'){
        enabledVideo = !enabledVideo;
        player.play(3);
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 't'){
        enableCreateTriangle = false;
    }
    else if(key == 'm'){
        enableMoveParticles = false;
    }
    else if(key == 'n'){
        enableNewParticle = false;
    }else if( key == 'y'){
      enableTargetParticle = true;
    }else if(key == 'l'){
      enableAddPartMaskLU = false;
    }else if(key == 'r'){
      enableAddPartMaskRU = false;
    }else if(key == 'L'){
      enableAddPartMaskLD = false;
    }else if(key == 'R'){
      enableAddPartMaskRD = false;
    }

    if(key == 'j'){
      //  loadJSON();
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    if(enableMoveParticles){
        if(mTempParticleId != -1){
           mTriangleManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));
           mTriangleManager->updateTargetPositions();
           mTriangleManager->renderMesh();
        }
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    if(enableCreateTriangle){
        Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
        //found something
        if(particle != NULL){
            //mParticleManager->updateParticleColor(particle->getParticleId(), ofColor(0, 150, 175));
            particle->setColor( ofColor(0, 150, 175));
            std::cout<<particle->getParticleId()<<std::endl;

            if(triangleCounter == 0)
                mtempTriA = particle->getParticleId();

            if(triangleCounter == 1){
                mtempTriB = particle->getParticleId();
            }

            if(triangleCounter == 2){
                mtempTriC = particle->getParticleId();

                Triangle * tri = new Triangle();
                tri->setParticleA( mTriangleManager->getParticle(mtempTriA) );
                tri->setParticleB( mTriangleManager->getParticle(mtempTriB) );
                tri->setParticleC( mTriangleManager->getParticle(mtempTriC) );
                mTriangleManager->addTriangle(tri);
                mTriangleManager->renderMesh();
                mTriangleManager->generateTriangles();
            }

            triangleCounter++;
            if(triangleCounter >=3 )
                triangleCounter = 0;
        }
    }
    else if(enableMoveParticles){
        Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
        //found something
        if(particle != NULL){
            mTempParticleId = particle->getParticleId();
          //  std::cout<<"m pressed: "<<mTempParticleId<<" "<<particle->getTargetId()<<std::endl;
            mTriangleManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));
            mTriangleManager->updateTargetPositions();
            mTriangleManager->renderMesh();
        }else{
            mTempParticleId = -1;
        }
    }
    else if(enableNewParticle){
        Particle * particle = new Particle();
        particle->setPosition(ofVec3f(x, y, 0));
        mTriangleManager->addParticle(particle);
        mTriangleManager->updateTargetPositions();
        mTriangleManager->generateTriangles();
        mTriangleManager->renderMesh();
    }else if(enableTargetParticle){
        Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
        if(particle != NULL){

          if(mTargetCounter == 0){
            mParticleTargetIdA = particle->getParticleId();
          }

          if(mTargetCounter == 1){
            mParticleTargetIdB = particle->getParticleId();
            std::cout<<"created target: "<<mParticleTargetIdA<<" - "<<mParticleTargetIdB<<std::endl;
            mTriangleManager->updateTargetId(mParticleTargetIdA, mParticleTargetIdB);

            //update target position
            mTriangleManager->updateTargetPos(mParticleTargetIdA, particle->getPosition());
          }

          mTargetCounter++;
          if(mTargetCounter >= 2)
            mTargetCounter = 0;

        }
    }else if(enableAddPartMaskLU){
      Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
      particle->setColor( ofColor(255, 0, 0));
      if(particle != NULL){
        mask.addParticleLU(ofVec3f(particle->getX(), particle->getY(), 0));
      }
    }else if(enableAddPartMaskLD){
      Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
      particle->setColor( ofColor(255, 0, 0));
      if(particle != NULL){
        mask.addParticleLD(ofVec3f(particle->getX(), particle->getY(), 0));
      }
    }else if(enableAddPartMaskRU){
      Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
    	particle->setColor( ofColor(255, 0, 0));
	     if(particle != NULL){
	        mask.addParticleRU(ofVec3f(particle->getX(), particle->getY(), 0));
        }
    }else if(enableAddPartMaskRD){
      Particle * particle = mTriangleManager->getNearestParticle(ofVec3f(x, y, 0));
        particle->setColor( ofColor(255, 0, 0));
             if(particle != NULL){
                mask.addParticleRD(ofVec3f(particle->getX(), particle->getY(), 0));
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    if(enableMoveParticles){
        if(mTempParticleId != -1){
           mTriangleManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));
           mTriangleManager->updateTargetPositions();
           mTriangleManager->renderMesh();
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::setVideo(int i){
	enableLineDelay = false;
        enableFacetas = false;
        enableStartDelay = false;
        enableLineDelay = false;

    if(i >= 0 && i < 4){
	enabledVideo = true;
	mDebugMesh = false;
	mDrawMesh = false;
        mWireFrameMesh = false;
        mFinishMask = true;
	mDrawMask = true; 
    }
    switch(i){
    case 0  :
       player.play(0);
       break; 
    case 1 :
       player.play(1);
       break;
    case 2 :
       player.play(2);
       break;
    case 3 :
       player.play(3);
       break;
    }
}

//--------------------------------------------------------------
void ofApp::setMood(int i){
    if(i == 8){
 	enabledVideo = false;
    	enableLineDelay = false;
    	enableFacetas = false;
        enableStartDelay = true;
	setWhiteWire = true;
	clearMesh();
        loadJSON(setWhiteWire);
	enabledVideo = false;
        mDebugMesh = false;
        mDrawMesh = false;
        mWireFrameMesh = true;
        mFinishMask = true;
        mDrawMask = true;
	startDelay = 0;
    }

    if(i == 7){
        enableLineDelay = false;
        enableFacetas = false;
        enableStartDelay = false;
        enableLineDelay = true;
        setWhiteWire = true;
        clearMesh();
        loadJSON(setWhiteWire);
        enabledVideo = false;
        mDebugMesh = false;
        mDrawMesh = false;
        mWireFrameMesh = false;
        mFinishMask = true;
        mDrawMask = false;
	numTriangles = mTriangleManager->getNumberOfTriangles();
	for(int i = 0; i < numTriangles; i++){
	    randomLine.push_back(i);
	}
	for(int i = 0; i < 3; i ++){
	    lineDelay[i] = 0;
	}
	std::random_shuffle(randomLine.begin(), randomLine.end());
        rando = rand() % 8 + 24;
    }

    if(i == 6){
	enabledVideo = false;
        enableLineDelay = false;
        enableStartDelay = false;
        setWhiteWire = true;
        clearMesh();
        loadJSON(setWhiteWire);
        enabledVideo = false;
        mDebugMesh = false;
        mDrawMesh = true;
        mWireFrameMesh = false;
        mFinishMask = true;
        mDrawMask = false;
	enableFacetas = true;
        numTriangles = mTriangleManager->getNumberOfTriangles();
	if(man.triangulos.size() == 0){
	    for(int i = 0; i < numTriangles; i ++){
	        man.addTriangulo(	mTriangleManager->getTriangle(i)->getPositionA(),
		   		    	mTriangleManager->getTriangle(i)->getPositionB(),
					mTriangleManager->getTriangle(i)->getPositionC());
	    }
	    man.setup();
	}
	man.begin();
    }
}

//--------------------------------------------------------------
void ofApp::drawStartDelay(){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0, 0, 0, 255 - startDelay);
    ofRect(0, 0, 1024, 768);
    ofPopStyle();
    startDelay ++;
    if(startDelay >= 255){
        startDelay = 0;
        enableStartDelay = false;
    }
}

//--------------------------------------------------------------
void ofApp::drawLineDelay(){
ofPushStyle();
ofSetLineWidth(0.5);
    for(int j = 0; j < 1/*NUM_RAND*/; j ++){
        for(int i = 0; i < ((j+1) * rando); i++){
	    ofVec3f posA = mTriangleManager->getTriangle(randomLine[i])->getPositionA();
	    ofVec3f posB = mTriangleManager->getTriangle(randomLine[i])->getPositionB();
	    ofVec3f posC = mTriangleManager->getTriangle(randomLine[i])->getPositionC();
	    
	    ofSetColor(200, 220, 255);     
	    ofLine(posA.x, posA.y, posA.x + ((posB.x - posA.x) * lineStep[j] * ofMap(lineDelay[0], 0, 300, j*20, 300 - j*20, true)), posA.y + ((posB.y - posA.y) * lineStep[j] * 		    ofMap(lineDelay[0], 0, 300, j*20, 300 - j*20, true)));
	    ofLine(posB.x, posB.y, posB.x + ((posC.x - posB.x) * lineStep[j] * ofMap(lineDelay[1], 0, 300, j*20, 300 - j*20, true)), posB.y + ((posC.y - posB.y) * lineStep[j] * 		    ofMap(lineDelay[1], 0, 300, j*20, 300 - j*20, true)));
	    ofLine(posC.x, posC.y, posC.x + ((posA.x - posC.x) * lineStep[j] * ofMap(lineDelay[2], 0, 300, j*20, 300 - j*20, true)), posC.y + ((posA.y - posC.y) * lineStep[j] * 		    ofMap(lineDelay[2], 0, 300, j*20, 300 - j*20, true)));	    
        }
    }
    if(lineGoesUp && lineDelay[0] < 300){
	lineDelay[0] = lineDelay[0] + 1;	
    }
    if(lineGoesUp && lineDelay[0] == 300 && lineDelay[1] < 300){
	lineDelay[1] ++;
    }
    if(lineGoesUp && lineDelay[1] == 300 && lineDelay[2] < 300){
	lineDelay[2] ++;
    }
    if(lineGoesUp && lineDelay[2] >= 300){
        lineGoesUp = false;
    }
    if(!lineGoesUp && lineDelay[2] > 0){
	lineDelay[2] --;
    }
    if(!lineGoesUp && lineDelay[2] == 0 && lineDelay[1] > 0){
	lineDelay[1] --;
    }
    if(!lineGoesUp && lineDelay[1] == 0 && lineDelay[0] > 0){
	lineDelay[0] --;
    }
    if(!lineGoesUp && lineDelay[0] == 0){
	lineGoesUp = true;
	std::random_shuffle(randomLine.begin(), randomLine.end());
        rando = rand() % 8 + 24;
    }
ofDrawBitmapString(ofToString(numTriangles), 500, 100);
ofDrawBitmapString(ofToString(lineDelay), 500, 110);
ofDrawBitmapString(ofToString(lineStep), 500, 120);
ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFacetas(){
	man.draw();
	//ofDrawBitmapString(ofToString(numTriangles), 800, 20);
	ofDrawBitmapString(ofToString(man.triangulos.size()), 800, 30);
}

