//
//  CropTool.cpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#include "CropTool.hpp"
#include <cmath>

void CropTool::Setup(ofRectangle * videoPlayerRect, float gui_x, float gui_y, CutToolsGUI * cutParameters)
{
    _videoPreviewBounds = videoPlayerRect;
    ResetCropBox();
    _cutParameters = cutParameters;
    _cropShader.load("shaders/crop.vert", "shaders/crop.frag");
}

void CropTool::ResetCropBox()
{
    _cropBox = ofRectangle(_videoPreviewBounds->x, _videoPreviewBounds->y, _videoPreviewBounds->width, _videoPreviewBounds->height);
}
 
void CropTool::DrawCropPreview()
{
    if(_cutParameters->IsCropped())
    {
        FadeCropRegion();
        ofNoFill();
        ofSetColor(255, 255,255, 255);
        ofDrawRectangle(_cropBox);
    }
}

void CropTool::CheckClick(int x, int y)
{
    
}

void CropTool::StartClick(int x, int y)
{
    if(_cutParameters->IsCropped() && IsInbounds(x, y))
    {
        InitializeCropBox(x,y);
    }
}

void CropTool::DragClick(int x, int y)
{
    if(_cutParameters->IsCropped())
    {
        CropTool::ConstrainCropBox(x,y);
    }
}

ofRectangle CropTool::GetCropBox()
{
    return _cropBox;
}

void CropTool::SetVideoSize(ofRectangle * videoPlayerRect)
{
    _videoPreviewBounds = videoPlayerRect;
}


bool CropTool::IsInbounds(int x, int y)
{
    return _videoPreviewBounds->inside(x,y);
}

void CropTool::ConstrainCropBox(int x, int y)
{
    x = (x < _videoPreviewBounds->getLeft()) ? _videoPreviewBounds->getLeft() : x;
    x = (x > _videoPreviewBounds->getRight()) ? _videoPreviewBounds->getRight() : x;

    y = (y < _videoPreviewBounds->getTop()) ? _videoPreviewBounds->getTop() : y;
    y = (y > _videoPreviewBounds->getBottom()) ? _videoPreviewBounds->getBottom() : y;
    
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

void CropTool::FadeCropRegion()
{
    _cropShader.begin();
    
    _cropShader.setUniform1f("left", _videoPreviewBounds->getLeft());
    _cropShader.setUniform1f("right", _videoPreviewBounds->getRight());
    _cropShader.setUniform1f("top", (float)ofGetHeight() - _videoPreviewBounds->getTop());
    _cropShader.setUniform1f("bottom", (float)ofGetHeight() - _videoPreviewBounds->getBottom());
    
    _cropShader.setUniform1f("cropLeft", _cropBox.getLeft());
    _cropShader.setUniform1f("cropRight", _cropBox.getRight());
    _cropShader.setUniform1f("cropTop", (float)ofGetHeight() - _cropBox.getTop());
    _cropShader.setUniform1f("cropBottom", (float)ofGetHeight() - _cropBox.getBottom());

    ofSetColor(200, 200, 200, 200);
    ofFill();
    ofDrawRectangle(ofRectangle(0,0,(float)ofGetWidth(), (float)ofGetHeight()));
    _cropShader.end();
}
