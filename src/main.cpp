#include "ofMain.h"
#include "ofApp.h"

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	// ofSetupOpenGL(1024, 768, OF_FULLSCREEN); // 1024x768 Full Screen
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
