#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Quick Cut Studio");
    
    float WINDOW_WIDTH = 1024.0;
    float WINDOW_HEIGHT = 768.0;
    float videoW = WINDOW_WIDTH/2;
    float videoH = 2 * WINDOW_HEIGHT / 3;
    float videoX = 50;//(WINDOW_WIDTH - videoW) / 3;
    float videoY = 50;//WINDOW_HEIGHT / 6;
    _videoPreviewRegion = ofRectangle(videoX, videoY, videoW, videoH);
    
    float gui_y = videoY + videoH + 25;
    _videoPreview.Setup(& _videoPreviewRegion, videoX,  gui_y);
    _cutToolsGui.Setup(videoX+250.0f, gui_y, &_videoPreview);
    _cropTool.Setup(& _videoPreviewRegion, videoX + 750.0f, gui_y, &_cutToolsGui);
    _clipProcessor.Setup(videoX + 500.0f, gui_y, &_videoPreview, &_cutToolsGui, & _cropTool);
}

//--------------------------------------------------------------
void ofApp::update(){
    _videoPreview.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    _cutToolsGui.DrawGUI();
    _videoPreview.Draw();
    _cropTool.DrawCropPreview();
    _clipProcessor.Draw();
}

void ofApp::ProcessClip()
{
    //Need to Add in some details about the size and stuff...
    _clipProcessor.CutClip();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _videoPreview.KeyboardNavigate(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    _cropTool.DragClick(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //_videoPreview.CheckClick(x,y);
    _cropTool.StartClick(x,y);
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
