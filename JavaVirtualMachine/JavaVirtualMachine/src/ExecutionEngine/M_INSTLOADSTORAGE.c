//#################################################################################################
/*! \file M_INSTLOADSTORAGE.c
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
#include <string.h>
#include "../../include/ExecutionEngine/I_INSTLOADSTORAGE.h"
#include "../../include/ExecutionEngine/I_EXCEPTION.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/Util/I_TYPECONVERSION.h"
#include "../../include/Estruturas/JAVAARRAY.h"
#include "../../include/Estruturas/OPCODES.h"



//--------------------------------------------------------------------------------------------------
void nop(Environment* environment){}


//--------------------------------------------------------------------------------------------------
void aconst_null(Environment* environment){
    
    pushInOperandStack(environment->thread, (u4)NULL);
}


//--------------------------------------------------------------------------------------------------
void iconst_m1(Environment* environment){
    
    pushInOperandStack(environment->thread, -1);
}


//--------------------------------------------------------------------------------------------------
void iconst_0(Environment* environment){
    
    pushInOperandStack(environment->thread, 0);
}


//--------------------------------------------------------------------------------------------------
void iconst_1(Environment* environment){
    
    pushInOperandStack(environment->thread, 1);
}


//--------------------------------------------------------------------------------------------------
void iconst_2(Environment* environment){
    
    pushInOperandStack(environment->thread, 2);
}


//--------------------------------------------------------------------------------------------------
void iconst_3(Environment* environment){
    
    pushInOperandStack(environment->thread, 3);
}


//--------------------------------------------------------------------------------------------------
void iconst_4(Environment* environment){
    
    pushInOperandStack(environment->thread, 4);
}


//--------------------------------------------------------------------------------------------------
void iconst_5(Environment* environment){
    
    pushInOperandStack(environment->thread, 5);
}


//--------------------------------------------------------------------------------------------------
void lconst_0(Environment* environment){
    
    pushInOperandStack(environment->thread, 0); //parte baixa
    pushInOperandStack(environment->thread, 0); //parte alta
}


//--------------------------------------------------------------------------------------------------
void lconst_1(Environment* environment){
    
    pushInOperandStack(environment->thread, 1);
    pushInOperandStack(environment->thread, 0);
}


//--------------------------------------------------------------------------------------------------
void fconst_0(Environment* environment){
    float x = 0;
    u4 Const;
    
    memcpy(&Const, &x, sizeof(u4));
    pushInOperandStack(environment->thread, Const);
}


//--------------------------------------------------------------------------------------------------
void fconst_1(Environment* environment){
    float x = 1;
    u4 Const;
    
    memcpy(&Const, &x, sizeof(u4));
    pushInOperandStack(environment->thread, Const);
}


//--------------------------------------------------------------------------------------------------
void fconst_2(Environment* environment){
    float x = 2;
    u4 Const;
    
    memcpy(&Const, &x, sizeof(u4));
    pushInOperandStack(environment->thread, Const);
}


//--------------------------------------------------------------------------------------------------
void dconst_0(Environment* environment){
    double x = 0;
    long long Const;
    
    memcpy(&Const, &x, sizeof(long long));
    
    u4 operandoPilha1 = (u4) ((Const & 0xFFFFFFFF00000000) >> 32);
    u4 operandoPilha2 = (u4) Const & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}


//--------------------------------------------------------------------------------------------------
void dconst_1(Environment* environment){
    double x = 1;
    long long Const;
    
    memcpy(&Const, &x, sizeof(long long));
    
    u4 operandoPilha1 = (u4) ((Const & 0xFFFFFFFF00000000) >> 32);
    u4 operandoPilha2 = (u4) Const & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}


//--------------------------------------------------------------------------------------------------
void bipush(Environment* environment){
    
    environment->thread->PC++;
    u1 byte_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                          environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                          ,environment->thread->PC);
    
    int byte_signal_extend = (signed char) byte_argument;
    
    pushInOperandStack(environment->thread, byte_signal_extend);
}


//--------------------------------------------------------------------------------------------------
void sipush(Environment* environment){
    
    environment->thread->PC++;
    u1 byte1_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                             environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                             ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 byte2_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    short short_result = (byte1_argument << 8) | byte2_argument;
    
    int short_signal_extend = (signed short) short_result;
    
    pushInOperandStack(environment->thread, short_signal_extend);
}


//--------------------------------------------------------------------------------------------------
void ldc(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    u1 tag_valor_constant_pool = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1].tag;
    
    if (tag_valor_constant_pool == CONSTANT_Integer || tag_valor_constant_pool == CONSTANT_Float){
        
        // Estrutra Integer e Float possuem o mesmo formato
        u4 valor_numerico = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1].u.Integer.bytes;
        
        pushInOperandStack(environment->thread, valor_numerico);
    }
    else if (tag_valor_constant_pool == CONSTANT_String){
        
        //CORRECAO: REFERENCIA PARA STRING INFO, NAO PARA O INDICE DA STRING INFO
        u4 referencia = (u4) &environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_argument-1];
        
        pushInOperandStack(environment->thread, referencia);
    }
}


//--------------------------------------------------------------------------------------------------
void ldc_w(Environment* environment){
    
    environment->thread->PC++;
    u1 index1byte_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 index2byte_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    u2 index_result = (index1byte_argument << 8) | index2byte_argument;
    
    u1 tag_valor_constant_pool = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].tag;
    
    if (tag_valor_constant_pool == CONSTANT_Integer || tag_valor_constant_pool == CONSTANT_Float){
        
        // Estrutra Integer e Float possuem o mesmo formato
        u4 valor_numerico = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Integer.bytes;
        
        pushInOperandStack(environment->thread, valor_numerico);
    }
    else if (tag_valor_constant_pool == CONSTANT_String){
        
        u4 referencia = (u4) &environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1];

        
        pushInOperandStack(environment->thread, referencia);
    }
}


//--------------------------------------------------------------------------------------------------
void ldc2_w(Environment* environment){
    
    environment->thread->PC++;
    u1 index1byte_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 index2byte_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    u2 index_result = (index1byte_argument << 8) | index2byte_argument;
    
    u1 tag_valor_constant_pool = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].tag;
    
    if (tag_valor_constant_pool == CONSTANT_Long || tag_valor_constant_pool == CONSTANT_Double){
        
        //Estrutura Long e Double possuem o mesmo formato
        u4 valor_numerico_high = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Long.high_bytes;
        
        u4 valor_numerico_low = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Long.low_bytes;
        
        pushInOperandStack(environment->thread, valor_numerico_low);
        pushInOperandStack(environment->thread, valor_numerico_high);
    }
}


//--------------------------------------------------------------------------------------------------
void iload(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[index_argument];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void lload(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[index_argument];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[index_argument+1];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void fload(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[index_argument];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void dload(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[index_argument];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[index_argument+1];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void aload(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[index_argument];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_0(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[0];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_1(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_2(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iload_3(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void lload_0(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[0];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void lload_1(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[1];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void lload_2(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[2];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void lload_3(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[3];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[4];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void fload_0(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[0];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void fload_1(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void fload_2(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void fload_3(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void dload_0(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[0];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void dload_1(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[1];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void dload_2(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[2];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void dload_3(Environment* environment){
    
    u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[3];
    u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[4];
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void aload_0(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[0];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void aload_1(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[1];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void aload_2(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[2];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void aload_3(Environment* environment){
    
    u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[3];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void iaload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u4 valor_numerico = *((u4*)((array_info->arrayAddress)+ index*sizeof(u4)));
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void laload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u8* array = array_info->arrayAddress;
    
    u8 value = array[index];
    
    u4 valor_numerico_high = value >> 32;
    u4 valor_numerico_low = (u4) value;
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void faload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u4 valor_numerico = *((u4*)((array_info->arrayAddress)+index*sizeof(u4)));
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void daload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u8* array = array_info->arrayAddress;
    
    u8 value = array[index];
    
    u4 valor_numerico_high = value >> 32;
    u4 valor_numerico_low = (u4) value;
    
    pushInOperandStack(environment->thread, valor_numerico_low);
    pushInOperandStack(environment->thread, valor_numerico_high);
}


//--------------------------------------------------------------------------------------------------
void aaload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    //Verificacao de erro de acesso de indice
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u4* array = array_info->arrayAddress;
    
    u4 valor_numerico = array[index];
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void baload(Environment* environment){
    
    int valor_numerico;
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    // Se o valor no componente do vetor for do tipo byte
    if (array_info->atype == T_BYTE) {
        
        // O valor eh estendido com sinal
        valor_numerico = *((char*)((array_info->arrayAddress)+index));
        
    }
    // Se o valor no componente do vetor for do tipo boolean
    else if (array_info->atype == T_BOOLEAN) {
        
        // O valor eh estendido sem sinal
        valor_numerico = *((u1*)((array_info->arrayAddress)+index));
        
    }
    
    pushInOperandStack(environment->thread, valor_numerico);
}


//--------------------------------------------------------------------------------------------------
void caload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u4 valor_numerico_zero_extend = *((u1*)((array_info->arrayAddress)+index));
    
    pushInOperandStack(environment->thread, valor_numerico_zero_extend);
}


//--------------------------------------------------------------------------------------------------
void saload(Environment* environment){
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    int valor_numerico_signal_extend = *((signed short*)((array_info->arrayAddress)+index*sizeof(u2)));
    
    pushInOperandStack(environment->thread, valor_numerico_signal_extend);
}


//--------------------------------------------------------------------------------------------------
void istore(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[index_argument] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void lstore(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[index_argument] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[index_argument+1] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void fstore(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[index_argument] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void dstore(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[index_argument] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[index_argument+1] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void astore(Environment* environment){
    
    environment->thread->PC++;
    u1 index_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[index_argument] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void istore_0(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[0] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void istore_1(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void istore_2(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void istore_3(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void lstore_0(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[0] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void lstore_1(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void lstore_2(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void lstore_3(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[4] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void fstore_0(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[0] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void fstore_1(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void fstore_2(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void fstore_3(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void dstore_0(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[0] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void dstore_1(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void dstore_2(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void dstore_3(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico_high;
    environment->thread->vmStack->top->localVariablesVector[4] = valor_numerico_low;
}


//--------------------------------------------------------------------------------------------------
void astore_0(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[0] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void astore_1(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[1] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void astore_2(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[2] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void astore_3(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    environment->thread->vmStack->top->localVariablesVector[3] = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void iastore(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    *((u4*)((array_info->arrayAddress)+index * sizeof(u4))) = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void lastore(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u8 value = valor_numerico_high;
    value = value<<32 | valor_numerico_low;
    
    u8* array = array_info->arrayAddress;
    
    array[index] = value;
}


//--------------------------------------------------------------------------------------------------
void fastore(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    *((u4*)((array_info->arrayAddress) + index * sizeof(u4))) = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void dastore(Environment* environment){
    
    u4 valor_numerico_high = popFromOperandStack(environment->thread);
    u4 valor_numerico_low = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u8 value = valor_numerico_high;
    value = value<<32 | valor_numerico_low;
    
    u8* array = array_info->arrayAddress;
    
    array[index] = value;
}


//--------------------------------------------------------------------------------------------------
void aastore(Environment* environment){
    
    u4 valor_numerico = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    //TODO: Otherwise, if arrayref is not null and the actual type of value is not assignment compatible (§2.6.7) with the actual type of the components of the array, aastore throws an ArrayStoreException.
    
    *((u4*)((array_info->arrayAddress)+ index * sizeof(u4))) = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void bastore(Environment* environment){
    
    u1 valor_numerico;
    
    u4 valor_numerico_int = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    // Se componentes do vetor forem do tipo byte
    if (array_info->atype == T_BYTE) {
        
        // O int value eh truncado para byte
        valor_numerico = valor_numerico_int;
        
    }
    // Se componentes do vetor forem do tipo boolean
    else if (array_info->atype == T_BOOLEAN) {
        
        // O int value eh truncado para o seu bit de ordem mais baixa e estendido sem sinal
        valor_numerico = (u1)(valor_numerico_int & 0x1);
        
    }
    
    *((u1*)((array_info->arrayAddress)+index)) = valor_numerico;
}


//--------------------------------------------------------------------------------------------------
void castore(Environment* environment){
    
    u4 valor_numerico_int = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u1 valor_numerico_char = valor_numerico_int;
    
    *((u1*)((array_info->arrayAddress)+index)) = valor_numerico_char;
}


//--------------------------------------------------------------------------------------------------
void sastore(Environment* environment){
    
    u4 valor_numerico_int = popFromOperandStack(environment->thread);
    
    u4 index = popFromOperandStack(environment->thread);
    
    JavaArray* array_info = (JavaArray*) popFromOperandStack(environment->thread);
    
    if (array_info->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    if (index > array_info->count) JVMThrow(ArrayIndexOutOfBoundsException, environment);
    
    u2 valor_numerico_short = valor_numerico_int;
    
    *((u2*)((array_info->arrayAddress)+ index * sizeof(u2))) = valor_numerico_short;
}


//--------------------------------------------------------------------------------------------------
void wide(Environment* environment){
    
    environment->thread->PC++;
    u1 opcode_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                              environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                              ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 indexbyte1_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                               environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                               ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 indexbyte2_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                               environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                               ,environment->thread->PC);
    
    u2 index_result = (indexbyte1_argument << 8) | indexbyte2_argument;
    
    
    // PRIMEIRO FORMATO
    if (opcode_argument == OP_iload || opcode_argument == OP_fload || opcode_argument == OP_aload) {
        
        u4 valor_numerico = environment->thread->vmStack->top->localVariablesVector[index_result];
        
        pushInOperandStack(environment->thread, valor_numerico);
    }
    else if (opcode_argument == OP_istore || opcode_argument == OP_fstore || opcode_argument == OP_astore){
        
        u4 valor_numerico = popFromOperandStack(environment->thread);
        
        environment->thread->vmStack->top->localVariablesVector[index_result] = valor_numerico;
    }
    else if (opcode_argument == OP_ret) {
        environment->thread->PC = environment->thread->vmStack->top->localVariablesVector[index_result];
    }
    else if (opcode_argument == OP_lload || opcode_argument == OP_dload) {
        
        u4 valor_numerico_high = environment->thread->vmStack->top->localVariablesVector[index_result];
        u4 valor_numerico_low = environment->thread->vmStack->top->localVariablesVector[index_result+1];
        
        pushInOperandStack(environment->thread, valor_numerico_low);
        pushInOperandStack(environment->thread, valor_numerico_high);
    }
    else if (opcode_argument == OP_lstore || opcode_argument == OP_dstore) {
        
        u4 valor_numerico_high = popFromOperandStack(environment->thread);
        u4 valor_numerico_low = popFromOperandStack(environment->thread);
        
        environment->thread->vmStack->top->localVariablesVector[index_result] = valor_numerico_high;
        environment->thread->vmStack->top->localVariablesVector[index_result+1] = valor_numerico_low;
    }
    
    // SEGUNDO FORMATO
    else if (opcode_argument == OP_iinc) {
        
        environment->thread->PC++;
        u1 constbyte1_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                       environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                       ,environment->thread->PC);
        
        environment->thread->PC++;
        u1 constbyte2_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                       environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                       ,environment->thread->PC);
        
        int constbyte_result = (int)((constbyte1_argument << 8) | constbyte2_argument);
        
        u4 index_forma2 = (u4)(index_result + constbyte_result);
        
        environment->thread->PC++;
        
        u1 Const = getByteCodeFromMethod(environment->thread->vmStack->top->method_info, environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread->PC);
        
        //environment->thread->PC++;
        
        char constSemSinal = (char) Const;
        
        environment->thread->vmStack->top->localVariablesVector[index_forma2] += constSemSinal;
    }
}


//--------------------------------------------------------------------------------------------------
void Dup(Environment* environment){

    u4 value = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value);
    pushInOperandStack(environment->thread, value);
}


//--------------------------------------------------------------------------------------------------
void dup_x1(Environment* environment){
    
    u4 value1 = popFromOperandStack(environment->thread);
    u4 value2 = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value1);
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
}


//--------------------------------------------------------------------------------------------------
void dup_x2(Environment* environment){
    
    u4 value1 = popFromOperandStack(environment->thread);
    u4 value2 = popFromOperandStack(environment->thread);
    u4 value3 = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value1);
    pushInOperandStack(environment->thread, value3);
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
}


//--------------------------------------------------------------------------------------------------
void Dup2(Environment* environment){
    
    u4 value1 = popFromOperandStack(environment->thread);
    u4 value2 = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
    
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
}


//--------------------------------------------------------------------------------------------------
void dup2_x1(Environment* environment){
    
    u4 value1 = popFromOperandStack(environment->thread);
    u4 value2 = popFromOperandStack(environment->thread);
    u4 value3 = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
    pushInOperandStack(environment->thread, value3);
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
}


//--------------------------------------------------------------------------------------------------
void dup2_x2(Environment* environment){
    
    u4 value1 = popFromOperandStack(environment->thread);
    u4 value2 = popFromOperandStack(environment->thread);
    u4 value3 = popFromOperandStack(environment->thread);
    u4 value4 = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
    pushInOperandStack(environment->thread, value4);
    pushInOperandStack(environment->thread, value3);
    pushInOperandStack(environment->thread, value2);
    pushInOperandStack(environment->thread, value1);
}


//--------------------------------------------------------------------------------------------------
void pop(Environment* environment){
    popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
void pop2(Environment* environment){
    popFromOperandStack(environment->thread);
    popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
void swap(Environment* environment){
    
    u4 value1 = popFromOperandStack(environment->thread);
    u4 value2 = popFromOperandStack(environment->thread);
    
    pushInOperandStack(environment->thread, value1);
    pushInOperandStack(environment->thread, value2);
}


