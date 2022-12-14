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
    
    void Setup(ofRectangle * bounds, float gui_x, float gui_y);
    
    void SetFile(string fileName);
    
    std::string GetFile();
    
    void Update();
    
    void Draw();
    
    float GetVideoDuration();
    
    float GetVideoWidth();
    
    ofRectangle GetVideoRect();
        
    void SetCurrentPrecentage(float & position);
    
    void KeyboardNavigate(int key);
    
    void TogglePlay();
    
    void ForwardOneFrame();
    
    void BackOneFrame();
    
    void SetStartTime(float x);
    
    void SetEndTime(float x);
                   
private:
    float _playbackStartTime;
    float _playbackEndTime;
    bool _frameByframe = false;
    ofVideoPlayer _previewPlayer;
    ofRectangle * _videoPlayerBounds;
    bool _isPlaying = false;
    
    ofxGuiGroup _gui;
    ofxButton _pausePlayToggle;
    ofxButton _forwardFrame;
    ofxButton _backFrame;
    ofParameter<float> _percentageComplete;
 
    void PauseVideo();
    
    void PlayVideo();
};
#endif /* VideoPreview_hpp */
