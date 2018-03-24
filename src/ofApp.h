#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxPanel gui;
    ofxSlider<int> brightness;
    float color;
    int red = 255;
    int green = 0;
    int blue = 255;
    int rateX = 3;
    string playPause = "pause";
    bool play = true;
    ofxToggle method;
    string algohsb = "algorithmic";
    float hue = 0.0;
    ofColor hsb;
    bool preview = false;
};
