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
/*!
 * Método responsavel por encerrar a JVM em caso de excessoes.
 *
 * \param msg Mensagem de erro a ser exibida
 */
EXT17 void JVMstopAbrupt(const char* msg);



#endif /* I_EXCEPTION_h */
