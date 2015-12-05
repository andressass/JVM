//#################################################################################################
/*! \file I_INSTRETURN.h
 *
 *  \brief Interface de instrucoes de retorno da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a retorno de funcoes.
 */
//##################################################################################################

#ifndef I_INSTRETURN_h
#define I_INSTRETURN_h
#ifdef M_INSTRETURN_SERV
#define EXT13
#else
#define EXT13 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------

/*!
 *  Instrucao para tratar retorno de um int
 *  \param Environment
 *  \return void
 */
EXT13 void ireturn(Environment* environment);

/*!
 *  Instrucao para tratar retorno de um long
 *  \param Environment
 *  \return void
 */
EXT13 void lreturn(Environment* environment);

/*!
 *  Instrucao para tratar retorno de um float
 *  \param Environment
 *  \return void
 */
EXT13 void freturn(Environment* environment);

/*!
 *  Instrucao para tratar retorno de um double
 *  \param Environment
 *  \return void
 */
EXT13 void dreturn(Environment* environment);

/*!
 *  Instrucao para tratar retorno de um caracter
 *  \param Environment
 *  \return void
 */
EXT13 void areturn(Environment* environment);

/*!
 *  Instrucao para tratar retorno em geral
 *  \param Environment
 *  \return void
 */
EXT13 void return_(Environment* environment);


#endif /* I_INSTRETURN_h */
