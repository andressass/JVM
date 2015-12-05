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
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

#include "../../include/Util/I_JAVALANG.h"
#include "../../include/Util/I_JAVAIO.h"


//--------------------------------------------------------------------------------------------------
int javaLibIsFrom(const char* name){
    if (strncmp(name, "java/", 5) == 0) return 1;
    if (strncmp(name, "Ljava/", 6) == 0) return 1;
    
    return 0;
}

//--------------------------------------------------------------------------------------------------
void javaLibExecuteMethod(const char* className, const char* methodName, const char* descriptorName,
                          Environment* environment){

    //Metodos de java/lang
    if (strncmp(className, "java/lang/", 10)==0) {
        //TODO: DECODE JAVA:LANG
        javaLangExecuteMethod(&className[10], methodName, descriptorName, environment);
    }
    //Metodos de java/io
    else if (strncmp(className, "java/io/", 8)==0) {
        //TODO: DECODE JAVA:IO
        javaIOExecuteMethod(&className[8], methodName, descriptorName, environment);
    }
    else
        popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
void javaLibGetStatic(const char* className, const char* fieldName,
                          const char* fieldDescriptor, Environment* environment){
    
    //Campos de java/lang
    if (strncmp(className, "java/lang/", 10)==0) {
        //TODO: CAMPOS JAVA:LANG
        javaLangGetStatic(&className[10], fieldName, fieldDescriptor, environment);
    }
    //Campos de java/io
    else if (strncmp(className, "java/io/", 8)==0) {
        //TODO: CAMPOS JAVA:IO
        javaIOGetStatic(&className[8], fieldName, fieldDescriptor, environment);
    }
    else
    pushInOperandStack(environment->thread, 0);
}



//--------------------------------------------------------------------------------------------------
void javaLibNewObject(const char* className, Environment* environment){
    //Campos de java/lang
    if (strncmp(className, "java/lang/", 10)==0) {
        //TODO: OBJETO JAVA:LANG
        javaLangNewObject(&className[10], environment);
    }
    //Campos de java/io
    else if (strncmp(className, "java/io/", 8)==0) {
        //TODO: OBJETO JAVA:IO
        javaIONewObject(&className[8], environment);
    }
    else
        pushInOperandStack(environment->thread, 0);
}