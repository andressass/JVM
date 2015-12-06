//#################################################################################################
/*! \file I_INSTLOGARITH.h
 *
 *  \brief Interface de instrucoes logico aritimeticas da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a instrucoes logico atmeticas
 */
//##################################################################################################

#ifndef I_INSTLOGARITH_h
#define I_INSTLOGARITH_h
#ifdef INSTLOGARITH_SERV
#define EXT11
#else
#define EXT11 extern
#endif

#include "../Estruturas/E_JVM.h"

//--------------------------------------------------------------------------------------------------
#define SHIFT_MASK_32 0x1F
#define SHIFT_MASK_64 0x3F

/*!
 *  Instrucao para soma de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void iadd(Environment*);

/*!
 *  Instrucao para soma de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ladd(Environment*);
/*!
 *  Instrucao para soma de float de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void fadd(Environment*);
/*!
 *  Instrucao para soma de double de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void dadd(Environment*);
/*!
 *  Instrucao para subtracao de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void isub(Environment*);
/*!
 *  Instrucao para subtracao de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lsub(Environment*);
/*!
 *  Instrucao para subtracao de float de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void fsub(Environment*);
/*!
 *  Instrucao para subtracao de double de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void dsub(Environment*);
/*!
 *  Instrucao para multiplicacao de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void imul(Environment*);
/*!
 *  Instrucao para multiplicacao de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lmul(Environment*);
/*!
 *  Instrucao para multiplicacao de float de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void fmul(Environment*);
/*!
 *  Instrucao para multiplicacao de double de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void dmul(Environment*);
/*!
 *  Instrucao para divisao de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void idiv(Environment*);
/*!
 *  Instrucao para divisao de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void Ldiv(Environment*);
/*!
 *  Instrucao para divisao de float de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void fdiv(Environment*);
/*!
 *  Instrucao para divisao de double de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ddiv(Environment*);
/*!
 *  Instrucao para resto de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void irem(Environment*);
/*!
 *  Instrucao para resto de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lrem(Environment*);
/*!
 *  Instrucao para resto de float de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void frem(Environment*);
/*!
 *  Instrucao para resto de double de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void Drem(Environment*);
/*!
 *  Instrucao para nega de inteiro de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ineg(Environment*);
/*!
 *  Instrucao para nega de inteiro de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lneg(Environment*);
/*!
 *  Instrucao para nega de float de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void fneg(Environment*);
/*!
 *  Instrucao para nega de double de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void dneg(Environment*);
/*!
 *  Instrucao para shift left de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ishl(Environment*);
/*!
 *  Instrucao para shift left de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lshl(Environment*);
/*!
 *  Instrucao para shift right de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ishr(Environment*);
/*!
 *  Instrucao para shift right de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lshr(Environment*);
/*!
 *  Instrucao para shift right sem sinal de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void iushr(Environment*);
/*!
 *  Instrucao para shift right sem sinal de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lushr(Environment*);
/*!
 *  Instrucao para and de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void iand(Environment*);
/*!
 *  Instrucao para and de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void land(Environment*);
/*!
 *  Instrucao para or de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ior(Environment*);
/*!
 *  Instrucao para or de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lor(Environment*);
/*!
 *  Instrucao para xor de inteiros de 32 bits
 *  \param Environment
 *  \return void
 */
EXT11 void ixor(Environment*);
/*!
 *  Instrucao para xor de inteiros de 64 bits
 *  \param Environment
 *  \return void
 */
EXT11 void lxor(Environment*);
/*!
 *  Instrucao para incremento de inteiros de 32 bits local
 *  \param Environment
 *  \param int será a constante que será somada
 *  \param u4 será o indice que será modificado
 *  \return void
 */
EXT11 void iinc(Environment*, int, u4);



#endif /* I_INSTLOGARITH_h */
