#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
//    set the gui here using ofxPanel grouping
    gui.setup();
    gui.add(brightness.setup("brightness", 225, 0, 255));
    gui.add(method.setup(true));
    gui.add(absoluteNumber.setup("absolute number", true));
}

//--------------------------------------------------------------
void ofApp::update(){
//    LOL idk why i declare color = rateX.. instead of just using rateX
    color = rateX;

    
    if (play) {
        
        //rgb algorithm:
// if 0 method replaced with the abs value at the end of rgb algorithm
//        if (red < 0) {
//            red = 0;
//        }
//        if (green < 0) {
//            green = 0;
//        }
//        if (blue < 0) {
//            blue = 0;
//        }
        if (red > 255) {
            red = 255;
        }
        if (green > 255) {
            green = 255;
        }
        if (blue > 255) {
            blue = 255;
        }
        if (red == 255 && green < 255) {
            green += color;
            blue -= color;
        }
        if (green == 255 && blue < 255) {
            blue += color;
            red -= color;
        }
        if (blue == 255 && red < 255) {
            red += color;
            green -= color;
        }
        
//This abs replace the if ( x < 0 ){ x = 0} at the top ^
        if (absoluteNumber) {
            red = abs(red);
            green = abs(green);
            blue = abs(blue);
        }
    
        
        //hue algorithm:
        hue++;
        if (hue > 255.0) {
            hue = 0.0;
        }
        hsb = ofColor::fromHsb(hue, 255, brightness);
    
    }
    
    method.setName("method: " + algohsb);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(20);
    if (method) {
        algohsb = "hsb";
        ofSetColor(red, green, blue); //method one (algorithmic)
    } else {
        algohsb = "algorithmic";
        ofSetColor(hsb); //method two (hsb)
    }
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    if (preview) {
        if (!method) {
            ofSetColor(red, green, blue); //preview (algorithmic)
        } else {
            ofSetColor(hsb); //preview (hsb)
        }
        ofDrawRectangle(ofGetWidth()-200, 0, 200, ofGetHeight());
        ofSetColor(0);
        ofSetLineWidth(10);
        ofDrawLine(ofGetWidth()-200, 0, ofGetWidth()-200, ofGetHeight());
        ofDrawBitmapStringHighlight(algohsb + "\npreview", ofGetWidth()-200, 12);
    }
    
    if (method) {
        ofSetColor(0, 255-brightness);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(0,255/2);
        ofDrawRectangle(35, ofGetHeight()-((12*7)+45), 110, -265);
        int rgb[4] = {0, red, green, blue};
        for (int i = 1; i <= 3; i++) {
            switch (i) {
                case 1:
                    ofSetColor(255, 0, 0);
                    break;
                case 2:
                    ofSetColor(0, 255, 0);
                    break;
                case 3:
                    ofSetColor(0, 0, 255);
                    break;
            }
            ofDrawRectangle(40*i, ofGetHeight()-((12*7)+50), 20, -rgb[i]);
        }
        ofSetColor(255);
        ofDrawBitmapStringHighlight("R: " + ofToString(red) + "\nG: " + ofToString(green) + "\nB: " + ofToString(blue) + "\n\nChange rate: " + ofToString(color) + "\n+ = increase rate\n- = decrease rate" , 20, ofGetHeight()-((12*7)+20));
    } else {
        ofSetCircleResolution(80);
        ofSetColor(0, 255/2);
        ofDrawCircle(120, ofGetHeight()-120, 100);
        ofSetColor(hsb);
        ofDrawCircle(120, ofGetHeight()-120, 50);
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(120, ofGetHeight()-120);
        ofPushMatrix();
        ofRotate(-120);
        for (int i = 0; i < 3; i++) {
            ofSetColor(ofColor::fromHsb(85*i, 255, 255));
            ofRotate(120);
            ofDrawCircle(0, -75, 20);
        }
        ofPopMatrix();
        ofRotate(360.0/255.0*hue);
        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(5);
        ofDrawCircle(0, -75, 20);
        ofPopStyle();
        ofPopMatrix();
    }
    ofSetColor(255);
    ofDrawBitmapStringHighlight("press space to " + playPause + "\nhold 'p' for preview", ofGetWidth()/2-10*11, ofGetHeight()-32);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '=':
            if (rateX < 85) {
                rateX += 1;
                while (255 % rateX != 0) {
                    rateX++;
                }
            }
            break;
        case '-':
            if (rateX > 1) {
                rateX -= 1;
                while (255 % rateX != 0) {
                    rateX--;
                }
            }
            break;
        case ' ':
            if (play) {
                playPause = "play";
                play = false;
            } else {
                playPause = "pause";
                play = true;
            }
            break;
        case 'p':
            preview = true;
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'p':
            preview = false;
            break;
    }

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::exit(){
    
}
