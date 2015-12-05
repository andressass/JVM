//#################################################################################################
/*! \file I_INSTCONVERSION.h
 *
 *  \brief Interface de instrucoes de conversao de tipos da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a conversao de tipos.
 */
//##################################################################################################

#ifndef I_INSTCONVERSION_h
#define I_INSTCONVERSION_h
#ifdef M_INSTCONVERSION_SERV
#define EXT12
#else
#define EXT12 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
#define SHIFT_MASK_UNSI 0xffffffff

/*!
 *  Instrucao para conversao de um int em um long
 *  \param Environment
 *  \return void
 */
EXT11 void i2l(Environment* environment);

/*!
 *  Instrucao para conversao de um int em um float
 *  \param Environment
 *  \return void
 */
EXT11 void i2f(Environment* environment);

/*!
 *  Instrucao para conversao de um int em um double
 *  \param Environment
 *  \return void
 */
EXT11 void i2d(Environment* environment);

/*!
 *  Instrucao para conversao de um long em um int
 *  \param Environment
 *  \return void
 */
EXT11 void l2i(Environment* environment);

/*!
 *  Instrucao para conversao de um long em um float
 *  \param Environment
 *  \return void
 */
EXT11 void l2f(Environment* environment);

/*!
 *  Instrucao para conversao de um long em um double
 *  \param Environment
 *  \return void
 */
EXT11 void l2d(Environment* environment);

/*!
 *  Instrucao para conversao de um float em um int
 *  \param Environment
 *  \return void
 */
EXT11 void f2i(Environment* environment);

/*!
 *  Instrucao para conversao de um float em um long
 *  \param Environment
 *  \return void
 */
EXT11 void f2l(Environment* environment);

/*!
 *  Instrucao para conversao de um float em um double
 *  \param Environment
 *  \return void
 */
EXT11 void f2d(Environment* environment);

/*!
 *  Instrucao para conversao de um double em um int
 *  \param Environment
 *  \return void
 */
EXT11 void d2i(Environment* environment);

/*!
 *  Instrucao para conversao de um double em um long
 *  \param Environment
 *  \return void
 */
EXT11 void d2l(Environment* environment);

/*!
 *  Instrucao para conversao de um double em um float
 *  \param Environment
 *  \return void
 */
EXT11 void d2f(Environment* environment);
/*!
 *  Instrucao para conversao de um int em um byte
 *  \param Environment
 *  \return void
 */
EXT11 void i2b(Environment* environment);

/*!
 *  Instrucao para conversao de um int em um char
 *  \param Environment
 *  \return void
 */
EXT11 void i2c(Environment* environment);

/*!
 *  Instrucao para conversao de um int em um short
 *  \param Environment
 *  \return void
 */
EXT11 void i2s(Environment* environment);

#endif /* I_INSTCONVERSION_h */
