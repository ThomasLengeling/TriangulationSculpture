//
//  Manager.hpp
//  triangulos
//
//  Created by DIEGO AMOZOO on 11/30/15.
//
//

#ifndef Manager_hpp
#define Manager_hpp

#include <stdio.h>
#include "Triangulo.hpp"
#define NUM 30
#define RANDOM 50
#endif /* Manager_hpp */

class Manager{
    
public:
    
    vector<Triangulo> triangulos;
    vector<int> disminuidos;
    vector<int> delays;
    vector<int> chek;
    
    void setup();
    void addTriangulo(ofVec3f, ofVec3f, ofVec3f);
    void draw();
    void begin();
    void update();
    void checkAll();
    
    int cont;
    
    
};
