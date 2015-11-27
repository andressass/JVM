//#################################################################################################
/*! \file M_OPTHREAD.c
 *
 *  \brief Modulo de threads da JVM
 *
 *  Modulo responsavel por implementar os metodos relacionados as operacoes que involvam Threads
 */
//##################################################################################################


#define OPTHREAD_SERV

#include <stdio.h>
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"


//--------------------------------------------------------------------------------------------------
Thread* newThread(){
    return NULL;
}


//--------------------------------------------------------------------------------------------------

void pushFrame(Thread* thread, const char* className, const char* methodName,
               const char*  MethodDescriptor){
}


//--------------------------------------------------------------------------------------------------
void popFrame(Thread* thread){
}


//--------------------------------------------------------------------------------------------------
Frame* getCurrentFrame(Thread* thread){
    return NULL;
}
