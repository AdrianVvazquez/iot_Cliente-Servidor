#include <stdio.h>
#include <errno.h>
#include <string.h> 
#include "SUCKIT.h"

int main(){
    int sfd, cfd;
    
    sfd = Crear_Socket();
    
    while(1){    
        cfd = Escuchar_Socket(sfd);
        if(cfd < 0){
            fprintf(stderr, "[SERVER-ERROR]: Conexión rechazada. %d: %s \n", errno, strerror( errno ));
            return -1;
        } else{
            // crear hilo
            Despachar_Socket(cfd);
        }
    }
    return 0;
}