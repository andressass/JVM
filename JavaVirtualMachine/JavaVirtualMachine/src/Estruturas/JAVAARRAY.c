//#################################################################################################
/*! \file JAVAARRAY.c
 *
 *  \brief Biblioteca de arrays Java
 *
 *  Biblioteca responsavel por implementar os metodos relacionados aos arrays da JVM
 */
//##################################################################################################

#define JAVAARRAY_SERV

#include "../../include/Estruturas/JAVAARRAY.h"


//--------------------------------------------------------------------------------------------------
JavaArray* newJavaArray(u1 n_atype, u2 n_count){
    
    JavaArray* array_info = (JavaArray*) malloc(sizeof(JavaArray));
    array_info->atype = n_atype;
    array_info->count = n_count;
    
    if (n_atype == T_BYTE || n_atype == T_BOOLEAN || n_atype == T_CHAR) {
        array_info->arrayAddress = (u1*) malloc(sizeof(u4) * n_count);
    }
    else if (n_atype == T_SHORT) {
        array_info->arrayAddress = (u2*) malloc(sizeof(u2) * n_count);
    }
    else if (n_atype == T_INT || n_atype == T_FLOAT) {
        array_info->arrayAddress = (u4*) malloc(sizeof(u4) * n_count);
    }
    else if (n_atype == T_LONG || n_atype == T_DOUBLE) {
        array_info->arrayAddress = (u4*) malloc(sizeof(u4) * n_count * 2);
    }
    // Se for do tipo reference
    else {
        
        array_info->arrayAddress = NULL;
    }
    
    return array_info;
}