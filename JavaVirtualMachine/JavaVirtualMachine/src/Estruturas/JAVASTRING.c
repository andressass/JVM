//#################################################################################################
/*! \file JAVASTRING.c
 *
 *  \brief Biblioteca de strings Java
 *
 *  Biblioteca responsavel por implementar os metodos relacionados as strings constantes da JVM
 */
//##################################################################################################

#define JAVASTRING_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/Estruturas/JAVASTRING.h"


//--------------------------------------------------------------------------------------------------
JavaString* newJavaString(const char* string){

    JavaString* string_info = (JavaString*) malloc(sizeof(JavaString));
    string_info->tag = CONSTANT_StringRef;
    string_info->size = strlen(string);
    string_info->stringAddress = (void*) string;
    
    return string_info;
}