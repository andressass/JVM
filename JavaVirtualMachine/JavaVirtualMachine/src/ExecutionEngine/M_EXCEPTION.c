//#################################################################################################
/*! \file I_EXCEPTION.c
 *
 *  \brief Modulo de excessoes da JVM.
 *
 *  Modulo responsavel por implementar os servicos relacionados ao tratamento de excessoes
 *  lancadas pela JVM.
 */
//##################################################################################################

#define EXCEPTION_SERV
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/ExecutionEngine/I_EXCEPTION.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"


//--------------------------------------------------------------------------------------------------
void JVMstopAbrupt(const char* msg){
    
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    if(msg) printf("\nERRO:\n %s", msg);
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    
    printf("\n\nForcando encerramento da JVM...\n\n");

    //TODO Liberar todas as estruturas
    
    exit(-1);
    
}


//--------------------------------------------------------------------------------------------------
void JVMThrow(int exception, Environment* environment){
    
    char mensagem[1000];
    strcpy(mensagem, "Excessao: ");
    
    //Selecionamos a mensagem de erro
    switch (exception) {
        case NullPointerException:
            strcat(mensagem, "NullPointerException");
            break;
        case AbstractMethodError:
            strcat(mensagem, "AbstractMethodError");
            break;
        case IncompatibleClassChangeError:
            strcat(mensagem, "IncompatibleClassChangeError");
            break;
        case IllegalAccessError:
            strcat(mensagem, "IllegalAccessError");
            break;
        case ArrayIndexOutOfBoundsException:
            strcat(mensagem, "ArrayIndexOutOfBoundsException");
            break;
        case NegativeArraySizeException:
            strcat(mensagem, "NegativeArraySizeException");
            break;
        default:
            break;
    }
    strcat(mensagem, "\n------------------------------------");
    strcat(mensagem, "\nClasse: ");
    strcat(mensagem, getClassNameFromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool,
                                                  environment->thread->vmStack->top->javaClass->arqClass->this_class));
    
    strcat(mensagem, "\nMetodo: ");
    strcat(mensagem, getUTF8FromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool,
                                             environment->thread->vmStack->top->method_info->name_index));
    strcat(mensagem, "\n------------------------------------");
    
    JVMstopAbrupt(mensagem);
}


//--------------------------------------------------------------------------------------------------
void JVMPrintFrameInfo(Frame* frame){

    printf("\n------------------------------------");
    
    printf("\nClasse: %s\n", getClassNameFromConstantPool(frame->javaClass->arqClass->constant_pool,
                                                          frame->javaClass->arqClass->this_class));
    printf("\nMetodo: %s\n", getUTF8FromConstantPool(frame->javaClass->arqClass->constant_pool,
                                                     frame->method_info->name_index));
    
    CodeAttribute* code = getCodeFromMethodInfo(frame->method_info, frame->javaClass->arqClass->constant_pool);
    
    printf("\nPilha de Operandos:");
    for (OperandStack* i = frame->opStk; i != NULL; i = i->nextStack) printf("\n| 0x%x", i->top);
    
    printf("\n\nVetor de Variaveis Locais:\n");

    for (int i = 0; i < code->max_locals; i++)
        printf(" 0x%x |", frame->localVariablesVector[i]);
    
    printf("\n------------------------------------");


}