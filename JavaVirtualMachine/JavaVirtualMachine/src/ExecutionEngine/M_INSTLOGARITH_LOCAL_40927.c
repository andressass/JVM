//#################################################################################################
/*! \file M_INSTLOGARITH.c
 *
 *  \brief Modulo que contem as instrucoes logicos aritmeticas.
 *
 *  Modulo responsavel por implementar as instrucoes de cunho logico e aritmetico
 */
//##################################################################################################

#define INSTLOGARITH_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../include/ExecutionEngine/I_INSTLOGARITH.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

void iadd(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 soma = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    soma = operando1 + operando2;
    
    pushInOperandStack(environment->thread, soma);
    
}


void ladd(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 soma64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha1;
    operando1_64 = operando1_64 << 32 | operandoPilha2;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha1;
    operando1_64 = operando1_64 << 32 | operandoPilha2;
    
    soma64 = operando1_64 + operando2_64;
    
    operandoPilha1 = (u4) ((soma64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) soma64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void fadd(Environment* environment){
    
    float operando1 = 0;
    float operando2 = 0;
    float soma = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 somaPilha = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    soma = operando1 + operando2;
    
    memcpy(&somaPilha, &soma, sizeof(u4));
    
    pushInOperandStack(environment->thread, somaPilha);
    
}

void dadd(Environment* environment){
    
    double operando1 = 0;
    double operando2 = 0;
    double soma = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    u8 operandoSoma1;
    u8 operandoSoma2;
    u8 somaLong;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoSoma1 = (u8) operandoPilha2;
    operandoSoma1 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoSoma1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoSoma2 = (u8) operandoPilha2;
    operandoSoma2 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoSoma2, sizeof(double));
    
    soma = operando1 + operando2;
    
    memcpy(&somaLong, &soma, sizeof(u8));
    
    operandoPilha1 = (u4) ((somaLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) somaLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}

void isub(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 sub = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    sub = operando2 - operando1;
    
    pushInOperandStack(environment->thread, sub);
    
}

void lsub(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 sub64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    sub64 = operando2_64 - operando1_64;
    
    operandoPilha1 = (u4) ((sub64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) sub64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void fsub(Environment* environment){
    
    float operando1 = 0;
    float operando2 = 0;
    float sub = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 subPilha = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    sub = operando2 - operando1;
    
    memcpy(&subPilha, &sub, sizeof(u4));
    
    pushInOperandStack(environment->thread, subPilha);
    
}

void dsub(Environment* environment){
    
    double operando1 = 0;
    double operando2 = 0;
    double sub = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    u8 operandoSub1;
    u8 operandoSub2;
    u8 subLong;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoSub1 = (u8) operandoPilha2;
    operandoSub1 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoSub1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoSub2 = (u8) operandoPilha2;
    operandoSub2 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoSub2, sizeof(double));
    
    sub = operando2 - operando1;
    
    memcpy(&subLong, &sub, sizeof(u8));
    
    operandoPilha1 = (u4) ((subLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) subLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}

void imul(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 mul = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    mul = operando2 * operando1;
    
    pushInOperandStack(environment->thread, mul);
    
}

void lmul(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 mul64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    mul64 = operando2_64 * operando1_64;
    
    operandoPilha1 = (u4) ((mul64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) mul64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void fmul(Environment* environment){
    
    float operando1 = 0;
    float operando2 = 0;
    float mul = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 mulPilha = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    mul = operando2 * operando1;
    
    memcpy(&mulPilha, &mul, sizeof(u4));
    
    pushInOperandStack(environment->thread, mulPilha);
    
}

void dmul(Environment* environment){
    
    double operando1 = 0;
    double operando2 = 0;
    double mul = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    u8 operandoMul1;
    u8 operandoMul2;
    u8 mulLong;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoMul1 = (u8) operandoPilha2;
    operandoMul1 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoMul1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoMul2 = (u8) operandoPilha2;
    operandoMul2 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoMul2, sizeof(double));
    
    mul = operando2 * operando1;
    
    memcpy(&mulLong, &mul, sizeof(u8));
    
    operandoPilha1 = (u4) ((mulLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) mulLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}

void idiv(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 div = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    if (operando1 == 0) {
        printf("ERRO nao pode ser feita divisao por zero\n");
    }else{
        div = operando2 / operando1;
    }
    
    pushInOperandStack(environment->thread, div);
    
}

void Ldiv(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 div64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    if (operando1_64 == 0) {
        printf("ERRO nao pode ser feita divisao por zero/n");
    }else{
        div64 = operando2_64 / operando1_64;
    }
    operandoPilha1 = (u4) ((div64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) div64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void fdiv(Environment* environment){
    
    float operando1 = 0;
    float operando2 = 0;
    float div = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 divPilha = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    if (operando1 == 0) {
        printf("ERRO nao pode ser feita divisao por zero/n");
    }else{
        div = operando2 / operando1;
    }
    memcpy(&divPilha, &div, sizeof(u4));
    
    pushInOperandStack(environment->thread, divPilha);
    
}

void ddiv(Environment* environment){
    
    double operando1 = 0;
    double operando2 = 0;
    double div = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    u8 operandoDiv1;
    u8 operandoDiv2;
    u8 divLong;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoDiv1 = (u8) operandoPilha2;
    operandoDiv1 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoDiv1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoDiv2 = (u8) operandoPilha2;
    operandoDiv2 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoDiv2, sizeof(double));
    
    if(operando1 == 0){
        printf("ERRO nao pode ser feita divisao por zero/n");
    }else{
        div = operando2 / operando1;
    }
    memcpy(&divLong, &div, sizeof(u8));
    
    operandoPilha1 = (u4) ((divLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) divLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}

void irem(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 rem = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    rem = operando2 % operando1;
    
    pushInOperandStack(environment->thread, rem);
    
}

void lrem(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 rem64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    rem64 = operando2_64 % operando1_64;
    
    operandoPilha1 = (u4) ((rem64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) rem64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void frem(Environment* environment){
    
    float operando1 = 0;
    float operando2 = 0;
    float rem = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 remPilha = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    memcpy(&operando1, &operandoPilha1, sizeof(float));
    memcpy(&operando2, &operandoPilha2, sizeof(float));
    
    rem = fmodf(operando2, operando1);
    
    memcpy(&remPilha, &rem, sizeof(u4));
    
    pushInOperandStack(environment->thread, remPilha);
    
}

void Drem(Environment* environment){
    
    double operando1 = 0;
    double operando2 = 0;
    double rem = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    u8 operandoRem1;
    u8 operandoRem2;
    u8 remLong;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoRem1 = (u8) operandoPilha2;
    operandoRem1 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando1, &operandoRem1, sizeof(double));
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoRem2 = (u8) operandoPilha2;
    operandoRem2 = (u8) operandoPilha1 << 32;
    
    memcpy(&operando2, &operandoRem2, sizeof(double));
    
    rem = fmod(operando2, operando1);
    
    memcpy(&remLong, &rem, sizeof(u8));
    
    operandoPilha1 = (u4) ((remLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) remLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}

void ineg(Environment* environment){
    
    u4 operando = 0;
    u4 neg = 0;
    
    operando = popFromOperandStack(environment->thread);
    
    neg = ~operando + 1;
    
    pushInOperandStack(environment->thread, neg);
    
}

void lneg(Environment* environment){
    
    u8 operando_64 = 0;
    u8 neg64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando_64 = (u8) operandoPilha2;
    operando_64 = (u8) operandoPilha1 << 32;
    
    neg64 = ~operando_64 + 1;
    
    operandoPilha1 = (u4) ((neg64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) neg64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void fneg(Environment* environment){
    
    float operando = 0;
    float neg = 0;
    
    u4 operandoPilha1 = 0;
    u4 negPilha = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    
    memcpy(&operando, &operandoPilha1, sizeof(float));
    
    neg = -(operando);
    
    memcpy(&negPilha, &neg, sizeof(u4));
    
    pushInOperandStack(environment->thread, negPilha);
    
}

void dneg(Environment* environment){
    
    double operando = 0;
    double neg = 0;
    
    u4 operandoPilha1;
    u4 operandoPilha2;
    
    u8 operandoNeg;
    u8 negLong;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operandoNeg = (u8) operandoPilha2;
    operandoNeg = (u8) operandoPilha1 << 32;
    
    memcpy(&operando, &operandoNeg, sizeof(double));
    
    neg = -(operando);
    
    memcpy(&negLong, &neg, sizeof(u8));
    
    operandoPilha1 = (u4) ((negLong & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) negLong & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
}

void ishl(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 shl = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    operando1 = operando1 & SHIFT_MASK_32;
    shl = operando2 << operando1;
    
    pushInOperandStack(environment->thread, shl);
    
}

void lshl(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 shl64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    operando1_64 = operando1_64 & SHIFT_MASK_32;
    shl64 = operando2_64 << operando1_64;
    
    operandoPilha1 = (u4) ((shl64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) shl64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void ishr(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 shr = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    operando1 = operando1 & SHIFT_MASK_32;
    shr = operando2 >> operando1;
    
    pushInOperandStack(environment->thread, shr);
    
}

void lshr(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 shr64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    operando1_64 = operando1_64 & SHIFT_MASK_32;
    shr64 = operando2_64 >> operando1_64;
    
    operandoPilha1 = (u4) ((shr64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) shr64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void iushr(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 shr = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    operando1 = operando1 & SHIFT_MASK_32;
    
    if(operando2 > 0){
        shr = operando2 >> operando1;
    }else{
        //copiado da especificacao
        shr = ((operando2 >> operando1) - (2 << ~operando1));
    }
    
    pushInOperandStack(environment->thread, shr);
    
}

void lushr(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 shr64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    operando1_64 = operando1_64 & SHIFT_MASK_32;
    
    if (operando1_64 > 0) {
        shr64 = operando2_64 >> operando1_64;
    }else{
        shr64 = ((operando2_64 >> operando1_64) - (2 << ~operando1_64));
    }
    operandoPilha1 = (u4) ((shr64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) shr64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void iand(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 and = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    and = operando2 & operando1;
    
    pushInOperandStack(environment->thread, and);
    
}

void land(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 and64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    and64 = operando2_64 & operando1_64;
    
    operandoPilha1 = (u4) ((and64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) and64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void ior(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 or = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    or = operando2 | operando1;
    
    pushInOperandStack(environment->thread, or);
    
}

void lor(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 or64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    or64 = operando2_64 | operando1_64;
    
    operandoPilha1 = (u4) ((or64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) or64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void ixor(Environment* environment){
    
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 xor = 0;
    
    operando1 = popFromOperandStack(environment->thread);
    
    operando2 = popFromOperandStack(environment->thread);
    
    xor = operando2 ^ operando1;
    
    pushInOperandStack(environment->thread, xor);
    
}

void lxor(Environment* environment){
    
    u8 operando1_64 = 0;
    u8 operando2_64 = 0;
    u8 xor64 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1_64 = (u8) operandoPilha2;
    operando1_64 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2_64 = (u8) operandoPilha2;
    operando2_64 = (u8) operandoPilha1 << 32;
    
    xor64 = operando2_64 ^ operando1_64;
    
    operandoPilha1 = (u4) ((xor64 & 0xFFFFFFFF00000000) >> 32);
    operandoPilha2 = (u4) xor64 & 0x00000000FFFFFFFF;
    
    pushInOperandStack(environment->thread, operandoPilha2);
    pushInOperandStack(environment->thread, operandoPilha1);
    
}

void iinc(Environment* environment){
    u1 index;
    u1 Const;
    
    environment->thread->PC++;
    
    index = getByteCodeFromMethod(environment->thread->vmStack->top->method_info, environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread->PC);
    
    environment->thread->PC++;
    
    Const = getByteCodeFromMethod(environment->thread->vmStack->top->method_info, environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread->PC);
    
    //environment->thread->PC++;
    
    char constSemSinal = (char) Const;
    
    environment->thread->vmStack->top->localVariablesVector[index] += constSemSinal;
}