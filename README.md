# Quick Cut Studio
Minimal desktop video editor using Openframeworks and FFMPEG to provide a basic GUI for making quick video cuts.

## Setup
1.) Install FFMPEG
`brew install ffmpeg`

2.) Setup/Install OpenF≈rameworks
2.a) Add the following modules:
* ofxGUI

3.) Note that this project requires ffmpeg to run. FFMPEG's path must be specfied in the app. If you run 
this on a mac and installed ffmpeg via homebrew, it should be `/opt/homebrew/bin` and the build should work 
for you. Otherwise you will need to find where ffmpeg is installed on your path and tweak line 53 or 
`ClipProcessor.cpp` to be `string pathCommand = "export PATH=$PATH:/YOUR/PATH/TO/FFMPEG; ";`


## WIP
This project is a work in progress.

## Use
Currently this supports only the most basic cuts.
The latest build is 
((here)[https://drive.google.com/file/d/1AnnnJeH1PXhWaJAcr5EAsonN2gsLVRo4/view?usp=sharing]).
