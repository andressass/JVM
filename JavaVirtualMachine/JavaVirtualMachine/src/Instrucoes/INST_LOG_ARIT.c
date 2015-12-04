//#################################################################################################
/*! \file INST_LOG_ARIT.c
 *
 *  \brief Modulo que contem as instrucoes logicos aritmeticas.
 *
 *  Modulo responsavel por implementar as instrucoes de cunho logico e aritmetico
 */
//##################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../include/Instrucoes/INST_LOG_ARIT.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

void iadd(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 soma = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    soma = operando1 + operando2;
    
    pushInOperandStack(thread, soma);
    
}


void ladd(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long soma64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    soma64 = operando1_64 + operando2_64;
    
    operandoPilha1 = (u4) ((soma64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) soma64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void fadd(Thread *thread){
    
    float operando1 = 0;
    float operando2 = 0;
    float soma = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 somaPilha = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    soma = operando1 + operando2;
    
    memcpy(&somaPilha, &soma, sizeof(u4));
    
    pushInOperandStack(thread, somaPilha);
    
}

void dadd(Thread *thread){
    
    double operando1 = 0;
    double operando2 = 0;
    double soma = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    long long operandoSoma1;
    long long operandoSoma2;
    long long somaLong;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoSoma1 = (long long) operandoPilha2;
    operandoSoma1 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoSoma1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoSoma2 = (long long) operandoPilha2;
    operandoSoma2 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoSoma2, sizeof(double));
    
    soma = operando1 + operando2;
    
    memcpy(&somaLong, &soma, sizeof(long long));
    
    operandoPilha1 = (u4) ((somaLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) somaLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
}

void isub(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 sub = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    sub = operando2 - operando1;
    
    pushInOperandStack(thread, sub);
    
}

void lsub(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long sub64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    sub64 = operando2_64 - operando1_64;
    
    operandoPilha1 = (u4) ((sub64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) sub64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void fsub(Thread *thread){
    
    float operando1 = 0;
    float operando2 = 0;
    float sub = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 subPilha = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    sub = operando2 - operando1;
    
    memcpy(&subPilha, &sub, sizeof(u4));
    
    pushInOperandStack(thread, subPilha);
    
}

void dsub(Thread *thread){
    
    double operando1 = 0;
    double operando2 = 0;
    double sub = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    long long operandoSub1;
    long long operandoSub2;
    long long subLong;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoSub1 = (long long) operandoPilha2;
    operandoSub1 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoSub1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoSub2 = (long long) operandoPilha2;
    operandoSub2 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoSub2, sizeof(double));
    
    sub = operando2 - operando1;
    
    memcpy(&subLong, &sub, sizeof(long long));
    
    operandoPilha1 = (u4) ((subLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) subLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
}

void imul(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 mul = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    mul = operando2 * operando1;
    
    pushInOperandStack(thread, mul);
    
}

void lmul(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long mul64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    mul64 = operando2_64 * operando1_64;
    
    operandoPilha1 = (u4) ((mul64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) mul64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void fmul(Thread *thread){
    
    float operando1 = 0;
    float operando2 = 0;
    float mul = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 mulPilha = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    mul = operando2 * operando1;
    
    memcpy(&mulPilha, &mul, sizeof(u4));
    
    pushInOperandStack(thread, mulPilha);
    
}

void dmul(Thread *thread){
    
    double operando1 = 0;
    double operando2 = 0;
    double mul = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    long long operandoMul1;
    long long operandoMul2;
    long long mulLong;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoMul1 = (long long) operandoPilha2;
    operandoMul1 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoMul1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoMul2 = (long long) operandoPilha2;
    operandoMul2 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoMul2, sizeof(double));
    
    mul = operando2 * operando1;
    
    memcpy(&mulLong, &mul, sizeof(long long));
    
    operandoPilha1 = (u4) ((mulLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) mulLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
}

void idiv(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 div = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    if (operando1 == 0) {
        printf("ERRO nao pode ser feita divisao por zero\n");
    }else{
        div = operando2 / operando1;
    }
    
    pushInOperandStack(thread, div);
    
}

void Ldiv(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long div64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    if (operando1_64 == 0) {
        printf("ERRO nao pode ser feita divisao por zero/n");
    }else{
        div64 = operando2_64 / operando1_64;
    }
    operandoPilha1 = (u4) ((div64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) div64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void fdiv(Thread *thread){
    
    float operando1 = 0;
    float operando2 = 0;
    float div = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 divPilha = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    if (operando1 == 0) {
        printf("ERRO nao pode ser feita divisao por zero/n");
    }else{
        div = operando2 / operando1;
    }
    memcpy(&divPilha, &div, sizeof(u4));
    
    pushInOperandStack(thread, divPilha);
    
}

void ddiv(Thread *thread){
    
    double operando1 = 0;
    double operando2 = 0;
    double div = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    long long operandoDiv1;
    long long operandoDiv2;
    long long divLong;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoDiv1 = (long long) operandoPilha2;
    operandoDiv1 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoDiv1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoDiv2 = (long long) operandoPilha2;
    operandoDiv2 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoDiv2, sizeof(double));
    
    if(operando1 == 0){
        printf("ERRO nao pode ser feita divisao por zero/n");
    }else{
        div = operando2 / operando1;
    }
    memcpy(&divLong, &div, sizeof(long long));
    
    operandoPilha1 = (u4) ((divLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) divLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
}

void irem(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 rem = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    rem = operando2 % operando1;
    
    pushInOperandStack(thread, rem);
    
}

void lrem(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long rem64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    rem64 = operando2_64 % operando1_64;
    
    operandoPilha1 = (u4) ((rem64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) rem64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void frem(Thread *thread){
    
    float operando1 = 0;
    float operando2 = 0;
    float rem = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 remPilha = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    rem = fmodf(operando2, operando1);
    
    memcpy(&remPilha, &rem, sizeof(u4));
    
    pushInOperandStack(thread, remPilha);
    
}

void Drem(Thread *thread){
    
    double operando1 = 0;
    double operando2 = 0;
    double rem = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    long long operandoRem1;
    long long operandoRem2;
    long long remLong;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoRem1 = (long long) operandoPilha2;
    operandoRem1 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoRem1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoRem2 = (long long) operandoPilha2;
    operandoRem2 = (long long) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoRem2, sizeof(double));
    
    rem = fmod(operando2, operando1);
    
    memcpy(&remLong, &rem, sizeof(long long));
    
    operandoPilha1 = (u4) ((remLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) remLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
}

void ineg(Thread *thread){
    
    u4 operando = 0;
    u4 neg = 0;
    
    operando = popFromOperandStack(thread);
    
    neg = ~operando + 1;
    
    pushInOperandStack(thread, neg);
    
}

void lneg(Thread *thread){
    
    long long operando_64 = 0;
    long long neg64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando_64 = (long long) operandoPilha2;
    operando_64 = (long long) operandoPilha1 << 32;
    
    neg64 = ~operando_64 + 1;
    
    operandoPilha1 = (u4) ((neg64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) neg64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void fneg(Thread *thread){
    
    float operando = 0;
    float neg = 0;
    
    u4 operandoPilha1 = 0;
    u4 negPilha = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    
    memcpy(&operando, &operandoPilha1, sizeof(float));
    
    neg = -(operando);
    
    memcpy(&negPilha, &neg, sizeof(u4));
    
    pushInOperandStack(thread, negPilha);
    
}

void dneg(Thread *thread){
    
    double operando = 0;
    double neg = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    long long operandoNeg;
    long long negLong;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operandoNeg = (long long) operandoPilha2;
    operandoNeg = (long long) operandoPilha1 << 32;
    
    memcpy(&operando, &operandoNeg, sizeof(double));
    
    neg = -(operando);
    
    memcpy(&negLong, &neg, sizeof(long long));
    
    operandoPilha1 = (u4) ((negLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) negLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
}

void ishl(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 shl = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    operando1 = operando1 & SHIFT_MASK_32;
    shl = operando2 << operando1;
    
    pushInOperandStack(thread, shl);
    
}

void lshl(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long shl64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    operando1_64 = operando1_64 & SHIFT_MASK_32;
    shl64 = operando2_64 << operando1_64;
    
    operandoPilha1 = (u4) ((shl64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) shl64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void ishr(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 shr = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    operando1 = operando1 & SHIFT_MASK_32;
    shr = operando2 >> operando1;
    
    pushInOperandStack(thread, shr);
    
}

void lshr(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long shr64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    operando1_64 = operando1_64 & SHIFT_MASK_32;
    shr64 = operando2_64 >> operando1_64;
    
    operandoPilha1 = (u4) ((shr64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) shr64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void iushr(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 shr = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    operando1 = operando1 & SHIFT_MASK_32;
    
    if(operando2 > 0){
        shr = operando2 >> operando1;
    }else{
        //copiado da especificacao
        shr = ((operando2 >> operando1) - (2 << ~operando1));
    }
    
    pushInOperandStack(thread, shr);
    
}

void lushr(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long shr64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    operando1_64 = operando1_64 & SHIFT_MASK_32;
    
    if (operando1_64 > 0) {
        shr64 = operando2_64 >> operando1_64;
    }else{
        shr64 = ((operando2_64 >> operando1_64) - (2 << ~operando1_64));
    }
    operandoPilha1 = (u4) ((shr64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) shr64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void iand(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 and = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    and = operando2 & operando1;
    
    pushInOperandStack(thread, and);
    
}

void land(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long and64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    and64 = operando2_64 & operando1_64;
    
    operandoPilha1 = (u4) ((and64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) and64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void ior(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 or = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    or = operando2 | operando1;
    
    pushInOperandStack(thread, or);
    
}

void lor(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long or64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    or64 = operando2_64 | operando1_64;
    
    operandoPilha1 = (u4) ((or64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) or64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void ixor(Thread *thread){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 xor = 0;
    
    operando1 = popFromOperandStack(thread);
    
    operando2 = popFromOperandStack(thread);
    
    xor = operando2 ^ operando1;
    
    pushInOperandStack(thread, xor);
    
}

void lxor(Thread *thread){
    
    long long operando1_64 = 0;
    long long operando2_64 = 0;
    long long xor64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando1_64 = (long long) operandoPilha2;
    operando1_64 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(thread);
    operandoPilha2 = popFromOperandStack(thread);
    
    operando2_64 = (long long) operandoPilha2;
    operando2_64 = (long long) operandoPilha1 << 32;
    
    xor64 = operando2_64 ^ operando1_64;
    
    operandoPilha1 = (u4) ((xor64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) xor64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(thread, operandoPilha2);
    pushInOperandStack(thread, operandoPilha1);
    
}

void iinc(Thread *thread){
    
    u4 operando1 = 0;
    u4 inc = 0;
    
    operando1 = popFromOperandStack(thread);
    
    inc = operando1++;
    
    pushInOperandStack(thread, inc);
    
}