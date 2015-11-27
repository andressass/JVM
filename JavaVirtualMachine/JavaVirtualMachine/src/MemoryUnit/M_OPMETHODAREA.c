//#################################################################################################
/*! \file M_OPMETHODAREA.c
 *
 *  \brief Modulo da area de metodos da JVM
 *
 *  Modulo responsavel por implementar os metodos relacionados as operacoes que involvam a area de 
 *  metodos
 */
//##################################################################################################


#define OPMETHODAREA_SERV

#include <stdio.h>
#include <string.h>
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"


//--------------------------------------------------------------------------------------------------
JavaClass* findJavaClass(const char* qualifiedName, MethodArea* methodArea){
    //TODO: Implementar metodo
    
//REMOVER________________________________________________
    if (strcmp(qualifiedName,"java/lang/Object") == 0) {
        return (JavaClass*) 1;
    }
//REMOVER________________________________________________
    
    
    return NULL;
}
