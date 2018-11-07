#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	std::cout << "UINT max = " << std::numeric_limits<unsigned>::max() << std::endl;
	std::cout << "ULONG max = " << std::numeric_limits<unsigned long long>::max() << std::endl;
	auto outputSize = static_cast<unsigned long long>(std::numeric_limits<unsigned>::max()) * 2 + 1;
	std::cout << "UINT * 2 + 1 = " << outputSize << std::endl;
	bool isMoreless = outputSize <= std::numeric_limits<unsigned long long>::max();
	std::cout << "UINT * 2 + 1 <= ULONG max ?  " << isMoreless << std::endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
