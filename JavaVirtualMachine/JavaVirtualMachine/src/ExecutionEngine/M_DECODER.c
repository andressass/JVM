//#################################################################################################
/*! \file M_DECODER.h
 *
 *  \brief Modulo do Decodificador da JVM.
 *
 *  Interface responsavel pela implementacao os servicos relacionados a decodificacao de bytecodes
 *  em instrucoes.
 */
//##################################################################################################

#define DECODER_SERV

#include <stdio.h>
#include <stdlib.h>
#include "../../include/ExecutionEngine/I_DECODER.h"
#include "../../include/Estruturas/OPCODES.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

//Gambiarra de instrucao
void iadd_GAMBIARRA(Thread* thread){
    
    int a = popFromOperandStack(thread);
    int b = popFromOperandStack(thread);
    
    pushInOperandStack(thread, a+b);
}

//--------------------------------------------------------------------------------------------------
instruction decode(u1 bytecode){
    
    switch (bytecode) {
        case OP_iadd:
            return iadd_GAMBIARRA;
            break;
        default:
            break;
    }
    
    return NULL;

}
