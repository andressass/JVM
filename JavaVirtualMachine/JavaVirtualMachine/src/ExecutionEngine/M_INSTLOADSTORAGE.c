//#################################################################################################
/*! \file M_INSTMEMORY.c
 *
 *  \brief Modulo das Instrucoes de carga e armazenamento da JVM.
 *
 *  Modulo responsavel pela implementacao dos servicos relacionados a instrucoes que transferem 
 *  valores entre o vetor de variaveis locais e a pilha de operandos de um frame de um metodo.
 */
//##################################################################################################

#define INSTLOADSTORAGE_SERV

#include <stdio.h>
#include <stdlib.h>
#include "../../include/ExecutionEngine/I_INSTLOADSTORAGE.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/Util/I_TYPECONVERSION.h"



//--------------------------------------------------------------------------------------------------
void nop(Thread* thread){}


//--------------------------------------------------------------------------------------------------
void aconst_null(Thread* thread){
    
    pushInOperandStack(thread, (u4)NULL);
}


//--------------------------------------------------------------------------------------------------
void iconst_m1(Thread* thread){
    
    pushInOperandStack(thread, -1);
}


//--------------------------------------------------------------------------------------------------
void iconst_0(Thread* thread){
    
    pushInOperandStack(thread, 0);
}


//--------------------------------------------------------------------------------------------------
void iconst_1(Thread* thread){
    
    pushInOperandStack(thread, 1);
}


//--------------------------------------------------------------------------------------------------
void iconst_2(Thread* thread){
    
    pushInOperandStack(thread, 2);
}


//--------------------------------------------------------------------------------------------------
void iconst_3(Thread* thread){
    
    pushInOperandStack(thread, 3);
}


//--------------------------------------------------------------------------------------------------
void iconst_4(Thread* thread){
    
    pushInOperandStack(thread, 4);
}


//--------------------------------------------------------------------------------------------------
void iconst_5(Thread* thread){
    
    pushInOperandStack(thread, 5);
}


//--------------------------------------------------------------------------------------------------
void lconst_0(Thread* thread){
    
//    long long_const = 0;
//    
//    u4 high_long = long_const>>32;
//    u4 low_long = long_const&0x0000ffff;
    
    pushInOperandStack(thread, 0); //parte baixa
    pushInOperandStack(thread, 0); //parte alta
}


//--------------------------------------------------------------------------------------------------
void lconst_1(Thread* thread){
    
    pushInOperandStack(thread, 1);
    pushInOperandStack(thread, 0);
}


//--------------------------------------------------------------------------------------------------
void fconst_0(Thread* thread){
    
    pushInOperandStack(thread, 0.0f);
}


//--------------------------------------------------------------------------------------------------
void fconst_1(Thread* thread){
    
    pushInOperandStack(thread, 1.0f);
}


//--------------------------------------------------------------------------------------------------
void fconst_2(Thread* thread){
    
    pushInOperandStack(thread, 2.0f);
}


//--------------------------------------------------------------------------------------------------
void dconst_0(Thread* thread){
    
    pushInOperandStack(thread, 0.0f);
    pushInOperandStack(thread, 0.0f);
}


//--------------------------------------------------------------------------------------------------
void dconst_1(Thread* thread){
    
    pushInOperandStack(thread, 1.0f); //parte baixa
    pushInOperandStack(thread, 0.0f); //parte alta
}


//--------------------------------------------------------------------------------------------------
void bipush(Thread* thread){
    
    thread->PC++;
    u1 byte_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                          thread->vmStack->top->javaClass->arqClass->constant_pool
                          ,thread->PC);
    
    int byte_extend = byte_argument;
    
    pushInOperandStack(thread, byte_extend);
}


//--------------------------------------------------------------------------------------------------
void sipush(Thread* thread){
    
    thread->PC++;
    u1 byte1_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                             thread->vmStack->top->javaClass->arqClass->constant_pool
                                             ,thread->PC);
    
    thread->PC++;
    u1 byte2_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    short short_result = (byte1_argument << 8) | byte2_argument;
    
    int short_extend = short_result;
    
    pushInOperandStack(thread, short_extend);
}


//--------------------------------------------------------------------------------------------------
void ldc(Thread* thread){
    
    thread->PC++;
    u1 index_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    u1 tag_valor_constant_pool = thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1].tag;
    
    if (tag_valor_constant_pool == CONSTANT_Integer){
        
        int valor_numerico_i = thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1].u.Integer.bytes;
        
        pushInOperandStack(thread, valor_numerico_i);
    }
    else if (tag_valor_constant_pool == CONSTANT_Float){
        
        float valor_numerico_f = u4ToFLoat(thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1].u.Float.bytes);
        
        pushInOperandStack(thread, valor_numerico_f);
    }
    else if (tag_valor_constant_pool == CONSTANT_String){
        
        u2 referencia = thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1].u.String.string_index;
        
        pushInOperandStack(thread, referencia);
    }
}


