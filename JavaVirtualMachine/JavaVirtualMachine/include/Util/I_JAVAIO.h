//#################################################################################################
/*! \file I_JAVAIO.h
 *
 *  \brief Interface simulada da biblioteca java.lang
 *
 *  Interface responsavel por disponibilizar servicos que simulam os metodos e atributos da
 *  biblioteca java.lang
 */
//##################################################################################################

#ifndef I_JAVAIO_h
#define I_JAVAIO_h
#ifdef JAVAIO_SERV
#define EXT24
#else
#define EXT24 extern
#endif

#include "../Estruturas/E_JVM.h"

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao de um metodo da biblioteca java.io
 *
 * \param className Nome da classe do metodo
 * \param methodName Nome do metodo a ser executado.
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
EXT24 void javaIOExecuteMethod(const char* className, const char* methodName,
                               const char* descriptorName, Environment* environment);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que obtem o valor de um campo estatico da biblioteca java.io e empilha na pilha de
 * operandos.
 *
 * \param className Nome da classe do campo
 * \param fieldName Nome do campo a ser obtido.
 * \param fieldDescriptor Descritor do campo a ser obtido.
 * \param environment Ambiente de execucao atual.
 */
EXT24 void javaIOGetStatic(const char* className, const char* fieldName,
                           const char* fieldDescriptor, Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria um objeto da biblioteca java.io e empilha uma referencia na pilha de operandos.
 *
 * \param className Nome da classe do objeto a ser criado.
 * \param environment Ambiente de execucao atual.
 */
EXT24 void javaIONewObject(const char* className, Environment* environment);



#endif /* I_JAVAIO_h */
