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
    std::string out_dir = ofFilePath::getAbsolutePath("Clips");
    std::string filenameOut = ofFilePath::getBaseName(originalFile) + "_" + to_string(_clipCount) + "." + ofFilePath::getFileExt(originalFile);

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
        //_cropTool->SetVideoSize(_videoPreview->GetVideoRect());
        ofLogNotice() << path;
    }
}

string ClipProcessor::FormatFFMPEGCommand(string fIn, string fOut, Interval clipInterval, AspectSize clipSize){
    string command = "ffmpeg -y -i ";
    command += fIn;
    float duration = clipInterval.endTime - clipInterval.startTime;
    command += " -ss " + to_string(clipInterval.startTime);
    command += " -t " + to_string(duration);
    
    
    command += " -vf \"";
    if(_cutParameters->GetPlaybackSpeed() > 1)
    {
        string playBackcommand = "setpts=PTS/" + to_string(_cutParameters->GetPlaybackSpeed()) +  ",";
        command += playBackcommand;
    }
    if(_cutParameters->IsCropped())
    {
        ofRectangle crop = ofRectangle(0.0f,0.0f, clipSize.width, clipSize.height);
        int x0 = _cropTool->GetCropBox().getLeft();
        int y0 =_cropTool->GetCropBox().getTop();
        int w = _cropTool->GetCropBox().width;
        int h = _cropTool->GetCropBox().height;
        
        string crop_bbox = "crop=" + to_string(w) + ":" + to_string(h) + ":" + to_string(x0) + ":" + to_string(y0) + ",";
        command += crop_bbox;
    }

    string aspect = "scale=" + to_string(clipSize.width) + ":" + to_string(clipSize.height) + "\"";
    command += aspect;
    
    command += " " + fOut;
    return command;
};
