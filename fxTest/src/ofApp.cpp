#include "ofApp.h"
#include "ofFbo.h"

void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE); // Removing this does not make bokeh work.
    ofEnableAlphaBlending();

    // This was proposed as a solution on the forums for a texture/coordinate
    // mismatch problem when using fbo textures. It does not help.
    /* ofDisableArbTex(); */

    render_buffer.allocate(width, height, GL_RGBA); //RGB or RGBA here makes no difference.
    fx_effect.allocate(width, height);
}

void ofApp::draw_rect_to_fbo_and_update_effect() {
    render_buffer.begin();
    {
        ofPushStyle();
        ofPushMatrix();
        {
            // Draw a dark-teal background
            ofSetColor(35, 75, 75);
            ofRect(0, 0, width, height);

            // Draw a rectangle
            float xr = width / 4.0;
            float yr = height / 4.0;
            float wr = width / 2.0;
            float hr = height / 2.0;
            ofSetColor(ofColor::fromHsb(125, 255, 255)); // make rectangle teal
            ofRect((int)xr, (int)yr, (int)wr, (int)hr);
        }
        ofPopMatrix();
        ofPopStyle();
    }
    render_buffer.end();

    fx_effect << render_buffer;
    // This .update() isn't necessary, but is used in sandbox example. It should
    // be removed from there, though, since .update() is called by the << operator.
    fx_effect.update();
}


void ofApp::update(){
    // Comment this out if you're testing ofxBloom
    // Has no effect on ofxGaussianBlur.
    // If 15, will make ofxBokeh draw nothing.
    fx_effect.setRadius(1.5);

    draw_rect_to_fbo_and_update_effect();
 } 

//--------------------------------------------------------------
void ofApp::draw(){

    /* draw_rect_to_fbo_and_update_effect(); */

    // We use a dark red background to easily see what we have painted ourselves.
    // Sandbox-example uses a black background. That changes nothing.
    ofBackground(70,35,35);
    /* ofBackground(0); */

    // This outputs the rectangle properly.
    /* render_buffer.draw(0, 0, width, height); */

    // This outputs the rectangle properly, so we know that the effect's textures[0]
    // is set to contain the render_buffer ofFbo's contents properly.
    fx_effect[0].draw(0, 0, width, height);

    // These things are set in the sandbox-example. Removing them produces identical results.
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);

    // ofxBokeh:
    // Will draw nothing in top left, top right and bottom left quadrants.
    // Will draw black pixels in lower right quadrant.
    // ofxBloom:
    // Draws a desaturated square in the lower right quadrant.
    // ofxGaussianBlur:
    // Will fill transparent pixels (anything not painted) of the fbo with black.
    // Will draw the fbo unchanged.
    // Will draw black pixels on the lower right quadrant afterwards.
    fx_effect.draw(0, 0, width, height);

    // Also from sandbox-example.
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
