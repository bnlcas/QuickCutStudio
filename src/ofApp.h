#pragma once

#include "ofMain.h"
#include "CutToolsGUI.hpp"
#include "VideoPreview.hpp"
#include "ClipProcessor.hpp"
#include "CropTool.hpp"

class ofApp : public ofBaseApp{

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
    
    private:
        void ProcessClip();
    
        CutToolsGUI _cutToolsGui;
        VideoPreview _videoPreview;
        ClipProcessor _clipProcessor;
        CropTool _cropTool;
};
