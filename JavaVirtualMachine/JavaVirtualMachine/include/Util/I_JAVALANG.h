//#################################################################################################
/*! \file I_JAVALANG.h
 *
 *  \brief Interface simulada da biblioteca java.lang
 *
 *  Interface responsavel por disponibilizar servicos que simulam os metodos e atributos da 
 *  biblioteca java.lang
 */
//##################################################################################################

#ifndef I_JAVALANG_h
#define I_JAVALANG_h
#ifdef JAVALANG_SERV
#define EXT25
#else
#define EXT25 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao de um metodo da biblioteca java.lang
 *
 * \param className Nome da classe do metodo
 * \param methodName Nome do metodo a ser executado.
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
EXT25 void javaLangExecuteMethod(const char* className, const char* methodName,
                                 const char* descriptorName, Environment* environment);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que obtem o valor de um campo estatico da biblioteca java.lang e empilha na pilha de
 * operandos.
 *
 * \param className Nome da classe do campo
 * \param fieldName Nome do campo a ser obtido.
 * \param fieldDescriptor Descritor do campo a ser obtido.
 * \param environment Ambiente de execucao atual.
 */
EXT25 void javaLangGetStatic(const char* className, const char* fieldName,
                             const char* fieldDescriptor, Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria um objeto da biblioteca java.lang e empilha uma referencia na pilha de operandos.
 *
 * \param className Nome da classe do objeto a ser criado.
 * \param environment Ambiente de execucao atual.
 */
EXT25 void javaLangNewObject(const char* className, Environment* environment);



#endif /* I_JAVALANG_h */
