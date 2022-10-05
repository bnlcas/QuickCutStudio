//
//  CropTool.hpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#ifndef CropTool_hpp
#define CropTool_hpp

#include <stdio.h>
#include <cmath>
#include "ofMain.h"
#include "CutToolsGUI.hpp"

using namespace std;

class CropTool
{
public:
    CropTool(){};
    
    void Setup(ofRectangle videoPlayerRect, float gui_x, float gui_y)
    {
        _videoPreviewBounds = videoPlayerRect;
        _cropBox = videoPlayerRect;
        //_cutToolsGUIParams = cutToolParams;
        
    }
     
    void DrawCropPreview()
    {
        ofNoFill();
        ofSetColor(255, 255,255, 255);
        ofDrawRectangle(_cropBox);
    }
    
    
    void CheckClick(int x, int y)
    {
        
    }
    
    void StartClick(int x, int y)
    {
        InitializeCropBox(x,y);
        //ofLogNotice() << myRect;
    }
    
    void DragClick(int x, int y)
    {
        ConstrainCropBox(x,y);
    }
    
    ofRectangle GetCropBox()
    {
        return _cropBox;
    }
    
private:
    //CutToolsGUI _cutToolsGUIParams;
    
    bool _isClicked = false;
    ofRectangle _videoPreviewBounds;
    
    int _initial_x;
    int _initial_y;
    
    ofRectangle _cropBox;
    
    bool IsInbounds(int x, int y)
    {
        return _videoPreviewBounds.inside(x,y);
    }
    
    void ConstrainCropBox(int x, int y)
    {
        x = (x < _videoPreviewBounds.getLeft()) ? _videoPreviewBounds.getLeft() : x;
        x = (x > _videoPreviewBounds.getRight()) ? _videoPreviewBounds.getRight() : x;

        y = (y < _videoPreviewBounds.getTop()) ? _videoPreviewBounds.getTop() : y;
        y = (y > _videoPreviewBounds.getBottom()) ? _videoPreviewBounds.getBottom() : y;
        int w = x - _initial_x;
        int h =  y - _initial_y;
           
        _cropBox.setWidth(w);
        _cropBox.setHeight(h);
    }
    
    void InitializeCropBox(int x, int y)
    {
        _initial_x = x;
        _initial_y = y;
        _cropBox.setX(x);
        _cropBox.setY(y);
        _cropBox.setWidth(0);
        _cropBox.setHeight(0);
    }
    
};
#endif /* CropTool_hpp */
