#include "ofApp.h"

int resultNum;
bool stopFlag;

string photoTime = "";

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
            image.clear();
            image.load(p[rates[resultNum][0].asString()]);
        }
    }
    
    //lets record the volume into an array
//    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
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
    
    ofDrawRectangle(30, 10, ofGetWidth()-30, 400);
    
    //ofSetColor(255, 255, 214);
    ofFill();
//    ofDrawCircle(200, 200, scaledVol * 190.0f);
    
    //ofDrawLine(ofGetWidth() / 2, 10, ofGetWidth() / 2, 400);
    
    bool photoed = false;
    ofBeginShape();
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, 410);
        
            ofSetColor(255, 255, 255);
//        ofDrawLine(i, 400, i, 400 - volHistory[i] * 8 + 450);
        ofVertex(i, 410 - volHistory[i] * 8 + 550);
        if( i == volHistory.size() -1 ) ofVertex(i , 410);
    }

    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    
    image.draw(150, ofGetHeight() - image.getHeight()/3 - 100,image.getWidth()/3,image.getHeight()/3);
    ofDrawBitmapString("Photo", 550, 460);
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

