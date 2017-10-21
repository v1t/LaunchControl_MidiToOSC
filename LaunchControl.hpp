
//  LaunchControl.hpp
//  ofxMaximTest
//
//  Created by Vytautas Niedvaras on 21/10/2017.


#ifndef LaunchControl_hpp
#define LaunchControl_hpp

//#include "ofApp.h"
#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 12000
#define NUM_MSG_STRINGS 20

class LaunchControl{
    
    ofxOscReceiver receiver;
    vector<int> allValues;
    vector<int*> bindings;
    int setChannel;
    void updateBindings(int index);
    
    
public:
   
    LaunchControl();
    void update();
    void bind(int channelIndex, string type, int controllerNumber, int &variable);
};

#endif /* LaunchControl_hpp */

