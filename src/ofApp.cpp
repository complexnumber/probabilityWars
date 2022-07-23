#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(225, 193, 110);
    ofSetWindowTitle("Probability Wars");
    ofSetFullscreen(false);
    //ofEnableSmoothing();

    game_settings = new GameSettings();
    if (game_settings->setup(13, 13, 9)) {
        game_state = gameState::START;
    }
    else {
        game_state = gameState::END;
    }
    game_settings->setFont("Arial.ttf", 20);
    game_settings->setWorldGraphics(0.85);
    game_settings->setCoin(20, 2, 6);
    game_settings->setTourTime(20);
    game_settings->setCountriesRandom();

    coin = new Coin();
    coin->setup(game_settings);
    world = new World();
    world->setup(game_settings);
    game = new GameFlow();
    game->setup(game_settings, world, coin);
}

//--------------------------------------------------------------
void ofApp::update(){
    switch (game_state) {
        case gameState::START: {
            break;
        }
        case gameState::GAME: {
            world->update();
            game->update();
            coin->update();
            break;
        }
        case gameState::END: {
            if (ofGetElapsedTimef() > 5) {
                ofExit();
            }
            break;
        }
        default: {
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (game_state){
        case gameState::START: {
            break;
        }
        case gameState::GAME: {
            world->draw();
            coin->draw();
            game->draw();
            break;
        }
        case gameState::END: {
            const string text = "Error";
            ofSetColor(0);
            game_settings->getFont().drawString(text, ofGetWidth() / 2 - game_settings->getFont().stringWidth(text) / 2, ofGetHeight() / 2 - game_settings->getFont().stringHeight(text) / 2);
            break;
        }
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ':
            switch (game_state) {
                case gameState::START: {
                    world->setupCountries();
                    game_state = gameState::GAME;
                    break;
                }
                case gameState::GAME: {
                    world->resetWorld();
                    game_state = gameState::START;
                    break;
                }
                case gameState::END: {
                    break;
                }
                default: {
                    break;
                }
                break;
            }
            break;
        case 'q': {
            ofExit();
            break;
        }
        case 'f': {
            ofToggleFullscreen();
            break;
        }
        default: {
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    switch (button) {
        case 0: {
            break;
        }
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        default: {
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    switch (game_state) {
        case gameState::START: {
            break;
        }
        case gameState::GAME: {
            switch (button) {
                case 0: {
                    world->getGrid()->updateSelectedUnits(x, y);
                    coin->checkPress(x, y);
                    game->checkPress(x, y);
                    break;
                }
                case 1: {
                    break;
                }
                case 2: {
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case gameState::END: {
            break;
        }
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
