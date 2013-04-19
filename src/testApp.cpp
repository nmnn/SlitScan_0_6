#include "testApp.h"

//set variables
int video_width;
int video_height;
int video_slice_x   = video_width/2;
int window_width    = 480;
int window_height   = video_height;
int draw_position_x = 0;
bool newFrame       = false;



//--------------------------------------------------------------
void testApp::setup(){
    //init Webcam Video
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(640,480);
    //Adjust VideoInput with Webcam settings
    //vidGrabber.videoSettings();

    //get video height and width
    window_width    = vidGrabber.getWidth();
    window_height   = vidGrabber.getHeight();

    texture.allocate(window_width, window_height, GL_RGB);
    texpixels = new unsigned char [window_width * window_height * 3];
}

//--------------------------------------------------------------
void testApp::update(){
    //Update webcam output
    vidGrabber.update();
    newFrame = vidGrabber.isInitialized();
    if(newFrame) {
        vidpixels = vidGrabber.getPixels();
        for (int y=0; y<window_height; y++) {
            unsigned char r, g, b;
            getPixel(video_slice_x, y, &r, &g, &b, video_width, vidpixels);
            setPixel(draw_position_x, y, r, g, b, window_width, texpixels);
        }
        texture.loadData(texpixels, window_width, window_height, GL_RGB);

        draw_position_x++;
        if (draw_position_x >= window_width) {
            draw_position_x = 0;
        }
        newFrame = false;
    }
}

//---------------------------------------------------------------
void testApp::setPixel(int horizontal, int vertical, unsigned char R, unsigned char G,
    unsigned char B, int w, unsigned char pixels[]){
    int thisPixel;
    thisPixel = 3*(w * vertical +horizontal);
    pixels[thisPixel]=R;
    pixels[thisPixel+1]=G;
    pixels[thisPixel+2]=B;
}

//--------------------------------------------------------------
void testApp::getPixel(int horizontal, int vertical, unsigned char* R, unsigned char* G,
    unsigned char* B, int w, unsigned char pixels[]){
    int thisPixel;
    thisPixel = 3*(w * vertical +horizontal);
    *R= pixels[thisPixel];
    *G= pixels[thisPixel+1];
    *B= pixels[thisPixel+2];
}

//--------------------------------------------------------------
void testApp::draw(){
    //Set background to black every frame, not really needed
    ofBackground(0, 0, 0);

    //Draw WebcamVideo, uncomment to show
    //vidGrabber.draw(0, 0);

    //draw texture slit
    texture.draw(0,0);

    //draw FrameRate
    ofDrawBitmapString( ofToString( ofGetFrameRate() ), 50, 50);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
