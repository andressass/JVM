//#################################################################################################
/*! \file INST_LOG_ARIT.h
 *
 *  \brief Instrucoes Logico Aritmeticas.
 *
 * Arquivo com o escopo das instrucoes logico aritmeticas
 */
//##################################################################################################

#ifndef INST_LOG_ARIT_h
#define INST_LOG_ARIT_h

#include "../../include/Estruturas/E_JVM.h"

#define SHIFT_MASK_32 0x1F
#define SHIFT_MASK_64 0x3F

/*!
 *  Instrucao para soma de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void iadd(Thread*);

/*!
 *  Instrucao para soma de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void ladd(Thread*);
/*!
 *  Instrucao para soma de float de 32 bits
 *  \param Thread
 *  \return void
 */
void fadd(Thread*);
/*!
 *  Instrucao para soma de double de 32 bits
 *  \param Thread
 *  \return void
 */
void dadd(Thread*);
/*!
 *  Instrucao para subtracao de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void isub(Thread*);
/*!
 *  Instrucao para subtracao de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lsub(Thread*);
/*!
 *  Instrucao para subtracao de float de 32 bits
 *  \param Thread
 *  \return void
 */
void fsub(Thread*);
/*!
 *  Instrucao para subtracao de double de 64 bits
 *  \param Thread
 *  \return void
 */
void dsub(Thread*);
/*!
 *  Instrucao para multiplicacao de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void imul(Thread*);
/*!
 *  Instrucao para multiplicacao de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lmul(Thread*);
/*!
 *  Instrucao para multiplicacao de float de 32 bits
 *  \param Thread
 *  \return void
 */
void fmul(Thread*);
/*!
 *  Instrucao para multiplicacao de double de 64 bits
 *  \param Thread
 *  \return void
 */
void dmul(Thread*);
/*!
 *  Instrucao para divisao de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void idiv(Thread*);
/*!
 *  Instrucao para divisao de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void Ldiv(Thread*);
/*!
 *  Instrucao para divisao de float de 32 bits
 *  \param Thread
 *  \return void
 */
void fdiv(Thread*);
/*!
 *  Instrucao para divisao de double de 64 bits
 *  \param Thread
 *  \return void
 */
void ddiv(Thread*);
/*!
 *  Instrucao para resto de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void irem(Thread*);
/*!
 *  Instrucao para resto de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lrem(Thread*);
/*!
 *  Instrucao para resto de float de 32 bits
 *  \param Thread
 *  \return void
 */
void frem(Thread*);
/*!
 *  Instrucao para resto de double de 64 bits
 *  \param Thread
 *  \return void
 */
void Drem(Thread*);
/*!
 *  Instrucao para nega de inteiro de 32 bits
 *  \param Thread
 *  \return void
 */
void ineg(Thread*);
/*!
 *  Instrucao para nega de inteiro de 64 bits
 *  \param Thread
 *  \return void
 */
void lneg(Thread*);
/*!
 *  Instrucao para nega de float de 32 bits
 *  \param Thread
 *  \return void
 */
void fneg(Thread*);
/*!
 *  Instrucao para nega de double de 64 bits
 *  \param Thread
 *  \return void
 */
void dneg(Thread*);
/*!
 *  Instrucao para shift left de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void ishl(Thread*);
/*!
 *  Instrucao para shift left de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lshl(Thread*);
/*!
 *  Instrucao para shift right de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void ishr(Thread*);
/*!
 *  Instrucao para shift right de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lshr(Thread*);
/*!
 *  Instrucao para shift right sem sinal de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void iushr(Thread*);
/*!
 *  Instrucao para shift right sem sinal de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lushr(Thread*);
/*!
 *  Instrucao para and de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void iand(Thread*);
/*!
 *  Instrucao para and de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void land(Thread*);
/*!
 *  Instrucao para or de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void ior(Thread*);
/*!
 *  Instrucao para or de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lor(Thread*);
/*!
 *  Instrucao para xor de inteiros de 32 bits
 *  \param Thread
 *  \return void
 */
void ixor(Thread*);
/*!
 *  Instrucao para xor de inteiros de 64 bits
 *  \param Thread
 *  \return void
 */
void lxor(Thread*);
/*!
 *  Instrucao para incremento de inteiros de 32 bits local
 *  \param Thread
 *  \return void
 */
void iinc(Thread*);
#endif /* INST_LOG_ARIT_h */
