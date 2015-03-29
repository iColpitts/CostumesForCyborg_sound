#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    
    ofBackground(30, 30, 130);
    
    //Audio Setup
    int bufferSize		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 0.1f;
    
    audio.assign(bufferSize, 0.0);
    
    //soundStream.listDevices();
    
    //if you want to set the device id to be different than the default
    //soundStream.setDeviceID(1); 	//note some devices are input only and some are output only
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update(){

    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // unrecognized message: display on the bottom of the screen
        string msg_string;
        msg_string = m.getAddress();        //find address
        msg_string += ": ";
        for(int i = 0; i < m.getNumArgs(); i++){
            // get the argument type
            msg_string += m.getArgTypeName(i);
            msg_string += ":";
            // display the argument - make sure we get the right type
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                msg_string += ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                
                    msg_string += ofToString(m.getArgAsFloat(i));
                    scale = m.getArgAsFloat(i);
                  if ( m.getArgAsFloat(0) == 1){
                    //-----Audio Out example code
                    targetFrequency = m.getArgAsFloat(1) * 8;
                    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
                  }
                  if ( m.getArgAsFloat(0) == 2){
                    //-----Audio Out example code
                    targetFrequency = m.getArgAsFloat(1) * 3;
                    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
                  }
                
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                msg_string += m.getArgAsString(i);
            }
            else{
                msg_string += "unknown";
            }
        }
        // add to the list of strings to display
        msg_strings[current_msg_string] = msg_string;
        timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
        current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
        // clear the next line
        msg_strings[current_msg_string] = "";
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    string buf;
    buf = "listening for osc messages on port" + ofToString(PORT);
    ofDrawBitmapString(buf, 10, 20);
    
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    // sin (n) seems to have trouble when n is very large, so we
    // keep phase in the range of 0-TWO_PI like this:
    while (phase > TWO_PI){
        phase -= TWO_PI;
    }
    
    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    for (int i = 0; i < bufferSize; i++){
        phase += phaseAdder;
        float sample = sin(phase);
        audio[i] = output[i*nChannels    ] = sample * volume;
    }
    
//    phaseAdder2 = 0.95f * phaseAdder2 + 0.05f * phaseAdderTarget2;
//    for (int i = 0; i < bufferSize; i++){
//        phase2 += phaseAdder2;
//        float sample = sin(phase2);
//        audio[i] = output[i*nChannels    ] = sample * volume;
//    }
    
}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
