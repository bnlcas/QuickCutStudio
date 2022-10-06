//
//  CutToolsGUI.cpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#include "CutToolsGUI.hpp"

void CutToolsGUI::Setup(float x, float y, VideoPreview * videoPreview)
{
    _gui.setup();
    _gui.add(_startTime.set("Clip Start Time", 0, 0, 100));
    _gui.add(_endTime.set("Clip End Time", 0, 0, 100));
    _gui.add(_outWidth.set("Out Width", 320, 960, 640));
    _gui.add(_outHeight.set("Out Height", 320, 960, 640));
    _gui.setPosition(x,y);
    
    _startTime.addListener(this, &CutToolsGUI::SetClipTime);
    _endTime.addListener(this, &CutToolsGUI::SetClipTime);

    _videoPreview = videoPreview;
}

void CutToolsGUI::DrawGUI()
{
    _gui.draw();
}

float CutToolsGUI::GetStartTime()
{
    return _startTime.get();
}

float CutToolsGUI::GetEndTime()
{
    return _endTime.get();
}

void CutToolsGUI::SetClipTime(float & time)
{
    //_videoPreview->PauseVideo();
    float duration = _videoPreview->GetVideoDuration();
    //_previewPlayer.setPosition(position);
    float percentage = (time / duration);
    percentage = (percentage > 1.0f) ? 1.0f : percentage;
    _videoPreview->SetCurrentPrecentage( percentage );
}

