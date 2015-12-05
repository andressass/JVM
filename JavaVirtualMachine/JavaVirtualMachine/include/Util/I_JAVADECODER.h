//#################################################################################################
/*! \file I_JAVADECODER.h
 *
 *  \brief Interface decodificadora de bibliotecas Java
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a decodificacao de metodos,
 * campos e estuturas que simulam o acesso a bibliotecas Java.
 */
//##################################################################################################

#ifndef I_JAVADECODER_h
#define I_JAVADECODER_h
#ifdef JAVADECODER_SERV
#define EXT23
#else
#define EXT23 extern
#endif

#include "../../include/Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que verifica se a classe, instancia ou campo pertencem a java/<pacote>
 *
 * \param name Nome a ser verificado.
 * \return 1 caso sim, 0 caso nao.
 */
EXT23 int isFromJavaLib(const char* name);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao de um metodo de uma biblioteca java
 *
 * \param className Nome da classe do metodo
 * \param methodName Nome do metodo a ser executado.
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
EXT23 void executeJavaLibMethod(const char* className, const char* methodName,
                                const char* descriptorName, Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que obtem o valor de um campo estatico de uma biblioteca java e empilha na pilha de 
 * operandos.
 *
 * \param className Nome da classe do campo
 * \param fieldName Nome do campo a ser obtido.
 * \param fieldDescriptor Descritor do campo a ser obtido.
 * \param environment Ambiente de execucao atual.
 */
EXT23 void getStaticFromJavaLib(const char* className, const char* fieldName,
                                const char* fieldDescriptor, Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria um objeto de uma biblioteca java e empilha uma referencia na pilha de operandos.
 *
 * \param className Nome da classe do objeto a ser criado.
 * \param environment Ambiente de execucao atual.
 */
EXT23 void newObjectFromJavaLib(const char* className, Environment* environment);

#endif /* I_JAVADECODER_h */
