//
//  ClipProcessor.hpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#ifndef ClipProcessor_hpp
#define ClipProcessor_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "VideoPreview.hpp"
#include "CutToolsGUI.hpp"

using namespace std;

struct AspectSize {
    int width;
    int height;
};

struct BoundingBox
{
    int x;
    int y;
    int w;
    int h;
};

struct Interval
{
    float startTime;
    float endTime;
};

class ClipProcessor{
public:
    ClipProcessor(){};
    
    void Setup(float x, float y, VideoPreview * preview, CutToolsGUI * cutParameters)
    {
        _uploadClip.addListener(this, &ClipProcessor::UploadClip);
        _processClip.addListener(this, &ClipProcessor::CutClip);
        _gui.setup();
        _gui.add(_uploadClip.setup("Upload"));
        _gui.add(_processClip.setup("Cut Clip"));
        _gui.setPosition(x,y);
        
        _cutParameters = cutParameters;
        _videoPreview = preview;
    }
    
    void Draw()
    {
        _gui.draw();
    }
    
    void CutClip()
    {
        _isProcessing = true;
        std::string originalFile = _videoPreview->GetFile();
        std::string out_dir = ofFilePath::getAbsolutePath("Clips");
        std::string filenameOut = ofFilePath::getBaseName(originalFile) + "_" + to_string(_clipCount) + "." + ofFilePath::getFileExt(originalFile);
        
        ofLogNotice() << originalFile;
        ofLogNotice() << filenameOut;

        float clipStartTime = _cutParameters->GetStartTime();
        float clipEndTime = _cutParameters->GetEndTime();
        Interval clipInterval { clipStartTime, clipEndTime };
                
        int outWidth = 640;
        int outHeight = 320;
        
        AspectSize clipSize  { outWidth, outHeight };
        
        int crop_X = 0;
        int crop_Y = 0;
        int crop_W = 640;
        int crop_H = 320;
        BoundingBox bbox { crop_X, crop_Y, crop_W, crop_H };
        
        std::string outCommand = FormatFFMPEGCommand(originalFile, out_dir+"/"+filenameOut, clipInterval, clipSize, bbox);
        
        ofLogNotice() << outCommand;
        ofSystem(outCommand);
        
        _clipCount += 1;
        _isProcessing = false;
    }
    
    bool IsProcessing()
    {
        return _isProcessing;
    }
    
private:
    ofxGuiGroup _gui;
    ofxButton _uploadClip;
    ofxButton _processClip;
    
    VideoPreview * _videoPreview;
    CutToolsGUI * _cutParameters;

    bool _isProcessing = false;
    int _clipCount = 1;
    
    void UploadClip(){
        ofFileDialogResult result = ofSystemLoadDialog("Load file");
        if(result.bSuccess) {
            string path = result.getPath();
            _videoPreview->SetFile(path);
            ofLogNotice() << path;
        }
    }

    string FormatFFMPEGCommand(string fIn, string fOut, Interval clipInterval, AspectSize clipSize, BoundingBox crop){
        string command = "ffmpeg -i ";
        command += fIn;
        float duration = clipInterval.endTime - clipInterval.startTime;
        command += " -ss " + to_string(clipInterval.startTime);
        command += " -t " + to_string(duration);
        
        /*
        string crop_bbox = "crop=" + to_string(crop.w) + ":" + to_string(crop.h) + ":" + to_string(crop.x) + ":" + to_string(crop.h);

        string aspect = "size=" + to_string(clipSize.width) + ":" + to_string(clipSize.height);
        
        command += " -vf "  + to_string('"') +  crop_bbox + "," + aspect +  to_string('"');
         */
        command += " " + fOut;
        return command;
    };
};


#endif /* ClipProcessor_hpp */
