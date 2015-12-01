//
//  Triangulo.hpp
//  triangulos
//
//  Created by DIEGO AMOZOO on 11/30/15.
//
//

#ifndef Triangulo_hpp
#define Triangulo_hpp

#include <stdio.h>
#include "ofMain.h"
#define TIEMPO 1

#endif /* Triangulo_hpp */

class Triangulo{
    
public:
    ofVec3f posA;
    ofVec3f posB;
    ofVec3f posC;
    int alpha;
    bool paBajo;
    bool paRriba;
    bool replace;
    
    void setup(ofVec3f, ofVec3f, ofVec3f);
    void draw();
    void disminuir();
    void aumentar();
    void update();
    
    

    
};
