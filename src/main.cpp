#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char** argv )
{
    //imprimir los argumentos proporcionados
    for(int i=0; i<argc; i++)
    {
        printf("argumento de programa: %i, %s \n",i, argv[i]);
    }

    int resX = 640;
    int resY = 480;
    bool fullscreen = false;
    int port = 6666 ;

    //analizar (parse) el archivo config.ini
    ifstream configfile;
    configfile.open("data/config.ini"); //ruta relativa a donde se encuentra el ejecutable

    if( configfile.is_open())
    {
        puts("leyendo datos del archivo config.ini");
        char * linea = new char[100];
        char *llave,*valor;
        while( !configfile.eof() )
        {
            configfile.getline(linea, 100);
            //ignorar lineas que comiencen con caracteres no aceptables
            if ( linea[0] != '/' &&
                 linea[0] != '[' &&
                 linea[0] != '\n' &&  //line feed
                 linea[0] != '\r' &&  //carriage return, solo en windows
                 linea[0] != '\0')
            {
                llave = strtok(linea,"=" );
                valor = strtok( NULL, "=");
                printf("llave: %s, valor:%s\n", llave,valor);
                if( !strcmp(llave,"resx") )
                    resX = atoi(valor);
                if( !strcmp(llave,"resy") )
                    resY = atoi(valor);
                if( !strcmp(llave,"fullscreen") )
                    fullscreen = atoi(valor)==0 ? false : true ;
                if( !strcmp(llave,"port") )
                    port = atoi(valor);
            }
        }
    }
    else
    {
        // "fallback", si no hay ini, usar argumentos del programa
        //asumir que el argumeno 1 es la resX y el arg 2 es en Y
        if( argc==3 )
        {
            resX = atoi( argv[1] );
            resY = atoi( argv[2] );
        }
    }

    ofSetupOpenGL( resX,resY,  fullscreen?OF_FULLSCREEN : OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    ofApp  * app = new ofApp();
    app->gamePort = port;
    ofRunApp(app);

}
