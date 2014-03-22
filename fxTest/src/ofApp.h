#pragma once

#include "ofMain.h"
/* #include "ofxGaussianBlur.h" */
#include "ofxBokeh.h"
/* #include "ofxBloom.h" */

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
        // Does not make a difference where it is called from, but is
        // called from update() in sandbox-example.
        void draw_plane_and_update_effect();

        int width = 640;
        int height = 480;
        ofxBokeh fx_effect;
        /* ofxBloom fx_effect; */
        /* ofxGaussianBlur fx_effect; */
        ofFbo render_buffer;
};
