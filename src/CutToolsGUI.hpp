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

class CutToolsGUI
{
public:
    CutToolsGUI(){};
    
    void Setup(float x, float y)
    {
        _gui.setup();
        _gui.add(_startTime.set("Clip Start Time", 0, 0, 100));
        _gui.add(_endTime.set("Clip End Time", 0, 0, 100));
        _gui.add(_outWidth.set("Out Width", 320, 960, 640));
        _gui.add(_outHeight.set("Out Height", 320, 960, 640));
        _gui.setPosition(x,y);
    }
    
    void DrawGUI()
    {
        _gui.draw();
    }
    
    
    
private:
    
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

    
    ofxButton _toggleCropTool;
};

#endif /* CutToolsGUI_hpp */
