//#################################################################################################
/*! \file M_INSTLOGARITH.c
 *
 *  \brief Modulo que contem as instrucoes de retorno.
 *
 *  Modulo responsavel por implementar as instrucoes que lidam com retorno de valores
 */
//##################################################################################################

#define M_INSTRETURN_SERV

#include <stdio.h>
#include <stdlib.h>

#include "../../include/ExecutionEngine/I_INSTRETURN.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

void ireturn(Environment* environment){
	u4 conteudo;
	Frame *tmp;

	tmp = getCurrentFrame(environment->environment->thread);
	conteudo = popFromOperandStack(environment->thread);
	popFrame(environment->thread);

	pushInOperandStack(environment->thread, conteudo);
}

void lreturn(Environment* environment){
	u4 conteudo1, conteudo2;
	Frame *tmp;

	tmp = getCurrentFrame(environment->thread);
	conteudo1 = popFromOperandStack(environment->thread);
	conteudo2 = popFromOperandStack(environment->thread);
	popFrame(environment->thread);

	pushInOperandStack(environment->thread, conteudo2);
	pushInOperandStack(environment->thread, conteudo1);
}

void freturn(Environment* environment){
	u4 conteudo;
	Frame *tmp;

	tmp = getCurrentFrame(environment->thread);
	conteudo = popFromOperandStack(environment->thread);
	popFrame(environment->thread);

	pushInOperandStack(environment->thread, conteudo);
}

void dreturn(Environment* environment){
	u4 conteudo1, conteudo2;
	Frame *tmp;

	tmp = getCurrentFrame(environment->thread);
	conteudo1 = popFromOperandStack(environment->thread);
	conteudo2 = popFromOperandStack(environment->thread);
	popFrame(environment->thread);

	pushInOperandStack(environment->thread, conteudo2);
	pushInOperandStack(environment->thread, conteudo1);
}

void areturn(Environment* environment){
	u4 conteudo;
	Frame *tmp;

	tmp = getCurrentFrame(environment->thread);
	conteudo = popFromOperandStack(environment->thread);
	popFrame(environment->thread);

	pushInOperandStack(environment->thread, conteudo);
}

void return_(Environment* environment){
	Frame *tmp;
	tmp = getCurrentFrame(environment->thread);
	popFrame(environment->thread);
}