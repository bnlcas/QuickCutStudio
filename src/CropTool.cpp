//
//  CropTool.cpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#include "CropTool.hpp"
#include <cmath>

void CropTool::Setup(ofRectangle videoPlayerRect, float gui_x, float gui_y, CutToolsGUI * cutParameters)
{
    _videoPreviewBounds = videoPlayerRect;
    _cropBox = videoPlayerRect;
    _cutParameters = cutParameters;
}
 
void CropTool::DrawCropPreview()
{
    ofNoFill();
    ofSetColor(255, 255,255, 255);
    ofDrawRectangle(_cropBox);
}

void CropTool::CheckClick(int x, int y)
{
    
}

void CropTool::StartClick(int x, int y)
{
    InitializeCropBox(x,y);
}

void CropTool::DragClick(int x, int y)
{
    CropTool::ConstrainCropBox(x,y);
}

ofRectangle CropTool::GetCropBox()
{
    return _cropBox;
}

bool CropTool::IsInbounds(int x, int y)
{
    return _videoPreviewBounds.inside(x,y);
}

void CropTool::ConstrainCropBox(int x, int y)
{
    x = (x < _videoPreviewBounds.getLeft()) ? _videoPreviewBounds.getLeft() : x;
    x = (x > _videoPreviewBounds.getRight()) ? _videoPreviewBounds.getRight() : x;

    y = (y < _videoPreviewBounds.getTop()) ? _videoPreviewBounds.getTop() : y;
    y = (y > _videoPreviewBounds.getBottom()) ? _videoPreviewBounds.getBottom() : y;
    
    int w = x - _initial_x;
    int h = y - _initial_y;
    
    if(abs(w) > abs(h * _cutParameters->GetAspectRatio()))
    {
        h = (int) ((float) w / _cutParameters->GetAspectRatio());
    }
    else
    {
        w =(int) ((float) h * _cutParameters->GetAspectRatio());
    }
       
    _cropBox.setWidth(w);
    _cropBox.setHeight(h);
}

void CropTool::InitializeCropBox(int x, int y)
{
    _initial_x = x;
    _initial_y = y;
    _cropBox.setX(x);
    _cropBox.setY(y);
    _cropBox.setWidth(0);
    _cropBox.setHeight(0);
}
