#include "VideoManager.h"

//--------------------------------------------------------------
void VideoManager::setup(){

	ofVideoPlayer player1;
	ofVideoPlayer player2;
	ofVideoPlayer player3;
	ofVideoPlayer player4;

	player1.loadMovie("agua.ogv");
	player2.loadMovie("nubes.ogv");
	player3.loadMovie("musgo.ogv");
	player4.loadMovie("sol.ogv");

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	for(int i = 0; i < 4; i ++){
		players[i].setLoopState(OF_LOOP_PALINDROME);
		isPlaying.push_back(false);
	}
}

//--------------------------------------------------------------
void VideoManager::update(){
    for(int i = 0; i < players.size(); i ++){
	if(isPlaying[i]){
	    players[i].update();
	}
    }
}
//--------------------------------------------------------------
void VideoManager::draw(){
    ofPushStyle();
    ofSetColor(255, 255, 255, 100);
    for(int i = 0; i < players.size(); i ++){
        if(isPlaying[i]){
            players[i].draw(0, 0, 1024, 768);
        }
    }	
    ofPopStyle();
}

//--------------------------------------------------------------
void VideoManager::stop(){
    for(int i = 0; i < players.size(); i ++){
        if(isPlaying[i]){
            players[i].stop();
	    isPlaying[i] = false;
        }
    }
}

//--------------------------------------------------------------
void VideoManager::play(int i){
    if(!isPlaying[i]){
	stop();
    }
    players[i].play();
    isPlaying[i] = true;   
} 
