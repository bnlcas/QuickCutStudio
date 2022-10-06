//
//  ClipProcessor.cpp
//  QuickCutStudio
//
//  Created by Benjamin Lucas on 10/1/22.
//

#include "ClipProcessor.hpp"

void ClipProcessor::Setup(float x, float y, VideoPreview * preview, CutToolsGUI * cutParameters)
{
    _uploadClip.addListener(this, &ClipProcessor::UploadClip);
    _processClip.addListener(this, &ClipProcessor::CutClip);
    _gui.setup();
    _gui.add(_uploadClip.setup("Upload"));
    _gui.add(_processClip.setup("Cut Clip"));
    _gui.setPosition(x,y);
    
    _cutParameters = cutParameters;
    _videoPreview = preview;
    
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
    std::string out_dir = ofFilePath::getAbsolutePath("Clips");
    std::string filenameOut = ofFilePath::getBaseName(originalFile) + "_" + to_string(_clipCount) + "." + ofFilePath::getFileExt(originalFile);
    
    ofLogNotice() << originalFile;
    ofLogNotice() << filenameOut;

    float clipStartTime = _cutParameters->GetStartTime();
    float clipEndTime = _cutParameters->GetEndTime();
    Interval clipInterval { clipStartTime, clipEndTime };
            
    ofVec2f outSize = _cutParameters->GetOutputSize();
    int outWidth = (int) outSize.x;
    int outHeight = (int) outSize.y;
    AspectSize clipSize  { outWidth, outHeight };
    
    std::string outCommand = FormatFFMPEGCommand(originalFile, out_dir+"/"+filenameOut, clipInterval, clipSize);
    
    //ofLogNotice() << outCommand;
    
    string ffmpegPathCommand = "export PATH=\"/opt/homebrew/bin/ffmpeg\"";
    string fullCommand = ffmpegPathCommand + "; " + outCommand;
    system(fullCommand.c_str());
    
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
        ofLogNotice() << path;
    }
}

string ClipProcessor::FormatFFMPEGCommand(string fIn, string fOut, Interval clipInterval, AspectSize clipSize){
    string command = "ffmpeg -i ";
    command += fIn;
    float duration = clipInterval.endTime - clipInterval.startTime;
    command += " -ss " + to_string(clipInterval.startTime);
    command += " -t " + to_string(duration);
    
    command += " -vf \"";
    if(_cutParameters->IsCropped())
    {
        ofRectangle crop = ofRectangle(0.0f,0.0f, clipSize.width, clipSize.height);
        
        string crop_bbox = "crop=" + to_string(crop.width) + ":" + to_string(crop.height) + ":" + to_string(crop.x) + ":" + to_string(crop.height) + ",";
        command += crop_bbox;
    }
    string aspect = "size=" + to_string(clipSize.width) + ":" + to_string(clipSize.height);
    
    command += aspect +  to_string('\"');
    command += " " + fOut;
    return command;
};
