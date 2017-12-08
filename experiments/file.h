
#include <SPI.h>
#include <SD.h>

void begin_sd_controller(){
    pinMode( 13, OUTPUT);
    if(!SD.begin( 4 ))
        Serial.println("Fail to load SD Card!");
}

void file_crip_operation( char*(*rot)(char*,char*), char* file_name, char* key ) {
    if(!SD.exists( file_name ))
        Serial.println("file not found");
    File f = SD.open( file_name, "FILE_READ" ) ;
    f.seek(NULL);
    char block[32];
    while( f.available() ){
        f.read(block,32);
        free( rot(block,key) );
        Serial.print("|");
    }
    f.close();
}