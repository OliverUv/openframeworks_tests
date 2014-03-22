#pragma once

#include "ofMain.h"
#include "ofxBokeh.h"
#include "ofxBloom.h"

class ofApp : public ofBaseApp{
    public:

        void setup();
        void update();
        void draw();

        // Inherited but unused.
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

    private:
        ofShader shader;
        ofPlanePrimitive plane;

        // To make it easier to draw to fbo in either update() or draw().
        void draw_to_fbo();

        int width = 1920;
        int height = 1200;
        ofxBokeh fx_effect;
        /* ofxBloom fx_effect; */
        ofFbo render_buffer;
};
