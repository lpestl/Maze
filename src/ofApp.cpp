#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Подписываемся на события элементов управления
	widthMaze_.addListener(this, &ofApp::widthMazeChanged);
	heightMaze_.addListener(this, &ofApp::heightMazeChanged);
	generateMazeButton_.addListener(this, &ofApp::generateMazeButtonClick);
	// Вызываем метод setup у панели
	mazeUiPanel_.setup();
	// И последовательно добавляем все элементы управления
	mazeUiPanel_.add(widthMaze_.setup("Width Maze", 3, 2, 100));
	mazeUiPanel_.add(heightMaze_.setup("Height Maze", 3, 2, 100));
	mazeUiPanel_.add(generateMazeButton_.setup("Generate Maze"));
}

//--------------------------------------------------------------
void ofApp::update(){
	maze_.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::azure, ofColor::orange);
	maze_.draw();
	mazeUiPanel_.draw();
}

void ofApp::exit()
{
	// Отписываемся от событий
	heightMaze_.removeListener(this, &ofApp::heightMazeChanged);
	widthMaze_.removeListener(this, &ofApp::widthMazeChanged);
	generateMazeButton_.removeListener(this, &ofApp::generateMazeButtonClick);
}

void ofApp::widthMazeChanged(int& width)
{
}

void ofApp::heightMazeChanged(int& height)
{
}

void ofApp::generateMazeButtonClick()
{
	maze_.setup(widthMaze_, heightMaze_);
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
