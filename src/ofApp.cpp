#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    minDistance = 10;
    leftMouseButtonPressed = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (leftMouseButtonPressed) {
        ofPoint mousePos(ofGetMouseX(), ofGetMouseY());
        if (lastPoint.distance(mousePos) >= minDistance) {
            // a.distance(b) calculates the Euclidean distance between point a and b.  It's
            // the straight line distance between the points.
            currentPolyline.curveTo(mousePos);
            lastPoint = mousePos;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);  // White color for saved polylines
    for (int i=0; i<polylines.size(); i++) {

        ofPolyline polyline = polylines[i];
        polyline.draw();

        ofSetColor(255, 50);
        float tangentLength = 300;
        for (int p=0; p<500; p+=1) {
            ofVec3f point = polyline.getPointAtPercent(p/500.0);
            float floatIndex = polyline.getIndexAtPercent(p/500.0);
            ofVec3f tangent = polyline.getTangentAtIndexInterpolated(floatIndex) * tangentLength;
            ofDrawLine(point-tangent/2, point+tangent/2);
        }
//        ofSetColor(255,100,0);  // Orange color for active polyline
        currentPolyline.draw();
    }
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
    if (button == OF_MOUSE_BUTTON_LEFT) {
        leftMouseButtonPressed = true;
        currentPolyline.curveTo(x, y);  // Remember that x and y are the location of the mouse
        currentPolyline.curveTo(x, y);  // Necessary duplicate for first control point
        lastPoint.set(x, y);  // Set the x and y of a ofVec2f in a single line
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(button == OF_MOUSE_BUTTON_LEFT){
        leftMouseButtonPressed = false;
        currentPolyline.curveTo(x,y);// Necessary duplicate for last control point
        currentPolyline.simplify(0.75);
        polylines.push_back(currentPolyline);
        currentPolyline.clear();//Erase the vertices, allows us to start a new brush stroke
    }
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
