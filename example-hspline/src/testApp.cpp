#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp(){

}

//--------------------------------------------------------------
void testApp::setup(){

	vector<ofPoint> pts;
	int n = (int) ofRandom(10,64);
	for(int i=0; i<n; i++){
		pts.push_back(	ofPoint( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(-1000) ));
	}
					  
	hspline.setup(&pts, 0.005, 0.5); // setup with pts, stride, alpha
					  	

}

//--------------------------------------------------------------
void testApp::update(){
	
	// alpha controls the tension of the tangent to the spline
	hspline.alpha = ofMap(mouseY, 0, ofGetHeight(), -1, 2 );
	
	// update receives a multiplier for the splines stride
	hspline.update( ofMap(mouseX, 0, ofGetWidth(), -1, 1) );
	
}


//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	ofBackground(200);
	
	ofSetColor(255,0,0,200);
	hspline.drawPath();

	ofSetColor(255,128,0,200);
	hspline.drawTrails();

	ofSetColor(0,0,255,200);
	hspline.draw();
		
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	setup();
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

