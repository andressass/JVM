//#################################################################################################
/*! \file I_EXCEPTION.c
 *
 *  \brief Modulo de excessoes da JVM.
 *
 *  Interface responsavel por implementar os servicos relacionados ao tratamento de excessoes
 *  lancadas pela JVM.
 */
//##################################################################################################

#define EXCEPTION_SERV
#include <stdio.h>
#include <stdlib.h>


//--------------------------------------------------------------------------------------------------
void JVMstopAbrupt(const char* msg){
    
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    if(msg) printf("\nERRO: %s", msg);
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    
    printf("\n\nForcando enceramento da JVM...\n\n");

    //TODO Liberar todas as estruturas
    
    exit(-1);
    
}