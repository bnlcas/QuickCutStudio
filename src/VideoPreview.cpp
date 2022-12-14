//
//  VideoPreview.cpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#include "VideoPreview.hpp"


void VideoPreview::Setup(ofRectangle * bounds, float gui_x, float gui_y)
{
    _videoPlayerBounds = bounds;
    SetFile("test.mp4");
    _previewPlayer.setLoopState(OF_LOOP_NORMAL);
            
    _pausePlayToggle.addListener(this, &VideoPreview::TogglePlay);
    _forwardFrame.addListener(this, &VideoPreview::ForwardOneFrame);
    _backFrame.addListener(this, &VideoPreview::BackOneFrame);
    
    _percentageComplete.addListener(this, &VideoPreview::SetCurrentPrecentage);
    _gui.setup();
    _gui.add(_percentageComplete.set("Percentage", 0, 0, 1));
    
    _gui.add(_pausePlayToggle.setup("Play"));
    _gui.add(_forwardFrame.setup("Next Frame"));
    _gui.add(_backFrame.setup("Prior Frame"));
    _gui.setPosition(gui_x, gui_y);
}

void VideoPreview::SetFile(string fileName)
{
    _previewPlayer.load(fileName);
    float newWidth = _videoPlayerBounds->height * (_previewPlayer.getWidth() / _previewPlayer.getHeight());
    
    _videoPlayerBounds->width = newWidth;
}

std::string VideoPreview::GetFile()
{
    return _previewPlayer.getMoviePath();
}

void VideoPreview::Update()
{
    _previewPlayer.update();
    if(_isPlaying)
    {
        ofLogNotice() << "cf: " << _previewPlayer.getCurrentFrame() << "duration f: " << (_playbackEndTime / _previewPlayer.getDuration());
        if(_previewPlayer.getCurrentFrame() > (int)((float)_previewPlayer.getTotalNumFrames() * (_playbackEndTime / _previewPlayer.getDuration()))){
            PauseVideo();
        }
    }
}

void VideoPreview::Draw()
{
    _gui.draw();
    
    _previewPlayer.draw(_videoPlayerBounds->x, _videoPlayerBounds->y, _videoPlayerBounds->width, _videoPlayerBounds->height);
}

float VideoPreview::GetVideoDuration()
{
    return _previewPlayer.getDuration();
}

float VideoPreview::GetVideoWidth()
{
    return _previewPlayer.getWidth();
}

void VideoPreview::SetStartTime(float x)
{
    _playbackStartTime = x;
}

void VideoPreview::SetEndTime(float x)
{
    _playbackEndTime = x;
}
               
ofRectangle VideoPreview::GetVideoRect()
{
    return ofRectangle(_videoPlayerBounds->x, _videoPlayerBounds->y, _videoPlayerBounds->width, _videoPlayerBounds->height) ;
}

void VideoPreview::SetCurrentPrecentage(float & position)
{
    PauseVideo();
    int setFrameNumber = (int) (position * (float) _previewPlayer.getTotalNumFrames());
        
    _previewPlayer.setFrame(setFrameNumber);
}

void VideoPreview::KeyboardNavigate(int key)
{
    switch(key){
        case 'f':
            _frameByframe = !_frameByframe;
            _previewPlayer.setPaused(_frameByframe);
        break;
        case OF_KEY_LEFT:
            _previewPlayer.previousFrame();
        break;
        case OF_KEY_RIGHT:
            _previewPlayer.nextFrame();
        break;
        case '0':
            _previewPlayer.firstFrame();
        break;
    }
}

void VideoPreview::TogglePlay()
{
    if(_isPlaying)
    {
        PauseVideo();
    }
    else
    {
        PlayVideo();
    }
    ofLogNotice() << _isPlaying;
}

void VideoPreview::ForwardOneFrame()
{
    PauseVideo();
    _previewPlayer.nextFrame();
}

void VideoPreview::BackOneFrame()
{
    PauseVideo();
    _previewPlayer.previousFrame();
}

void VideoPreview::PauseVideo()
{
    _isPlaying = false;
    _previewPlayer.setPaused(true);
    _pausePlayToggle.setName("Play");
}

void VideoPreview::PlayVideo()
{
    int startFrame = (int) (_playbackStartTime  * (float) _previewPlayer.getTotalNumFrames() / _previewPlayer.getDuration());
    _previewPlayer.setFrame(startFrame);
    _previewPlayer.play();
    _pausePlayToggle.setName("Pause");
    _isPlaying = true;
}
