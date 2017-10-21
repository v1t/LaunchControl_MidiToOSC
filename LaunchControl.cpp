//
//  LaunchControl.cpp
//  ofxMaximTest
//
//  Created by Vytautas Niedvaras on 21/10/2017.
//

#include "LaunchControl.hpp"

LaunchControl::LaunchControl(){
    receiver.setup(PORT);
    allValues = vector<int>(56);
    bindings = vector<int*>(56);

}

void LaunchControl::update(){
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);

        if(m.getAddress() == "/LaunchControl/Knob"){
            int channel = m.getArgAsInt(0);
            int objectIndex = m.getArgAsInt(1);
            int value = m.getArgAsInt(2);
            
            switch(channel) {
                case 2:
                    if(objectIndex > 20 && objectIndex< 29){
                        int index = objectIndex - 21;
                        allValues[index] = value;
                        updateBindings(index);
                    }
                    if(objectIndex > 40 &&  objectIndex< 49){
                        int index =objectIndex - 41 + 8;
                        allValues[objectIndex - 41 + 8] = value;
                        updateBindings(index);
                    }
                    if(objectIndex > 113 && objectIndex < 118){
                        int index =objectIndex - 90;
                        allValues[objectIndex - 90] = (value == 127) ? 1 : 0;
                        updateBindings(index);
                    }
                    break;
                case 14:
                    if(objectIndex > 20 && objectIndex< 29){
                        int index =objectIndex - 21 + 28;
                        allValues[objectIndex - 21 + 28] = value;
                        updateBindings(index);
                    }
                    if(objectIndex > 40 &&objectIndex< 49){
                        int index =objectIndex - 41 + 28 + 8;
                        allValues[objectIndex - 41 + 28 + 8] = value;
                        updateBindings(index);
                    }
                    if(objectIndex > 113 && objectIndex < 118){
                        int index =objectIndex - 90 + 28;
                        allValues[objectIndex - 90 + 28] = (value == 127) ? 1 : 0;
                        updateBindings(index);
                    }
                    break;
            }
        }
        if(m.getAddress() == "/LaunchControl/Button"){;
            int channel = m.getArgAsInt(0);
            int objectIndex = m.getArgAsInt(1);
            int value = m.getArgAsInt(2);
            
            switch(channel) {
                case 2:
                    if(objectIndex > 8 && objectIndex < 13){
                        int index = objectIndex + 7;
                        allValues[objectIndex + 7] = (value == 127) ? 1 : 0;
                        updateBindings(index);
                    }
                    if(objectIndex > 24 && objectIndex < 29){
                        int index = objectIndex - 5;
                        allValues[objectIndex - 5] = (value == 127) ? 1 : 0;
                        updateBindings(index);
                    }
                    break;
                case 14:
                    if(objectIndex > 8 && objectIndex < 13){
                        int index =objectIndex + 7 + 28;
                        allValues[objectIndex + 7 + 28] = (value == 127) ? 1 : 0;
                        updateBindings(index);
                    }
                    if(objectIndex > 24 && objectIndex < 29){
                        int index = objectIndex - 5 + 28;
                        allValues[objectIndex - 5 + 28] = (value == 127) ? 1 : 0;
                        updateBindings(index);
                    }
                    break;
            }
        }
    }
}

void LaunchControl::updateBindings(int index){
    if(bindings[index] != nullptr){
        *bindings[index] = allValues[index];
    }
}

void LaunchControl::bind(int channelIndex, string type, int controllerNumber, int &variable){
    
    if (channelIndex < 0 || channelIndex > 1) channelIndex = 0;
    if(type == "KNOB"){
        bindings[channelIndex*28 +controllerNumber] = &variable;
    }
    if(type == "BUTTON"){
        bindings[channelIndex*28 + 16 + controllerNumber] = &variable;
        cout<<channelIndex*28 + 16 + controllerNumber<<endl;
    }
}


