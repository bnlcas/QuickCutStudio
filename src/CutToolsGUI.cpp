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
    _gui.add(_outWidth.set("Out Width", 320, 0, 960));
    _gui.add(_isPortrait.set("Is Portrait", true));
    _gui.add(_crop.set("Crop Video", false));
    
    _gui.setPosition(x,y);
    
    _startTime.addListener(this, &CutToolsGUI::SetClipTime);
    _endTime.addListener(this, &CutToolsGUI::SetClipTime);
    _isPortrait.addListener(this, &CutToolsGUI::SetApsectRatio);

    _videoPreview = videoPreview;
    ConfigureCutSettings();
}

void CutToolsGUI::ConfigureCutSettings()
{
    float duration = _videoPreview->GetVideoDuration();
    float width = _videoPreview->GetVideoWidth();
    _startTime.set("Clip Start Time", 0, 0, duration);
    _endTime.set("Clip End Time", duration, 0, duration);
    _outWidth.set("Output Width", width, 0, width);
    _crop.set("Crop Video", false);

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

bool CutToolsGUI::IsPortait()
{
    return _isPortrait;
}

bool CutToolsGUI::IsCropped()
{
    return _crop.get();
}

void CutToolsGUI::SetApsectRatio(bool & isPortrait)
{
    _isPortrait = isPortrait;
}

float CutToolsGUI::GetAspectRatio()
{
    if(_isPortrait)
    {
        return 0.5625;
    }
    else
    {
        return 1.7777777777777777;
    }
}

ofVec2f CutToolsGUI::GetOutputSize()
{
    float w = _outWidth.get();
    float aspectRatio = 0.5625;// 9:16
    float h = _isPortrait.get() ? w * aspectRatio : w / aspectRatio;
    return ofVec2f(w, h);
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

