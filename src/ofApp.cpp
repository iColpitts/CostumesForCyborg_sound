#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // listen on the given port
    //cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    //current_msg_string = 0;
    
    //ofBackground(30, 30, 130);
    
    //Audio Setup
    int bufferSize		= 512;
    sampleRate 			= 44100;
    volume				= 0.3f;
    
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    
    rAudio.assign(bufferSize, 0.0);
    
    phase2 				= 0;
    phaseAdder2 		= 0.0f;
    phaseAdderTarget2 	= 0.0f;

    lAudio.assign(bufferSize, 0.0);
    
    //soundStream.listDevices();
    
    //if you want to set the device id to be different than the default
    //soundStream.setDeviceID(1); 	//note some devices are input only and some are output only
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    //VideoPlayback
    ofSetVerticalSync(true);
    frameByframe = false;
    
    // Uncomment this to show movies with alpha channels
    // fingerMovie.setPixelFormat(OF_PIXELS_RGBA);
    
    video.loadMovie("ThesisVid.mov");
    video.play();
    
    bleConnect = 0;
    
    ofSetFrameRate(60);
    
    //Terminal commands for beginning bean communication
    //cout << ofSystem( "cd " + bleScript );
    //cout << ofSystem( "pwd" );
    //cout << ofSystem( "dos /usr/local/bin/node /Users/Izzie1/of_v0.8.4_osx_release/apps/myApps/CostumesForCyborg_sound/NodeShit/bean-to-osc.js");
    

}

//--------------------------------------------------------------
void ofApp::update(){

    video.update();
    //if (volumeBool == true)
    //{
    //    phaseAdder = 0;
    //    phaseAdder2 = 0;
    //}
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        video.setVolume(0.0);
        //bool volumeBool = false;
        
        for(int i = 0; i < m.getNumArgs(); i++){
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    scale = m.getArgAsFloat(i);
                  if ( m.getArgAsFloat(0) == 1){
                    //-----Audio Out example code
                    targetFrequency = m.getArgAsFloat(1) * 8;
                    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
                  }
                  if ( m.getArgAsFloat(0) == 2){
                    //-----Audio Out example code
                    targetFrequency2 = m.getArgAsFloat(1) * 3;
                    phaseAdderTarget2 = (targetFrequency2 / (float) sampleRate) * TWO_PI;
                  }
                if ( m.getArgAsFloat(0) == 3){
                    video.setVolume(0.0);
                }
                if (m.getArgAsFloat(0) == 4){
                    video.setVolume(1.0);
                    //bool volumeBool = true;
                    
                    targetFrequency = 0;
                    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;;
                    
                    targetFrequency2 = 0;
                    phaseAdderTarget2 = (targetFrequency / (float) sampleRate) * TWO_PI;;
                }
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            }
        }
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    //Draw video
    ofSetHexColor(0xFFFFFF);
    
    video.draw(0,0);
    ofSetHexColor(0x000000);
    unsigned char * pixels = video.getPixels();
    
    //string buf;
    //buf = "listening for osc messages on port" + ofToString(PORT);
    //ofDrawBitmapString(buf, 10, 20);
    
    //for(int i = 0; i < NUM_MSG_STRINGS; i++){
    //    ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
    //}
    
    
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
        lAudio[i] = output[i*nChannels    ] = sample * volume;
    }
    
    phaseAdder2 = 0.95f * phaseAdder2 + 0.05f * phaseAdderTarget2;
    for (int i = 0; i < bufferSize; i++){
        phase2 += phaseAdder2;
        float sample = sin(phase2);
        rAudio[i] = output[i*nChannels  +1  ] = sample * volume;
    }
    
}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
