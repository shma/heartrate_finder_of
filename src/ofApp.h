#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxExif.h"
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
				

    vector <float> volHistory;
    
    
    vector <float> taken;
    map <std::string, std::string> p;
    
    
    ofxJSONElement rates;
    ofxJSONElement places;
    
    ofImage image;
    
    ofDirectory dir;
    
    EXIFInfo exif;
    
    // GUIのパラメーター
    ofxPanel gui;
    
    // 
    ofxIntSlider rate;
    ofxIntSlider acceleration;
    ofxIntSlider second;
    ofxToggle rateToggle;
    
    
//    ofxFloatSlider rate;
    ofxVec2Slider position;
};
