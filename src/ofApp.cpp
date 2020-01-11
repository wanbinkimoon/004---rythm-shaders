#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(60);
  
  int sampleRate = 44100;
  int bufferSize = 512;
  int outChannels = 0;
  int inChannels = 2;

  // setup the sound stream
  soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize, 3);

  //setup ofxAudioAnalyzer with the SAME PARAMETERS
  audioAnalyzer.setup(sampleRate, bufferSize, inChannels);
  shader.load("shader_2/shader");
  shader_box.load("shader_box/shader");
  shader_1.load("shader_1/shader");
}

//--------------------------------------------------------------
void ofApp::update(){
//  smooth = ofClamp(ofGetMouseX() / (float)ofGetWidth(), 0.0, 1.0);
  smooth = .8;
  //get the analysis values
//  rms_l = audioAnalyzer.getValue(RMS, 0, smooth);
//  rms_r = audioAnalyzer.getValue(RMS, 1, smooth);
  melBands = audioAnalyzer.getValues(MEL_BANDS, 0, smooth);
}

//--------------------------------------------------------------
void ofApp::draw(){
  float sound_v = audioAnalyzer.getValue(RMS, 0, smooth);
  shader.begin();
  shader.setUniform1f("u_time", ofGetElapsedTimef());
  shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  shader.setUniform1f("u_sound", sound_v);
  ofFill();
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  shader.end();
    
  int side = 200;
  int maxZ = 600;
  ofNoFill(); ofSetColor(255);
  ofDrawRectangle(
                  ofGetWidth() * .5 - side + side * .1 + 1,
                  ofGetHeight() * .5 - side + side * .1 + 1,
                  side * 2 - side * .2 - 2,
                  side * 2 - side * .2 - 2);
  
  
  shader_box.begin();
  ofFill();
  ofDrawBox(ofGetWidth() * .5 - side  * .5 - side * .1, ofGetHeight() * .5 - side * .5 - side * .1, ofMap(melBands[1], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[1], DB_MIN, DB_MAX, -maxZ, maxZ));
  ofDrawBox(ofGetWidth() * .5 + side  * .5 + side * .1, ofGetHeight() * .5 - side * .5 - side * .1, ofMap(melBands[2], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[2], DB_MIN, DB_MAX, -maxZ, maxZ));
  ofDrawBox(ofGetWidth() * .5 - side  * .5 - side * .1, ofGetHeight() * .5 + side * .5 + side * .1, ofMap(melBands[4], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[4], DB_MIN, DB_MAX, -maxZ, maxZ));
  ofDrawBox(ofGetWidth() * .5 + side  * .5 + side * .1, ofGetHeight() * .5 + side * .5 + side * .1, ofMap(melBands[6], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[6], DB_MIN, DB_MAX, -maxZ, maxZ));
  shader_box.end();
  
  shader_1.begin();
  ofNoFill(); ofSetColor(255);
  ofDrawBox(ofGetWidth() * .5 - side  * .5 - side * .1, ofGetHeight() * .5 - side * .5 - side * .1, ofMap(melBands[1], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[1], DB_MIN, DB_MAX, -maxZ, maxZ));
  ofDrawBox(ofGetWidth() * .5 + side  * .5 + side * .1, ofGetHeight() * .5 - side * .5 - side * .1, ofMap(melBands[2], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[2], DB_MIN, DB_MAX, -maxZ, maxZ));
  ofDrawBox(ofGetWidth() * .5 - side  * .5 - side * .1, ofGetHeight() * .5 + side * .5 + side * .1, ofMap(melBands[4], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[4], DB_MIN, DB_MAX, -maxZ, maxZ));
  ofDrawBox(ofGetWidth() * .5 + side  * .5 + side * .1, ofGetHeight() * .5 + side * .5 + side * .1, ofMap(melBands[6], DB_MIN, DB_MAX, -maxZ, maxZ) * .5, side, side, side * 2 + ofMap(melBands[6], DB_MIN, DB_MAX, -maxZ, maxZ));
  shader_1.end();
}
//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &inBuffer){
  //ANALYZE SOUNDBUFFER:
  audioAnalyzer.analyze(inBuffer);
}

//--------------------------------------------------------------
void ofApp::exit(){
  ofSoundStreamStop();
  audioAnalyzer.exit();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
  
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
  
}
