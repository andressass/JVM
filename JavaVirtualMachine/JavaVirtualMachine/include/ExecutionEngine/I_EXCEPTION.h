//#################################################################################################
/*! \file I_EXCEPTION.h
 *
 *  \brief Interface de excessoes da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados ao tratamento de excessoes
 *  lancadas pela JVM.
 */
//##################################################################################################

#ifndef I_EXCEPTION_h
#define I_EXCEPTION_h
#ifdef EXCEPTION_SERV
#define EXT17
#else
#define EXT17 extern
#endif

#include "../Estruturas/E_JVM.h"

//--------------------------------------------------------------------------------------------------
// Definicao de Excessoes
//--------------------------------------------------------------------------------------------------

#define NullPointerException            40 //!< Erro de referencia nula
#define AbstractMethodError             41 //!< Erro de chamada de metodo abstrato
#define IncompatibleClassChangeError    42 //!< Erro de chamada de metodo incompativel
#define IllegalAccessError              43 //!< Erro de acesso
#define ArrayIndexOutOfBoundsException  44 //!< Erro acesso index array


//--------------------------------------------------------------------------------------------------
//Metodos
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
/*!
 * Método responsavel por encerrar a JVM em caso de excessoes.
 *
 * \param msg Mensagem de erro a ser exibida
 */
EXT17 void JVMstopAbrupt(const char* msg);


//--------------------------------------------------------------------------------------------------
/*!
 * Pelo lancamento e tratamento de excessoes
 *
 * \param exception codigo da excessao
 */
EXT17 void JVMThrow(int exception, Environment* environment);


#endif /* I_EXCEPTION_h */
