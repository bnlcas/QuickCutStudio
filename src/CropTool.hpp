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
    
    void Setup(ofRectangle videoPlayerRect, float gui_x, float gui_y, CutToolsGUI * cutParameters);
     
    void DrawCropPreview();
    
    void CheckClick(int x, int y);
    
    void StartClick(int x, int y);
    
    void DragClick(int x, int y);
    
    ofRectangle GetCropBox();
    
    void SetVideoSize(ofRectangle videoPlayerRect);
    
private:
    CutToolsGUI * _cutParameters;
    
    bool _isClicked = false;
    ofRectangle _videoPreviewBounds;
    
    int _initial_x;
    int _initial_y;
    
    ofRectangle _cropBox;
    
    ofShader _cropShader;
    
    bool IsInbounds(int x, int y);
    
    void ConstrainCropBox(int x, int y);
    
    void InitializeCropBox(int x, int y);
    
    void FadeCropRegion();
};
#endif /* CropTool_hpp */
