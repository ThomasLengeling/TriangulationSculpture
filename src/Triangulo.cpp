//
//  Triangulo.cpp
//  triangulos
//
//  Created by DIEGO AMOZOO on 11/30/15.
//
//

#include "Triangulo.hpp"


//--------------------------------------------------------------
void Triangulo::setup(ofVec3f posa, ofVec3f posb, ofVec3f posc){
    posA = posa;
    posB = posb;
    posC = posc;
    alpha = 300;
    paBajo = false;
    paRriba = false;
    replace = false;
}

//--------------------------------------------------------------
void Triangulo::draw(){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0, 0, 0, alpha);
    glBegin(GL_TRIANGLES);
 
	glVertex3f(posA.x, posA.y, 0);    // lower left vertex
	glVertex3f(posB.x, posB.y, 0);    // lower right vertex
	glVertex3f(posC.x, posC.y, 0);    // upper vertex
 
    glEnd();
    ofPopStyle();
}

//--------------------------------------------------------------
void Triangulo::disminuir(){
    if(alpha > 0){
        alpha = alpha - TIEMPO;
    }
    if (alpha == 0) {
        paBajo = false;
        paRriba = true;
    }
}

//--------------------------------------------------------------
void Triangulo::aumentar(){
    if (alpha < 300) {
        alpha = alpha + TIEMPO;
    }
    if (alpha == 300) {
        paRriba = false;
        replace = true;
    }
}


//--------------------------------------------------------------
void Triangulo::update(){
    if (paBajo && alpha > 0) {
        disminuir();
    }
    if (paRriba && alpha < 300) {
        aumentar();
    }
}
