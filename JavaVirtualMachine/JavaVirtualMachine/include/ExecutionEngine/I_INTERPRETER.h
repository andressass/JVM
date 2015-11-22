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
#ifdef M_INTERPRETER_SERV
#define EXT8
#else
#define EXT8 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por executar uma thread.
 *
 * \param thread  Thread a ser executada.
 * \param Ponteiro Area de metodos a ser utilizada durante a execucao.
 */
EXT8 void execute(Thread* thread, MethodArea* methodArea);


#endif /* I_INTERPRETER_h */
