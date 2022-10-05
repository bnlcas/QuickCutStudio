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
#include "CutToolsGUI.hpp"


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
        
        _percentageComplete.addListener(this, &VideoPreview::SetPosition);
        _gui.setup();
        _gui.add(_percentageComplete.set("Percentage", 0, 0, 1));
        
        _gui.add(_pausePlayToggle.setup("Play"));
        _gui.add(_forwardFrame.setup("Next Frame"));
        _gui.add(_backFrame.setup("Prior Frame"));
        _gui.setPosition(gui_x, gui_y);
        _videoPlayerBounds = bounds;
    }
    
    void SetFile()
    {
        _previewPlayer.load("test.mp4");
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
    
    void SetPosition(float & position)
    {
        PauseVideo();
        //_previewPlayer.setPosition(position);
        int setFrameNumber = (int) (position * (float) _previewPlayer.getTotalNumFrames());
        
        /*int deltaFrames = setFrameNumber - _previewPlayer.getCurrentFrame();
        
        if(deltaFrames > 0)
        {
            for(int i = 0; i < deltaFrames; i++)
            {
                _previewPlayer.nextFrame();
            }
        }
        else
        {
            for(int i = 0; i < -deltaFrames; i++)
            {
                _previewPlayer.previousFrame();
            }
        }*/
        
            
        _previewPlayer.setFrame(setFrameNumber);
        
        //ofLogNotice() << frameNumber;
        //ofLogNotice() << _previewPlayer.getSpeed();
        //ofLogNotice() << _previewPlayer.getDuration();
        //_previewPlayer.setSpeed(1);
        //_previewPlayer.setPosition(0.5);
        //_previewPlayer.setPaused(true);
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
