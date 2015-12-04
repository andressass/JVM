//#################################################################################################
/*! \file JAVAARRAY.c
 *
 *  \brief Biblioteca de arrays Java
 *
 *  Biblioteca responsavel por implementar os metodos relacionados aos arrays da JVM
 */
//##################################################################################################

#define JAVAARRAY_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/Estruturas/JAVAARRAY.h"


//--------------------------------------------------------------------------------------------------
JavaArray* newJavaArray(u1 n_type, u2 n_length, u4* n_arrayAdress){
    
    JavaArray* array_info = (JavaArray*) malloc(sizeof(JavaArray));
    array_info->type = n_type;
    array_info->length = n_length;
    array_info->arrayAddress = n_arrayAdress;
    
    return array_info;
}