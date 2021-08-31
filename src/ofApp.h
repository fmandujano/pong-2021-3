#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        //estado de las teclas de movimiento
        bool w,s;
        //posicion de la paleta
        ofVec2f * posPaletaP1;
        ofVec2f * posPaletaP2;
        ofVec2f * posPelota;
        ofVec2f * velPelota;
        float rPelota;
};
