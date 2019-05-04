#include "ofApp.h"

//--------------------------------------------------------------
ofVboMesh createCircle(int res, float radius)
{
	ofVboMesh mesh;

	int nvert = res;
	float a = 360.0f / (float)nvert;
	double ca = cos(1. / nvert);
	double sa = sin(1. / nvert);
	ofVec3f p = ofVec3f(0, 1, 0) * radius;
	ofMatrix3x3 rot = ofMatrix3x3(ca, sa, 0, -sa, ca, 0, 0, 0, 1);

	for (int i = 0; i < nvert; ++i)
	{
		mesh.addVertex(p);
		p = p.rotate(a, ofVec3f(0, 0, 1));

		if (i > 1)
		{
			mesh.addIndex(0);
			mesh.addIndex(i - 1);
			mesh.addIndex(i);
		}
	}

	return mesh;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowPosition(550, 300);
	ofSetVerticalSync(false);
	ofBackground(0, 0, 0);

	this->debriPositions.resize(SpaceSimulation::SPACE_OBJECT_MAX);
	this->buffer.allocate();
	this->buffer.bind(GL_TEXTURE_BUFFER);
	this->buffer.setData(this->debriPositions, GL_STREAM_DRAW);
	this->textureBuffer.allocateAsBufferTexture(this->buffer ,GL_RG32F);

	this->debriShader.load("shaders\\debriVert.glsl", "shaders\\debriFrag.glsl");
	this->debriShader.begin();
	this->debriShader.setUniformTexture("debriPositions", this->textureBuffer, 0);
	this->debriShader.end();
	
	this->debriMesh = createCircle(5, 10);
	
	//camera.enableOrtho();
	camera.setPosition(glm::vec3(0, 0, -60));
	camera.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	camera.setNearClip(1);
	camera.setFarClip(ofGetWidth() * 120);

}

//--------------------------------------------------------------
void ofApp::update(){
	double deltaTime = ofGetLastFrameTime();
	if (deltaTime > ofApp::max_dt)
	{
		deltaTime = ofApp::max_dt;
	}

	//printf("deltaTime : %f \n" , (deltaTime));

	this->SpaceSimulation.Tick(deltaTime);
	int count = SpaceSimulation.MovingObjectCount;
	for (int i = 0; i < count; ++i)
	{
		auto spaceObject = SpaceSimulation.MovingSpaceObjects[i];
		debriPositions[i] = spaceObject.position;
	}

	buffer.updateData(0, debriPositions);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(20);

	camera.begin();
	//ofSetupScreenOrtho(this->windowSize.x, this->windowSize.y);
	
	int count = this->SpaceSimulation.MovingObjectCount;
	//ofTranslate(this->halfWindowSize);
	/*
	for (int i = 0; i < count; ++i)
	{
		ofDrawCircle(this->SpaceSimulation.MovingSpaceObjects[i].position, 5);
	}
	*/

	debriShader.begin();

	//debriShader.setUniformMatrix4f("WorldMatrix", ofGetCurrentMatrix(ofMatrixMode::OF_MATRIX_MODELVIEW) );
	ofSetColor(ofColor::white);
	debriMesh.draw(OF_MESH_FILL);

	//debriMesh.drawInstanced(OF_MESH_POINTS, count);
	debriShader.end();

	camera.end();

//	ofPopMatrix();
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
