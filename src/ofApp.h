#pragma once

#include "ofMain.h"
#include "ofVbo.h"
#include "ofGraphics.h"
#include "SpaceSimulator.h"
#include "glm/common.hpp"
#include "glm/mat2x2.hpp"

class ofApp : public ofBaseApp{

	private:
		double max_dt = .03f;
		glm::vec2 windowSize = glm::vec2(1024, 768);
		glm::vec2 halfWindowSize = windowSize / 2;

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

		SpaceSimulation::SpaceSimulator SpaceSimulation;

		ofTexture textureBuffer;
		ofBufferObject buffer;
		vector<ofVec2f> debriPositions;
		ofVboMesh debriMesh;
		ofShader debriShader;
		ofCamera camera;
};
