#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    string rateFile = "2016_0628_rate.json";
    string placeFile = "2016_0623_place.json";
    
    bool rateSuccessful = rates.open(rateFile);
    bool placeSuccessful = places.open(placeFile);
    
    ofToggleFullscreen();
    
    if (rateSuccessful)
    {
//        ofLogNotice("ofApp::setup") << result.getRawString();
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(80);
    ofBackground(0, 0, 0);
    
    volHistory.assign(ofGetWidth(), 0.0);
    taken.assign(ofGetWidth(), 0.0);
    
    int photoCount = dir.listDir("img/0628");
    
    for (int i=0; i<photoCount; i++) {
        exif = getEXIF(dir.getPath(i));
        
        string aa = (exif.DateTimeOriginal);
        aa.erase(--aa.end());
        cout << aa << endl;
        p[aa] = dir.getPath(i);
    }
    
    // colorの初期値、最小値、最大値を設定
    ofColor initColor = ofColor(0, 127, 255, 255);
    ofColor minColor = ofColor(0,0,0,0);
    ofColor maxColor = ofColor(255,255,255,255);
    
    // positionの初期値、最小値、最大値を設定
    ofVec2f initPos = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    ofVec2f minPos = ofVec2f(0, 0);
    ofVec2f maxPos = ofVec2f(ofGetWidth(), ofGetHeight());

    graphHeight = 500;

    gui.setup();
    gui.setPosition(550, graphHeight + 250);
    gui.setSize(600, gui.getHeight());
    gui.setDefaultWidth(600);
    gui.add(rate.setup("rate", 0, 0, 120));
    gui.add(acceleration.setup("acceleration", -10, -10, 10));
    gui.add(second.setup("second", 1, 1, 60));

    accelerationNum = 0;

}


//--------------------------------------------------------------
void ofApp::update(){
    
    if (!stopFlag) {
        volHistory.push_back(rates[resultNum][1].asInt());
        resultNum++;
    
        if (rates.size() == resultNum) {
            resultNum = 0;
        }
        
        // 写真を発見したらロードして表示
        auto itr = p.find(rates[resultNum][0].asString());
        if( itr != p.end() ) {
            //設定されている場合の処理
            if (rates[resultNum][1].asInt() > rate && accelerationNum > acceleration) {
                image.clear();
                image.load(p[rates[resultNum][0].asString()]);
                photoTime = rates[resultNum][0].asString();
            }
        }
        
        if (resultNum > second) {
            accelerationNum = rates[resultNum][1].asInt() - rates[resultNum - second][1].asInt();
        }
        
    }
    
    if( volHistory.size() >= ofGetWidth() ){
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

    ofDrawBitmapString("Heart Rate Monitor", 20, 28);
    ofDrawBitmapString(rates[resultNum][0].asString() + " : " + rates[resultNum][1].asString(), 20, 56);
    
//    ofDrawRectangle(30, 10, ofGetWidth()-30, 400);
    
    //ofSetColor(255, 255, 214);
    ofFill();
//    ofDrawCircle(200, 200, scaledVol * 190.0f);
    
    //ofDrawLine(ofGetWidth() / 2, 10, ofGetWidth() / 2, graphHeight);
    
    bool photoed = false;
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, graphHeight);
        
            ofSetColor(255, 255, 255);
//        ofDrawLine(i, 400, i, 400 - volHistory[i] * 8 + 450);
        ofVertex(i, graphHeight - volHistory[i] * 8 + 550);
        if( i == volHistory.size() -1 ) ofVertex(i , graphHeight);
    }

    ofEndShape(false);
    ofPopMatrix();
    ofPopStyle();
    
    
    image.draw(150, graphHeight + 100,image.getWidth()/3,image.getHeight()/3);
    ofDrawBitmapString("Photo", 550, graphHeight + 110);
    ofDrawBitmapString("Time : " + photoTime, 550, graphHeight + 130);
    ofDrawBitmapString("Whether : cloudy", 550, graphHeight + 150);
    ofDrawBitmapString("Place : Ogaki", 550, graphHeight + 170);
    ofDrawBitmapString("Acceleration : " + ofToString(accelerationNum), 550, graphHeight + 190);
    
    ofDrawBitmapString("Change Parameter", 550, graphHeight + 220);
    
    // GUIを表示
    gui.draw();
    
    ofDrawBitmapString("History", 1200, graphHeight + 110);
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

