//
//  ClipProcessor.cpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#include "ClipProcessor.hpp"

void ClipProcessor::Setup(float x, float y, VideoPreview * preview, CutToolsGUI * cutParameters, CropTool * crop)
{
    _uploadClip.addListener(this, &ClipProcessor::UploadClip);
    _processClip.addListener(this, &ClipProcessor::CutClip);
    _gui.setup();
    _gui.add(_uploadClip.setup("Upload"));
    _gui.add(_processClip.setup("Cut Clip"));
    _gui.setPosition(x,y);
    
    _cutParameters = cutParameters;
    _videoPreview = preview;
    _cropTool = crop;
    
    startThread();
}

void ClipProcessor::Draw()
{
    _gui.draw();
}

void ClipProcessor::CutClip()
{
    _isProcessing = true;
    std::string originalFile = _videoPreview->GetFile();
    //std::string out_dir = ofFilePath::getAbsolutePath("Clips");
    std::string out_dir = ofFilePath::getEnclosingDirectory(originalFile);
    std::string filenameOut = ofFilePath::getBaseName(originalFile) + "_Clip_" + to_string(_clipCount) + "." + ofFilePath::getFileExt(originalFile);

    float clipStartTime = _cutParameters->GetStartTime();
    float clipEndTime = _cutParameters->GetEndTime();
    Interval clipInterval { clipStartTime, clipEndTime };
            
    ofVec2f outSize = _cutParameters->GetOutputSize();
    int outWidth = (int) outSize.x;
    int outHeight = (int) outSize.y;
    outWidth = 2 * (outWidth / 2);
    outHeight = 2 * (outHeight / 2);
    AspectSize clipSize  { outWidth, outHeight };
    
    std::string outCommand = FormatFFMPEGCommand(originalFile, out_dir+"/"+filenameOut, clipInterval, clipSize);
    
    //ofLogNotice() << outCommand;

    string pathCommand = "export PATH=$PATH:/opt/homebrew/bin;";
    //pathCommand += "; echo $PATH";
    pathCommand += outCommand;

    system(pathCommand.c_str());
    

    _clipCount += 1;
    _isProcessing = false;
}

bool ClipProcessor::IsProcessing()
{
    return _isProcessing;
}

void ClipProcessor::UploadClip(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
        string path = result.getPath();
        _videoPreview->SetFile(path);
        _cutParameters->ConfigureCutSettings();
        _cropTool->ResetCropBox();
        ofLogNotice() << path;
    }
}

string ClipProcessor::FormatFFMPEGCommand(string fIn, string fOut, Interval clipInterval, AspectSize clipSize){
    string command = "ffmpeg -y -v 0 -i ";
    command += fIn;
    float duration = clipInterval.endTime - clipInterval.startTime;
    command += " -ss " + to_string(clipInterval.startTime);
    command += " -t " + to_string(duration);
    
    string vfxCommand = " -vf \"";
    bool addVfx = false;
    if(_cutParameters->GetPlaybackSpeed() > 1)
    {
        string playBackcommand = "setpts=PTS/" + to_string(_cutParameters->GetPlaybackSpeed());
        vfxCommand += playBackcommand;
        addVfx = true;
    }
    if(_cutParameters->IsCropped())
    {
        if(addVfx)
        {
            vfxCommand += ",";
        }
        ofRectangle crop = ofRectangle(0.0f,0.0f, clipSize.width, clipSize.height);
        
        ofRectangle videoRect = _videoPreview->GetVideoRect();
        float scale =  _videoPreview->GetVideoWidth() / videoRect.width;
        int x0 = scale * (_cropTool->GetCropBox().getLeft() - videoRect.getLeft());
        int y0 = scale * (_cropTool->GetCropBox().getTop() - videoRect.getTop());
        int w = (int) (scale * _cropTool->GetCropBox().width);
        int h = (int) (scale * _cropTool->GetCropBox().height);
        w = 2 * (w / 2);
        h = 2 * (h / 2);
        
        //ofLogNotice() << "w: " << w << " vw: " << _videoPreview->GetVideoWidth() << " pw: " << videoRect.width;
        //ofLogNotice() << "scale X: " << scaleX << " y:" << scaleY;
        
        string crop_bbox = "crop=" + to_string(w) + ":" + to_string(h) + ":" + to_string(x0) + ":" + to_string(y0);
        vfxCommand += crop_bbox;
        addVfx = true;
    }
    bool scale = true;
    if(scale)
    {
        if(addVfx)
        {
            vfxCommand += ",";
        }
        string aspect = "scale=" + to_string(clipSize.width) + ":" + to_string(clipSize.height);
        vfxCommand += aspect;
        addVfx = true;
    }
    vfxCommand += "\"";
    
    if(addVfx)
    {
        command += vfxCommand;
    }
    command += " " + fOut;
    ofLogNotice() << command;
    return command;
};
