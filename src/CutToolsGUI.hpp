//
//  CutToolsGUI.hpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#ifndef CutToolsGUI_hpp
#define CutToolsGUI_hpp

#include <stdio.h>
#include "ofxGui.h"
#include "VideoPreview.hpp"

class CutToolsGUI
{
public:
    CutToolsGUI(){};
    
    void Setup(float x, float y, VideoPreview * videoPreview);
    
    void ConfigureCutSettings();
    
    void DrawGUI();
    
    float GetStartTime();
    
    float GetEndTime();
    
    bool IsPortait();
    
    bool IsCropped();
    
    void SetApsectRatio(bool & isPortrait);
    
    float GetAspectRatio();
    
    ofVec2f GetOutputSize();

    
private:
    VideoPreview * _videoPreview;
    //ofxGuiGroup
    //ofxPanel
    ofxGuiGroup _gui;
    ofxButton _cutSection;
    ofParameter<float> _startTime;
    ofParameter<float> _endTime;
    
    ofParameter<int> _outWidth;
    ofParameter<int> _outHeight;
    
    ofParameter<bool> _is916;
    ofParameter<bool> _isPortrait;
    
    ofParameter<bool> _crop;
    
    void SetClipTime(float & time);
};

#endif /* CutToolsGUI_hpp */
