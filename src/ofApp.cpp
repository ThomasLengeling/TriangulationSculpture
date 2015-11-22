#include "ofApp.h"

using namespace tri;

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetVerticalSync(true);

  ofSetFrameRate(30);

  ofSetLogLevel(OF_LOG_VERBOSE);

  ofEnableAntiAliasing();

  //ofEnableSmoothing();

  ofEnableAlphaBlending();

  ofEnableBlendMode(OF_BLENDMODE_ADD);

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

  loadJSON();

  mTriangleManager->generateTriangles();
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
    gui.add(mWireFrameMesh.setup("WireFrame Mesh", true));
    gui.add(mWireFrameWidth.setup("Line Width", 3, 1, 6));
    gui.add(mDrawMesh.setup("Draw Mesh", true));
    gui.add(mDebugMesh.setup("Debug Mesh", false));
    gui.add(mButtonXMLSave.setup("Save Console Values"));
    gui.add(mButtonOSC.setup("Setup OSC"));
    gui.add(mButtonSaveJSON.setup("Save Mesh"));
    gui.add(mButtonResetMesh.setup("Reset Mesh"));

    mHideGUI = true;

    gui.loadFromFile("settings.xml");


}

//--------------------------------------------------------------
void ofApp::clearMesh(){
    mTriangleManager->cleanMesh();
    mTriangleManager->renderMesh();
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
	  sender.setup(host, mPortSlider);
    }catch(std::exception & e){
        std::cout<<e.what()<<std::endl;
    }
}

void ofApp::loadJSON(){

    std::string file = "mesh.json";
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
        Particle * tmpParticles = new Particle();
        tmpParticles->setTargetId(ptid);
        tmpParticles->setPosition(ofVec3f(px, py, 0));
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

    mTriangleManager->renderMesh();
    mTriangleManager->updateColorMesh();
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
}

//--------------------------------------------------------------
void ofApp::draw(){

   ofBackground(ofColor(0));

    if(mDrawMesh){
      mTriangleManager->drawMesh();
    }

    if(mWireFrameMesh){
      ofSetLineWidth(int(mWireFrameWidth));
      mTriangleManager->drawWireFrameMesh();
    }

    if(mDebugMesh)
      mTriangleManager->drawPoints();

    if( !mHideGUI ){
		gui.draw();
	}
}

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
    }

    if(key == 'l'){
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

          if(mTargetCounter == 0)
            mParticleTargetIdA = particle->getParticleId();

          if(mTargetCounter == 1){
            mParticleTargetIdB = particle->getParticleId();
            std::cout<<"created target: "<<mParticleTargetIdA<<" "<<mParticleTargetIdB<<std::endl;
            mTriangleManager->updateTargetId(mParticleTargetIdA, mParticleTargetIdB);

            //update target position
            mTriangleManager->updateTargetPos(mParticleTargetIdA, particle->getPosition());
          }

          mTargetCounter++;
          if(mTargetCounter >= 2)
            mTargetCounter = 0;

        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    if(enableMoveParticles){
        if(mTempParticleId != -1){
           mTriangleManager->updateParticlePos(mTempParticleId, ofVec3f(x, y, 0));
           mTriangleManager->renderMesh();
           mTriangleManager->updateTargetPositions();
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
