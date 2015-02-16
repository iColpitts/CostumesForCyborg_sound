#pragma once

#include "ofMain.h"
#include "ofxOSC.h"

// listen on port 12345
#define PORT 41234
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void windowResized(int w, int h);
		void gotMessage(ofMessage msg);
    
        // OSC reciever
        ofTrueTypeFont font;
        ofxOscReceiver receiver;
    
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
    
        // Simple AudioOut Example
        void audioOut(float * input, int bufferSize, int nChannels);
        
        
        ofSoundStream soundStream;
    
        int		sampleRate;
        float 	volume;
        float   scale;
    
        vector <float> audio;
        
        //------------------- for the simple sine wave synthesis
        float 	targetFrequency;
        float 	phase;
        float 	phaseAdder;
        float 	phaseAdderTarget;

		
};
