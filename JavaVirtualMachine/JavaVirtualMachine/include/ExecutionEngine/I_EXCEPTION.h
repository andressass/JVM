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
// Definicao de Excessoes e Debugs
//--------------------------------------------------------------------------------------------------

#define NullPointerException            40 //!< Erro de referencia nula
#define AbstractMethodError             41 //!< Erro de chamada de metodo abstrato
#define IncompatibleClassChangeError    42 //!< Erro de chamada de metodo incompativel
#define IllegalAccessError              43 //!< Erro de acesso
#define ArrayIndexOutOfBoundsException  44 //!< Erro acesso index array
#define NegativeArraySizeException      45 //!< Erro de tamanho de array negativo

#define DEBUG_ShowClassFiles            0b001 //!< Ativar exibidor.class
#define DEBUG_DebugModus                0b010 //!< Imprimir frames por instrução
#define DEBUG_ShowBonus                 0b100 //!< Imprimir bonus

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

//--------------------------------------------------------------------------------------------------
/*!
 * Funcao que imprime informacoes relativas ao frame atual
 *
 * \param frame Frame a ser exibido
 * \param opcode Opcode a ser impresso (NULL caso nao precise)
 */
EXT17 void JVMPrintFrameInfo(Frame* frame, u1 opcode);


#endif /* I_EXCEPTION_h */
