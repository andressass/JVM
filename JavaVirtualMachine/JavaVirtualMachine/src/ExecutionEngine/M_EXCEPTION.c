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


//--------------------------------------------------------------------------------------------------
void JVMstopAbrupt(const char* msg){
    
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    if(msg) printf("\nERRO:\n %s", msg);
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    
    printf("\n\nForcando enceramento da JVM...\n\n");

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
        default:
            break;
    }
    strcat(mensagem, "\n------------------------------------");
    strcat(mensagem, "\nClasse: ");
    strcat(mensagem, getClassNameFromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread->vmStack->top->javaClass->arqClass->this_class));
    
    strcat(mensagem, "\nMetodo: ");
    strcat(mensagem, getUTF8FromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread->vmStack->top->method_info->name_index));
    strcat(mensagem, "\n------------------------------------");
    
    JVMstopAbrupt(mensagem);

}