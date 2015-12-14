//
//  Manager.cpp
//  triangulos
//
//  Created by DIEGO AMOZOO on 11/30/15.
//
//

#include "Manager.hpp"
#include <algorithm>

//--------------------------------------------------------------
void Manager::addTriangulo(ofVec3f posa, ofVec3f posb, ofVec3f posc){
    Triangulo tri;
    tri.setup(posa, posb, posc);
    triangulos.push_back(tri);
}

//--------------------------------------------------------------
void Manager::draw(){
    for (int i = 0; i < triangulos.size(); i++) {
        triangulos[i].draw();
    }
}

//--------------------------------------------------------------
void Manager::setup(){
    for (int i = 0; i < NUM; i++) {
        int temp = rand() % 48;
        while (std::find(disminuidos.begin(), disminuidos.end(), temp) != disminuidos.end()) {
            temp = rand() % 48;
        }
        disminuidos.push_back(temp);
        temp = rand() % RANDOM;
        while (temp % 2 != 0) {
            temp = rand() % RANDOM;
        }
        delays.push_back(temp);
    }
    cont = 0;
}

//--------------------------------------------------------------
void Manager::begin(){
    bool done = false;
    for (int i = 0; i < disminuidos.size(); i++) {
        if (!triangulos[disminuidos[i]].paRriba && ! done) {
            triangulos[disminuidos[i]].paBajo = true;
            done = true;
        }
    }
    
}

//--------------------------------------------------------------
void Manager::update(){
    for (int i = 0; i < disminuidos.size(); i++) {
        triangulos[disminuidos[i]].update();
        if (triangulos[disminuidos[i]].replace) {
            int temp = rand() % 48;
            while (std::find(disminuidos.begin(), disminuidos.end(), temp) != disminuidos.end()) {
                temp = rand() % 48;
            }
            triangulos[disminuidos[i]].replace = false;
            triangulos[disminuidos[i]].paRriba = false;
            disminuidos[i] = temp;
            temp = rand() % RANDOM;
            while (temp % 2 != 0) {
                temp = rand() % RANDOM;
            }
            delays[i] = temp;
        }
        if (triangulos[disminuidos[i]].alpha == 300-delays[i] && !triangulos[disminuidos[i]].paRriba) {
            triangulos[disminuidos[(i+1)%disminuidos.size()]].paBajo = true;
        }
    }

}

//--------------------------------------------------------------
void Manager::checkAll(){
    bool restart = true;
    for (int i = 0; i < triangulos.size(); i++) {
        if (triangulos[i].alpha != 300) {
            restart = false;
            if (triangulos[i].alpha == 1 && !triangulos[i].paBajo && triangulos[i].paRriba) {
                restart = true;
            }
        }
        if (triangulos[i].paRriba && triangulos[i].paBajo) {
            triangulos[i].paRriba = false;
        }
    }
    if (restart) {
        cont ++;
        begin();
    }
}
