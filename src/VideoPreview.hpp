//
//  VideoPreview.hpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#ifndef VideoPreview_hpp
#define VideoPreview_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"


class VideoPreview{
public:
    VideoPreview(){};
    
    void Setup(ofRectangle bounds, float gui_x, float gui_y)
    {
        _previewPlayer.load("GreenPointSunset.mov");
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
        _videoPlayerBounds = bounds;
    }
    
    void SetFile(string fileName)
    {
        _previewPlayer.load(fileName);
    }
    
    std::string GetFile()
    {
        return _previewPlayer.getMoviePath();
    }
    
    void Update()
    {
        //_previewPlayer.
        //_previewPlayer.
        _previewPlayer.update();
        if(_isPlaying)
        {
            //_percentageComplete.set(_previewPlayer.getPosition());
        }
    }
    
    void Draw()
    {
        _gui.draw();
        _previewPlayer.draw(_videoPlayerBounds);
    }
    
    float GetVideoDuration()
    {
        return _previewPlayer.getDuration();
    }
        
    void SetCurrentPrecentage(float & position)
    {
        PauseVideo();
        //_previewPlayer.setPosition(position);
        int setFrameNumber = (int) (position * (float) _previewPlayer.getTotalNumFrames());
            
        _previewPlayer.setFrame(setFrameNumber);
    }
    
    void KeyboardNavigate(int key)
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
    
    void TogglePlay()
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
    
    void ForwardOneFrame()
    {
        PauseVideo();
        _previewPlayer.nextFrame();
    }
    
    void BackOneFrame()
    {
        PauseVideo();
        _previewPlayer.previousFrame();
    }
                   
private:
    //CutToolsGUI _cutToolsGUIParams;
    bool _frameByframe = false;
    ofVideoPlayer _previewPlayer;
    ofRectangle _videoPlayerBounds;
    bool _isPlaying = false;
    
    ofxGuiGroup _gui;
    ofxButton _pausePlayToggle;
    ofxButton _forwardFrame;
    ofxButton _backFrame;
    ofParameter<float> _percentageComplete;

    
    void PauseVideo()
    {
        _isPlaying = false;
        _previewPlayer.setPaused(true);
        _pausePlayToggle.setName("Play");
    }
    
    void PlayVideo()
    {
        _previewPlayer.play();
        _pausePlayToggle.setName("Pause");
        _isPlaying = true;
    }
};
#endif /* VideoPreview_hpp */
