#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //condiciones iniciales de los objetos de juego
    posPaletaP1 = new ofVec2f(10, 50 );
    posPaletaP2 = new ofVec2f(ofGetWidth()-15-10, 50 );
    rPelota = 15;
    posPelota = new ofVec2f (ofGetWidth()/2, ofGetHeight()/2);
    velPelota = new ofVec2f(100,100 );

    //estado inicial de la aplicacion
    AppState = EAppState::menu;

    //configurar el menu
    mainPanel.setup();
    mainPanel.add( btnServer.setup("Crear partida")  );
    mainPanel.add( btnClient.setup("Conectar a partida") );
    mainPanel.setPosition( ofGetWidth()/2 - mainPanel.getWidth()/2 ,
                           ofGetHeight()/2 - mainPanel.getHeight()/2);

    btnServer.addListener( this, &ofApp::setupServer );
    btnClient.addListener( this, &ofApp::setupClient );
}

void ofApp::setupServer()
{
    AppState = EAppState::server;
    puts("Creando servidor");

    udpManager.Create();
    udpManager.Bind( gamePort );
    udpManager.SetNonBlocking(true);

    int port;
    udpManager.GetListenAddr(serverIP, port);
    printf("ip local : %s ", serverIP.c_str());
}

void ofApp::setupClient()
{
    AppState = EAppState::client;
    puts("Creando cliente");

    udpManager.Create();

    //mostrar UI para pedir la IP
    string strIP = ofSystemTextBoxDialog("IP del servidor", "127.0.0.1" );

    udpManager.Connect( strIP.c_str()  , gamePort);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if( AppState == EAppState::server)
        updateServer();
    else if( AppState == EAppState::client)
        updateClient();
}


void ofApp::updateServer()
{
    //calculo de movimieento de jugador local
    if(w) posPaletaP1->y -= 150 * ofGetLastFrameTime() ;
    if(s) posPaletaP1->y += 150 * ofGetLastFrameTime() ;

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



    /* recibir mov del jugador remoto */
    memset(buffer, 0, BUFFER_SIZE);
    if( udpManager.Receive(buffer, BUFFER_SIZE ) > 0 )
    {
        //imprimir valor recibido
        //puts( buffer );
        //deserializar valores separados por comas
        char * tempBuffer;
        tempBuffer = strtok( buffer, ",");
        //el primer valor es la pos en X
        posPaletaP2->x = atof(tempBuffer);
        //el segundo valor se obtiene llamando otra vez a strtok
        tempBuffer = strtok( NULL, ",");
        posPaletaP2->y = atof(tempBuffer);
    }
}

void ofApp::updateClient()
{
    //calculo de movimieento de jugador local
    if(w) posPaletaP2->y -= 150 * ofGetLastFrameTime() ;
    if(s) posPaletaP2->y += 150 * ofGetLastFrameTime() ;

    /* enviar la posicion de la paleta P2 */
    //limpiar el buffer, poner a 0 sus bytes
    memset( buffer, 0, BUFFER_SIZE);
    //serializacion con valores separados por coma (CSV)
    sprintf( buffer, "%f,%f\n",posPaletaP2->x, posPaletaP2->y);
    //enviar por el socket
    udpManager.Send( buffer, BUFFER_SIZE );
}

//--------------------------------------------------------------
void ofApp::draw()
{
    if( AppState == EAppState::menu )
    {
        mainPanel.draw();
    }
    else
    {
        ofBackground(ofColor::black);
        ofSetColor(255,255,0);
        //titulo
        ofDrawBitmapString( AppState == EAppState::server ?
                                "SERVER" : "CLIENT",
                            15,15);


        ofCircle( posPelota->x,posPelota->y, 0, rPelota);
        //dinbujar paletas de jugadores
        ofRect(posPaletaP1->x, posPaletaP1->y, 15,100);
        ofRect( posPaletaP2->x, posPaletaP2->y, 15,100 );
    }
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
