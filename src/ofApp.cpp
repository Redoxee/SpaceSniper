#include "ofApp.h"

//--------------------------------------------------------------
ofVboMesh createCircle()
{
	ofVboMesh mesh;

	int nvert = 8;
	float a = 1.0f / (float)nvert;
	double ca = cos(1. / nvert);
	double sa = sin(1. / nvert);
	ofVec3f p = ofVec3f(0, 1, 0) * .5;
	ofMatrix3x3 rot = ofMatrix3x3(ca, sa, 0, -sa, ca, 0, 0, 0, 1);
	/*
	mesh.addVertex(ofVec3f(-.5, -.5, 0));
	mesh.addVertex(ofVec3f(-.5, .5, 0));
	mesh.addVertex(ofVec3f( .5, .5, 0));
	mesh.addVertex(ofVec3f( .5, -.5, 0));

	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(2);
	mesh.addIndex(2);
	mesh.addIndex(3);
	mesh.addIndex(0);
	*/
	for (int i = 0; i < nvert; ++i)
	{
		mesh.addVertex(p);
		p = p.rotate(a, ofVec3f(0, 0, 1));

		cout << "point " << p << std::endl;
		mesh.addIndex(i);
	}
	mesh.addIndex(0);

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

	this->debriMesh = createCircle();
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
	//ofSetupScreenOrtho(this->windowSize.x, this->windowSize.y);
	//ofPushMatrix();
	
	int count = this->SpaceSimulation.MovingObjectCount;
	/*
	ofTranslate(this->halfWindowSize);
	for (int i = 0; i < count; ++i)
	{
		ofDrawCircle(this->SpaceSimulation.MovingSpaceObjects[i].position, 5);
	}
	*/


	debriShader.begin();
	debriMesh.draw(OF_MESH_WIREFRAME);

	//debriMesh.drawInstanced(OF_MESH_POINTS, count);
	debriShader.end();

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
