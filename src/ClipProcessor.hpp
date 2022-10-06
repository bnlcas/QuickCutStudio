//
//  ClipProcessor.hpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#ifndef ClipProcessor_hpp
#define ClipProcessor_hpp

#include <stdio.h>
#include <stdlib.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "VideoPreview.hpp"
#include "CutToolsGUI.hpp"

using namespace std;

struct AspectSize {
    int width;
    int height;
};

struct BoundingBox
{
    int x;
    int y;
    int w;
    int h;
};

struct Interval
{
    float startTime;
    float endTime;
};

class ClipProcessor : public ofThread{
public:
    ClipProcessor(){};
    
    void Setup(float x, float y, VideoPreview * preview, CutToolsGUI * cutParameters);
    
    void Draw();
    
    void CutClip();
    
    bool IsProcessing();
    
private:
    ofxGuiGroup _gui;
    ofxButton _uploadClip;
    ofxButton _processClip;
    
    VideoPreview * _videoPreview;
    CutToolsGUI * _cutParameters;

    bool _isProcessing = false;
    int _clipCount = 1;
    
    void UploadClip();
    
    string FormatFFMPEGCommand(string fIn, string fOut, Interval clipInterval, AspectSize clipSize);
};


#endif /* ClipProcessor_hpp */
