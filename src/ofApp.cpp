#include "ofApp.h"

int resultNum;
bool stopFlag;

//--------------------------------------------------------------
void ofApp::setup(){
    
    string rateFile = "2016_0623_rate.json";
    string placeFile = "2016_0623_place.json";
    
    bool rateSuccessful = rates.open(rateFile);
    bool placeSuccessful = places.open(placeFile);
    
    
    if (rateSuccessful)
    {
//        ofLogNotice("ofApp::setup") << result.getRawString();
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(0, 0, 0);
    
    
    volHistory.assign(600, 0.0);
    
    int photoCount = dir.listDir("img");
    
    for (int i=0; i<photoCount; i++) {
        cout << dir.getPath(i) << endl;
        places[i][4] = dir.getPath(i);
    }
    
    
    image.load("img/IMG_3686.jpg");
}


//--------------------------------------------------------------
void ofApp::update(){
    
    if (!stopFlag) {
        volHistory.push_back(rates[resultNum][1].asInt());
        resultNum++;
    
        if (rates.size() == resultNum) {
            resultNum = 0;
        }
    
    
        for (int j = 0; j < places.size(); j++) {
            if (rates[resultNum][0] == places[j][0]) {
                image.clear();
                image.load(places[j][4].asString());
            
            }
        }
    }
    
    //lets record the volume into an array
//    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 600 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofNoFill();
    
    // draw the average volume:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Heart Rate Monitor", 4, 18);
    ofDrawBitmapString(rates[resultNum][0].asString() + " : " + rates[resultNum][1].asString(), 4, 36);
    
    ofDrawRectangle(0, 0, 600, 400);
    
    
    
    //ofSetColor(255, 255, 214);
    ofFill();
//    ofDrawCircle(200, 200, scaledVol * 190.0f);
    
    //lets draw the volume history as a graph
    
    
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, 400);
        
        ofVertex(i, 400 - volHistory[i] * 8 + 450);
        if( i == volHistory.size() -1 ) ofVertex(i, 400);
        
        
        
    }
    /**
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, 400);
        cout << ofToString(volHistory[i] * 70) << endl;
        
        ofVertex(i, 400 - volHistory[i] * 70);
        
        if( i == volHistory.size() -1 ) ofVertex(i, 400);
    }
     **/
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    ofDrawBitmapString("Photo", 620, 18);
    image.draw(620, 20,image.getWidth()/3,image.getHeight()/3);
    
    
    
}



//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if( key == 's' ){
        stopFlag = !stopFlag;
    }
    
    if( key == 'e' ){

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

