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
JavaArray* newJavaArray(u4 n_atype, u2 n_count, void* n_arrayAddress){
    
    JavaArray* array_info = (JavaArray*) malloc(sizeof(JavaArray));
    array_info->atype = n_atype;
    array_info->count = n_count;
    array_info->arrayAddress = n_arrayAddress;
    
    return array_info;
}