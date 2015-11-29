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
#include <stdlib.h>
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"


//--------------------------------------------------------------------------------------------------
Thread* newThread(){
    
    Thread* thread = (Thread*) malloc(sizeof(Thread));

    thread->PC = 0;
    
    thread->vmStack = NULL;
    
    return thread;    
}


//--------------------------------------------------------------------------------------------------
void pushFrame(Environment* environment, const char* className, const char* methodName,
               const char*  MethodDescriptor){
    
    Frame* newFrame = (Frame*) malloc(sizeof(Frame));
    
    
    //Salvamos o pc do metodo anterior
    newFrame->returnPC = environment->thread->PC;
    
    //Colocamos pc na posicao de inicio do codigo do novo metodo
    environment->thread->PC = 0;
    
    //Empilhamos o frame
    VMStack* newStackFrame = (VMStack*) malloc(sizeof(VMStack));
    newStackFrame->next = environment->thread->vmStack;
    environment->thread->vmStack = newStackFrame;
    
    environment->thread->vmStack->top = newFrame;
    
    newFrame->javaClass = getClass(className, environment);
    
    //Buscamos o endereco do metodo
    newFrame->method_info = getMethodInfoFromClass(newFrame->javaClass, methodName, MethodDescriptor);
    //TODO: VERIFICAR RESTRICOES DE ACESSO DO METODO
    
    //Obtemos o atributo code do metodo
    CodeAttribute* methodCode = getCodeAttributeFromMethod(newFrame->javaClass, methodName,
                                                           MethodDescriptor);
    
    //TODO: Lancamento de erro caso nao exista atributo code
    
    //Alocamos o array de variaveis locais
    newFrame->localVariablesVector = (u4*) calloc(methodCode->max_locals, sizeof(u4));
    
    //Alocamos a pilha de operandos
    newFrame->opStk = (OperandStack*) calloc(methodCode->max_stack+1, sizeof(OperandStack));
    
    free(methodCode);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que libera recursivamente um frame da memoria
 *
 * \param frame Frame a ser desalocado
 */
void freeFrame(Frame* frame){
    free(frame->opStk);
    free(frame->localVariablesVector);
    free(frame);
}


//--------------------------------------------------------------------------------------------------
void popFrame(Thread* thread){
    if (thread->vmStack->top != NULL) {

        //Desempilhamos
        VMStack* oldStackFrame = thread->vmStack;
        thread->vmStack = thread->vmStack->next;
        
        //Retornamos PC
        thread->PC = oldStackFrame->top->returnPC;
        
        //Liberamos o frame da memoria
        freeFrame(oldStackFrame->top);
    }
}


//--------------------------------------------------------------------------------------------------
Frame* getCurrentFrame(Thread* thread){
    return thread->vmStack->top;
}


//--------------------------------------------------------------------------------------------------
void pushInOperandStack(Thread* thread, u4 value){
    Frame* currentFrame = getCurrentFrame(thread);
    
    //A o proximo elemento do "vetor" alocado da pilha, aponta para o elemento atual
    currentFrame->opStk[1].nextStack = currentFrame->opStk;
    //O elemento atual aponta para o proximo elemento
    currentFrame->opStk = &currentFrame->opStk[1];
    //Empilhamaos o valor no novo topo da pilha
    currentFrame->opStk->top = value;
}


//--------------------------------------------------------------------------------------------------
u4 popFromOperandStack(Thread* thread){
    Frame* currentFrame = getCurrentFrame(thread);
    
    //Salvamos uma referencia do elemento a ser desempilhado
    OperandStack* popped = currentFrame->opStk;
    //Desempilhamos (como eh um vetor fixo de elementos, somente passamos a referencia para o
    // proximo elemento)
    currentFrame->opStk = currentFrame->opStk->nextStack;
    
    //Retornamos o valor do elemento desempilhado
    return popped->top;
}

