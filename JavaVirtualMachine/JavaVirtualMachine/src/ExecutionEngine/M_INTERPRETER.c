//#################################################################################################
/*! \file M_INTERPRETER.c
 *
 *  \brief Modulo do Interpretador da JVM.
 *
 *  Modulo responsavel por implentar os servicos relacionados ao interpretador da JVM.
 */
//##################################################################################################

#include <stdio.h>
#include "../../include/ExecutionEngine/I_INTERPRETER.h"
#include "../../include/ExecutionEngine/I_DECODER.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

#define INTERPRETER_SERV


//--------------------------------------------------------------------------------------------------
void execute(Environment* environment){

    //Enquanto a pilha de frames nao estiver vazia
    while (environment->thread->vmStack != NULL) {

        //! Obtem o opcode
        u1 opcode = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                          environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                          , environment->thread->PC);
        
        //! Decodifica o opcode
        instruction nextInstruction = decode(opcode);
        
        //! Executa o a instrucao referente ao opcode
        if(nextInstruction) nextInstruction(environment->thread);
        else break; //REMOVER
        
        //Atualizamos o valor de PC
        environment->thread->PC++;
    }
    
}