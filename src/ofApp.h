#pragma once

#include "ofMain.h"
#include "visualization/Maze.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void widthMazeChanged(int &width);
		void heightMazeChanged(int &height);
		void generateMazeButtonClick();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		Maze maze_;

		ofxPanel mazeUiPanel_;
		ofxIntSlider widthMaze_;
		ofxIntSlider heightMaze_;
		ofxButton generateMazeButton_;
};