//--------------------------------------------------------------------------------------------------
void ldc_w(Thread* thread){
    
    thread->PC++;
    u1 index1byte_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    thread->PC++;
    u1 index2byte_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                                   thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,thread->PC);
    
    u2 index_result = (index1byte_argument << 8) | index2byte_argument;
    
    u1 tag_valor_constant_pool = thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].tag;
    
    if (tag_valor_constant_pool == CONSTANT_Integer){
        
        int valor_numerico_i = thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Integer.bytes;
        
        pushInOperandStack(thread, valor_numerico_i);
    }
    else if (tag_valor_constant_pool == CONSTANT_Float){
        
        float valor_numerico_f = (float)thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Float.bytes;
        
        pushInOperandStack(thread, valor_numerico_f);
    }
    else if (tag_valor_constant_pool == CONSTANT_String){
        
        u2 referencia = thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.String.string_index;
        
        pushInOperandStack(thread, referencia);
    }
}


//--------------------------------------------------------------------------------------------------
void ldc2_w(Thread* thread){
    
    thread->PC++;
    u1 index1byte_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                                   thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,thread->PC);
    
    thread->PC++;
    u1 index2byte_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                                   thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,thread->PC);
    
    u2 index_result = (index1byte_argument << 8) | index2byte_argument;
    
    u1 tag_valor_constant_pool = thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].tag;
    
    if (tag_valor_constant_pool == CONSTANT_Long){
        
        //Estrutura Long e Double possuem o mesmo formato
        int valor_numerico_high_i = (int)thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Long.high_bytes;
        
        int valor_numerico_low_i = (int)thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Long.low_bytes;
        
        pushInOperandStack(thread, valor_numerico_low_i);
        pushInOperandStack(thread, valor_numerico_high_i);
    }
    else if (tag_valor_constant_pool == CONSTANT_Double){
        
        //Estrutura Long e Double possuem o mesmo formato
        float valor_numerico_high_f = u4ToFLoat(thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Double.high_bytes);
        
        float valor_numerico_low_f = u4ToFLoat(thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Double.low_bytes);
        
        pushInOperandStack(thread, valor_numerico_low_f);
        pushInOperandStack(thread, valor_numerico_high_f);
    }
}


