//#################################################################################################
/*! \file M_INSTCONVERSION.c
 *
 *  \brief Modulo que contem as instrucoes de conversao.
 *
 *  Modulo responsavel por implementar as instrucoes de conversao entre tipos na JVM
 */
//##################################################################################################

#define M_INSTCONVERSION_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/ExecutionEngine/I_INSTCONVERSION.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

void i2l(Environment* environment) {
	int64_t aux1;
	int32_t aux3;
	u4 aux2;

	aux3 = (signed) popFromOperandStack(environment->thread);
	aux1 = aux3;
	//CORRECAO: PRIMERIO O LOW
  aux2 = aux1 & SHIFT_MASK_UNSI;
	pushInOperandStack(environment->thread,aux2);

	//CORRECAO: DEPOIS O HIGH
  aux2 = aux1 >> 32;
	pushInOperandStack(environment->thread, aux2);
}

void i2f(Environment* environment) {
	u4 *aux1;
	int32_t aux3;
	float aux2;

	aux3 = (signed) popFromOperandStack(environment->thread);
	aux2 = (float) aux3;
	aux1 = malloc(sizeof(u4));


	memcpy(aux1, &aux2, sizeof(u4));

	pushInOperandStack(environment->thread,*aux1);
}


void i2d(Environment* environment) {
	int64_t *aux1;
	int32_t aux4;
	double aux2;
	u4 aux3;

	aux1 = malloc(sizeof(int64_t));
	aux4 = (signed) popFromOperandStack(environment->thread);
	aux2 = (double) aux4;


	memcpy(aux1, &aux2, sizeof(int64_t));

	aux3 = *aux1 & SHIFT_MASK_UNSI;
	pushInOperandStack(environment->thread,aux3);

	aux3 = *aux1 >> 32;
	pushInOperandStack(environment->thread,aux3);

}

void l2i(Environment* environment) {
	u4 aux1;

	// Remove o high do operand stack
	popFromOperandStack(environment->thread);

	// Pega o low do operand stack
	aux1 = (u4) popFromOperandStack(environment->thread);

	// Dá push do valor no operand stack
	pushInOperandStack(environment->thread,aux1);
}


void l2f(Environment* environment) {
	int64_t aux1, aux2;
	float aux3;
	u4 *u4aux;

	// Pega o high do operand stack
	aux1 = popFromOperandStack(environment->thread);
	// Pega o low do operand stack
	aux2 = popFromOperandStack(environment->thread);

	// Move o high com operação de 32 bits à esquerda e adiciona o low
	aux1 = aux1 << 32;
	aux1 = aux2;

	// Converte a junçao do high-low para um float
	aux3 = (float) aux1;
	u4aux = malloc(sizeof(u4));
	memcpy(u4aux, &aux3, sizeof(u4));

	// Dá push do valor no operand stack
	pushInOperandStack(environment->thread,*u4aux);
}


void l2d(Environment* environment) {
	int64_t aux1, *aux3, aux4;
	double aux2;
	u4 u4aux;

	// Pega o high do operand stack
	aux1 = popFromOperandStack(environment->thread);
	// Pega o low do operand stack
	aux4 = popFromOperandStack(environment->thread);

	// Move o high com operação de 32 bits à esquerda e adiciona o low
	aux1 = aux1 << 32;
	aux1 |= aux4;

	// Converte a junçao do high-low para um double
	aux2 = (double) aux1;
	aux3 = malloc(sizeof(int64_t));
	memcpy(aux3, &aux2, sizeof(int64_t));

	// Dá push do low no operand stack
	u4aux = *aux3 & SHIFT_MASK_UNSI;
	pushInOperandStack(environment->thread,u4aux);

	// Dá push do high no operand stack
	u4aux = *aux3 >> 32;
	pushInOperandStack(environment->thread,u4aux);
}

void f2i(Environment* environment) {
	u4 aux2;
	float aux1;
	int32_t aux3;

	aux2 = popFromOperandStack(environment->thread);
	memcpy(&aux1, &aux2, sizeof(float));
	aux3 = (int32_t) aux1;
	pushInOperandStack(environment->thread,aux3);
}

void f2l(Environment* environment) {
	int64_t aux1;
	u4 aux2;
	float aux3;

	aux1 = popFromOperandStack(environment->thread);

	aux2 = aux1 & SHIFT_MASK_UNSI;
	memcpy(&aux3, &aux2, sizeof(float));
	pushInOperandStack(environment->thread,aux3);

	aux2 = aux1 >> 32;
	memcpy(&aux3, &aux2, sizeof(float));
	pushInOperandStack(environment->thread,aux3);
}

void f2d(Environment* environment) {
	double aux4;
	float *aux2;
	u4 aux1, aux3;
	u8 aux5;

	aux1 = popFromOperandStack(environment->thread);
	aux2 = malloc(sizeof(float));

	memcpy(aux2, &aux1, sizeof(float));
	aux4 = *aux2;
	memcpy(&aux5, &aux4, sizeof(u8));

	aux3 = aux5 & 0xffffffff;
	pushInOperandStack(environment->thread,aux3);
	aux3 = aux5 >> 32;
	pushInOperandStack(environment->thread,aux3);
}

void d2i(Environment* environment) {
	int64_t aux1, aux4;
	double *aux2;
	int32_t aux3;

	aux1 = popFromOperandStack(environment->thread);
	aux4 = popFromOperandStack(environment->thread);

	aux1 = aux1 << 32;
	aux1 |= aux4;
	aux2 = malloc(sizeof(double));

	memcpy(aux2, &aux1, sizeof(double));
	aux3 = (int32_t) *aux2;
	pushInOperandStack(environment->thread,aux3);
}

void d2l(Environment* environment) {
	int64_t aux1, aux3;
	double *aux2;
	u4 aux0;

	aux1 = popFromOperandStack(environment->thread);
	aux3 = popFromOperandStack(environment->thread);
	aux1 = aux1 << 32;
	aux1 |= aux3;
	aux2 = malloc(sizeof(double));

	memcpy(aux2, &aux1, sizeof(double));
	aux1 = (int64_t) *aux2;
	aux0 = aux1 & SHIFT_MASK_UNSI;
	pushInOperandStack(environment->thread,aux0);
	aux0 = aux1 >> 32;
	pushInOperandStack(environment->thread,aux0);
}

void d2f(Environment* environment) {
	int64_t aux1, aux4;
	double *aux2;
	float aux3;
	u4 *aux0;

	aux1 = popFromOperandStack(environment->thread);
	aux4 = popFromOperandStack(environment->thread);
	aux1 = aux1 << 32;
	aux1 |= aux4;
	aux2 = malloc(sizeof(double));

	memcpy(aux2, &aux1, sizeof(double));
	aux3 = (float) *aux2;
	aux0 = malloc(sizeof(u4));

	memcpy(aux0, &aux3, sizeof(u4));
	pushInOperandStack(environment->thread,*aux0);

}

void i2b(Environment* environment) {
	char aux1;

	aux1 = (char) popFromOperandStack(environment->thread);
	pushInOperandStack(environment->thread,(int32_t) aux1);

}

void i2c(Environment* environment) {
	char aux1;

	aux1 = (char) popFromOperandStack(environment->thread);
	pushInOperandStack(environment->thread,(int32_t) aux1);

}

void i2s(Environment* environment) {
	short aux1;

	aux1 = (short) popFromOperandStack(environment->thread);
	pushInOperandStack(environment->thread,(int32_t) aux1);

}
