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
#include "../../include/ExecutionEngine/I_EXCEPTION.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/Estruturas/OPCODES.h"

#define INTERPRETER_SERV


//--------------------------------------------------------------------------------------------------
void execute(Environment* environment){

    //! Enquanto a pilha de frames nao estiver vazia:
    while (environment->thread->vmStack != NULL) {

        //! 1.Obtem o opcode.
        u1 opcode = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                          environment->thread->vmStack->top->javaClass->arqClass->constant_pool,
                                          environment->thread->PC);
        
        //! 2.Decodifica o opcode
        instruction nextInstruction = decode(opcode);
        
        //! 2.1 Imprime informações de frame em modo de debug
        if(environment->debugFlags & DEBUG_DebugModus){
            JVMPrintFrameInfo(environment->thread->vmStack->top, opcode);
            printf("\n> Pressione Enter para continuar...");
            getchar();
        }
        
        //! 3.Executa o a instrucao referente ao opcode
        if(nextInstruction) nextInstruction(environment);
        
        //! 4.Atualizamos o valor de PC
        environment->thread->PC++;
    }
    
}