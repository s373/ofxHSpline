#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp(){
	clear = true;
}

//--------------------------------------------------------------
void testApp::setup(){



}

//--------------------------------------------------------------
void testApp::update(){

	if(clear){
		vector<ofPoint> pts;
		int n = (int) ofRandom(3,20);
		float vol = 0.5e3;
		for(int i=0; i<n; i++){
			pts.push_back(	ofPoint( ofRandom(-vol,vol), ofRandom(-vol,vol), vol/(float)(i+1) ));
		}
		pts.push_back(pts[0]);//close

		hspline.setup(&pts, 0.005, 0.5); // setup with pts, stride, alpha
		clear = false;
	}

	// alpha controls the tension of the tangent to the spline
	hspline.alpha = ofMap(mouseY, 0, ofGetHeight(), -100, 100 );

	// update receives a multiplier for the splines stride
	// hspline.update( ofMap(mouseX, 0, ofGetWidth(), -10, 20) );
	hspline.stride = ofMap(mouseX, 0, ofGetWidth(), -0.1, 0.2);
	hspline.update( 1 );

}


//--------------------------------------------------------------
void testApp::draw(){

	ofEnableAlphaBlending();
	ofBackground(200);
	cam.begin();
	ofSetColor(255,0,0,200);
	hspline.drawPath();

	ofSetColor(255,128,0,200);
	hspline.drawTrails();

	ofSetColor(0,0,255,200);
	hspline.draw();
	cam.end();
	ofDrawBitmapString("æ: "+ofToString(hspline.alpha)+
	"\ns: " +ofToString(hspline.stride), 10, 10);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	clear = true;

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