//--------------------------------------------------------------------------------------------------
void iload(Thread* thread){
    
    thread->PC++;
    u1 index_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    
    int valor_numerico = thread->vmStack->top->localVariablesVector[index_argument-1];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void lload(Thread* thread){
    
    thread->PC++;
    u1 index_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    
    int valor_numerico_high = thread->vmStack->top->localVariablesVector[index_argument-1];
    
    int valor_numerico_low = thread->vmStack->top->localVariablesVector[index_argument];
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void fload(Thread* thread){
    
    thread->PC++;
    u1 index_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    
    float valor_numerico = u4ToFLoat(thread->vmStack->top->localVariablesVector[index_argument-1]);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void dload(Thread* thread){
    
    thread->PC++;
    u1 index_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    
    float valor_numerico_high = u4ToFLoat(thread->vmStack->top->localVariablesVector[index_argument-1]);
    
    float valor_numerico_low = u4ToFLoat(thread->vmStack->top->localVariablesVector[index_argument]);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void aload(Thread* thread){
    
    thread->PC++;
    u1 index_argument = getByteCodeFromMethod(thread->vmStack->top->method_info,
                                              thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,thread->PC);
    
    
    u4 valor_numerico = thread->vmStack->top->localVariablesVector[index_argument-1];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_0(Thread* thread){
    
    int valor_numerico = thread->vmStack->top->localVariablesVector[0];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_1(Thread* thread){
    
    int valor_numerico = thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_2(Thread* thread){
    
    int valor_numerico = thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_3(Thread* thread){
    
    int valor_numerico = thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void lload_0(Thread* thread){
    
    int valor_numerico_high = thread->vmStack->top->localVariablesVector[0];
    
    int valor_numerico_low = thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void lload_1(Thread* thread){
    
    int valor_numerico_high = thread->vmStack->top->localVariablesVector[1];
    
    int valor_numerico_low = thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void lload_2(Thread* thread){
    
    int valor_numerico_high = thread->vmStack->top->localVariablesVector[2];
    
    int valor_numerico_low = thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void lload_3(Thread* thread){
    
    int valor_numerico_high = thread->vmStack->top->localVariablesVector[3];
    
    int valor_numerico_low = thread->vmStack->top->localVariablesVector[4];
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void fload_0(Thread* thread){
    
    float valor_numerico = u4ToFLoat(thread->vmStack->top->localVariablesVector[0]);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void fload_1(Thread* thread){
    
    float valor_numerico = u4ToFLoat(thread->vmStack->top->localVariablesVector[1]);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void fload_2(Thread* thread){
    
    float valor_numerico = u4ToFLoat(thread->vmStack->top->localVariablesVector[2]);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void fload_3(Thread* thread){
    
    float valor_numerico = u4ToFLoat(thread->vmStack->top->localVariablesVector[3]);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void dload_0(Thread* thread){
    
    float valor_numerico_high = u4ToFLoat(thread->vmStack->top->localVariablesVector[0]);
    
    float valor_numerico_low = u4ToFLoat(thread->vmStack->top->localVariablesVector[1]);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void dload_1(Thread* thread){
    
    float valor_numerico_high = u4ToFLoat(thread->vmStack->top->localVariablesVector[1]);
    
    float valor_numerico_low = u4ToFLoat(thread->vmStack->top->localVariablesVector[2]);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void dload_2(Thread* thread){
    
    float valor_numerico_high = u4ToFLoat(thread->vmStack->top->localVariablesVector[2]);

    float valor_numerico_low = u4ToFLoat(thread->vmStack->top->localVariablesVector[3]);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void dload_3(Thread* thread){
    
    float valor_numerico_high = u4ToFLoat(thread->vmStack->top->localVariablesVector[3]);
    
    float valor_numerico_low = u4ToFLoat(thread->vmStack->top->localVariablesVector[4]);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void aload_0(Thread* thread){
    
    u4 valor_numerico = thread->vmStack->top->localVariablesVector[0];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void aload_1(Thread* thread){
    
    u4 valor_numerico = thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void aload_2(Thread* thread){
    
    u4 valor_numerico = thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void aload_3(Thread* thread){
    
    u4 valor_numerico = thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iaload(Thread* thread){
    
    u4 index = popFromOperandStack(thread);
    
    int* arrayref = (int*) popFromOperandStack(thread);
    
    if (arrayref == NULL) {
        //TODO: throw NullPointerException;
    }
    
    //TODO: Otherwise, if index is not within the bounds of the array referenced by arrayref, the iaload instruction throws an ArrayIndexOutOfBoundsException.
    
    int valor_numerico = *(arrayref+index);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void laload(Thread* thread){
    
    u4 index = popFromOperandStack(thread);
    
    int* arrayref = (int*) popFromOperandStack(thread);
    
    if (arrayref == NULL) {
        //TODO: throw NullPointerException;
    }
    
    //TODO: Otherwise, if index is not within the bounds of the array referenced by arrayref, the iaload instruction throws an ArrayIndexOutOfBoundsException.
    
    int valor_numerico_high = *(arrayref+index);
    
    int valor_numerico_low = *(arrayref+index+1);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void faload(Thread* thread){
    
    u4 index = popFromOperandStack(thread);
    
    int* arrayref = (int*) popFromOperandStack(thread);
    
    if (arrayref == NULL) {
        //TODO: throw NullPointerException;
    }
    
    //TODO: Otherwise, if index is not within the bounds of the array referenced by arrayref, the iaload instruction throws an ArrayIndexOutOfBoundsException.
    
    float valor_numerico = *(arrayref+index);
    
    pushInOperandStack(thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void daload(Thread* thread){
    
    u4 index = popFromOperandStack(thread);
    
    int* arrayref = (int*) popFromOperandStack(thread);
    
    if (arrayref == NULL) {
        //TODO: throw NullPointerException;
    }
    
    //TODO: Otherwise, if index is not within the bounds of the array referenced by arrayref, the iaload instruction throws an ArrayIndexOutOfBoundsException.
    
    float valor_numerico_high = *(arrayref+index);
    
    float valor_numerico_low = *(arrayref+index+1);
    
    pushInOperandStack(thread, valor_numerico_low);
    pushInOperandStack(thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void aaload(Thread* thread){
    
    u4 index = popFromOperandStack(thread);
    
    int* arrayref = (int*) popFromOperandStack(thread);
    
    if (arrayref == NULL) {
        //TODO: throw NullPointerException;
    }
    
    //TODO: Otherwise, if index is not within the bounds of the array referenced by arrayref, the iaload instruction throws an ArrayIndexOutOfBoundsException.
    
    int valor_numerico = *(arrayref+index);
    
    pushInOperandStack(thread, valor_numerico);
}

