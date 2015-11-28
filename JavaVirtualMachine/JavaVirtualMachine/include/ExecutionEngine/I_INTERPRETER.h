//#################################################################################################
/*! \file I_INTERPRETER.h
 *
 *  \brief Interface do Interpretador da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados ao interpretador da JVM.
 */
//##################################################################################################

#ifndef I_INTERPRETER_h
#define I_INTERPRETER_h
#ifdef INTERPRETER_SERV
#define EXT8
#else
#define EXT8 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por executar um ambiente de execucao.
 *
 * \param enviroment  Estrutura contendo a thread e a area de metodos a ser executada
 */
EXT8 void execute(Environment* environment);


#endif /* I_INTERPRETER_h */
