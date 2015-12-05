//#################################################################################################
/*! \file I_JAVADECODER.c
 *
 *  \brief Modulo decodificador de bibliotecas Java
 *
 *  Interface responsavel por implementar os servicos relacionados a decodificacao de metodos,
 * campos e estuturas que simulam o acesso a bibliotecas Java.
 */
//##################################################################################################


#define JAVADECODER_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/Util/I_JAVADECODER.h"


//--------------------------------------------------------------------------------------------------
int isFromJavaLib(const char* name){

    if (strncmp(name, "java/", 5) == 0) return 1;
    if (strncmp(name, "Ljava/", 6) == 0) return 1;
    
    return 0;
}

//--------------------------------------------------------------------------------------------------
void executeJavaLibMethod(const char* className, const char* methodName, const char* descriptorName,
                          Environment* environment){

    //Metodos de java/lang
    if (strncmp(className, "java/lang/", 10)==0) {
        //TODO: DECODE JAVA:LANG
    }
    //Metodos de java/io
    else if (strncmp(className, "java/io/", 8)==0) {
        //TODO: DECODE JAVA:IO
    }
}


//--------------------------------------------------------------------------------------------------
void getStaticFromJavaLib(const char* className, const char* fieldName,
                          const char* fieldDescriptor, Environment* environment){
    
    //Campos de java/lang
    if (strncmp(className, "java/lang/", 10)==0) {
        //TODO: CAMPOS JAVA:LANG
    }
    //Campos de java/io
    else if (strncmp(className, "java/io/", 8)==0) {
        //TODO: CAMPOS JAVA:IO
    }
}



//--------------------------------------------------------------------------------------------------
void newObjectFromJavaLib(const char* className, Environment* environment){
    //Campos de java/lang
    if (strncmp(className, "java/lang/", 10)==0) {
        //TODO: OBJETO JAVA:LANG
    }
    //Campos de java/io
    else if (strncmp(className, "java/io/", 8)==0) {
        //TODO: OBJETO JAVA:IO
    }
}