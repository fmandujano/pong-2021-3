#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    posPaletaP1 = new ofVec2f(10, 50 );
    posPaletaP2 = new ofVec2f(10, 50 );
    rPelota = 15;
    posPelota = new ofVec2f (ofGetWidth()/2, ofGetHeight()/2);
    velPelota = new ofVec2f(100,100 );
}

//--------------------------------------------------------------
void ofApp::update()
{
    //calculo de movimieento de jugador local
    if(w) posPaletaP1->y -= 50 * ofGetLastFrameTime() ;
    if(s) posPaletaP1->y += 50 * ofGetLastFrameTime() ;

    //calculo de movimiento de la pelota
    posPelota->x += velPelota->x * ofGetLastFrameTime();
    posPelota->y += velPelota->y * ofGetLastFrameTime();

    //rebotes de pelota
    if ( posPelota->x <=0 )
    {
        velPelota->x *= -1;
        posPelota->x = 1;
    }
    if ( posPelota->x > ofGetWidth() )
    {
        velPelota->x *= -1;
        posPelota->x = ofGetWidth()-1;
    }
    if ( posPelota->y <=0 )
    {
        velPelota->y *= -1;
        posPelota->y = 1;
    }
    if ( posPelota->y > ofGetHeight() )
    {
        velPelota->y *= -1;
        posPelota->y = ofGetHeight() -1;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(ofColor::black);
    ofSetColor(255,255,0);
    ofCircle( posPelota->x,posPelota->y, 0, rPelota);
    //dinbujar paletas de jugadores
    ofRect(posPaletaP1->x, posPaletaP1->y, 15,50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if( key == 'w' )
    {
        w = true;
    }
    if( key == 's' )
    {
        s = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if( key == 'w' )
    {
        w = false;
    }
    if( key == 's' )
    {
        s = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
