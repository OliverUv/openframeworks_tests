#include "ofApp.h"
#include "ofFbo.h"

void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE); // Removing this does not make bokeh work.
    ofEnableAlphaBlending();

    // This was proposed as a solution on the forums for a texture/coordinate
    // mismatch problem when using fbo textures. It does not help.
    /* ofDisableArbTex(); */

    shader.load("shadersGL3/shader");

    // We enlarge the plane so it covers half the screen.
    int plane_width = width * 0.5;
    int plane_height = height * 0.5;
    int plane_grid_size = 60;
    int plane_columns = plane_width / plane_grid_size;
    int plane_rows = plane_height / plane_grid_size;
    plane.set(plane_width, plane_height, plane_columns, plane_rows, OF_PRIMITIVE_TRIANGLES);

    render_buffer.allocate(width, height, GL_RGBA); //RGB or RGBA here makes no difference.
    fx_effect.allocate(width, height);
}

void ofApp::draw_plane_and_update_effect() {
    ofFloatColor c = ofColor::fromHsb(125, 255, 255); // Teal color
    float line_color[4] = {c.r, c.g, c.b, c.a};

    render_buffer.begin();
    shader.begin();
    {
        // Drawing the background to the render_buffer fbo has no effect.

        // This just sets the color for all frags
        shader.setUniform4fv("line_color", &line_color[0]);

        ofPushMatrix();
        {
            // draw plane in center of screen
            float cx = width / 2.0;
            float cy = height / 2.0;
            ofTranslate(cx, cy);
            /* plane.drawWireframe(); */
            plane.draw();
        }
        ofPopMatrix();
    }
    shader.end();
    render_buffer.end();

    fx_effect << render_buffer;
    // This .update() isn't necessary, but is used in sandbox example. It should
    // be removed from there, though, since .update() is called by the << operator.
    fx_effect.update();
}


void ofApp::update(){
    // Comment this out if you're testing ofxBloom
    fx_effect.setRadius(1.5);

    /* draw_plane_and_update_effect(); */
 } 

//--------------------------------------------------------------
void ofApp::draw(){

    draw_plane_and_update_effect();

    // We use a dark red background to easily see what we have painted ourselves.
    // Sandbox-example uses a black background. Using that does not help.
    ofBackground(70,35,35);
    /* ofBackground(0); */

    // This outputs the plane properly.
    /* render_buffer.draw(0, 0, width, height); */

    // This outputs the plane properly, so we know that the effect's
    // tex0 is set to contain the render_buffer ofFbo's contents properly.
    fx_effect[0].draw(0, 0, width, height);

    // These things are used in sandbox-example. They don't change anything though.
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);

    // ofxBokeh:
    // Will draw nothing in top left, top right and bottom left quadrants.
    // Will draw black pixels in lower right quadrant.
    // ofxBloom:
    // Will draw nothing at all.
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
