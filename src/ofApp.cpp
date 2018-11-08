#include "ofApp.h"
#include "MazeGenerator.h"

//--------------------------------------------------------------
void ofApp::setup(){
	maze_.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	maze_.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::azure, ofColor::orange);
	maze_.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	maze_.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	maze_.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	maze_.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	maze_.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	maze_.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	maze_.mouseScrolled(x, y, scrollX, scrollY);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	maze_.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
