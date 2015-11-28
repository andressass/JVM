//#################################################################################################
/*! \file I_CLASSLOADER.h
 *
 *  \brief Interface do Carregador de Classes da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados ao carregamento de classes da 
 *  JVM.
 */
//##################################################################################################

#ifndef I_CLASSLOADER_h
#define I_CLASSLOADER_h
#ifdef M_CLASSLOADER_SERV
#define EXT9
#else
#define EXT9 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dado um nome qualificado de classe, retorna uma estrutura JavaClass preenchida
 *
 * \param qualifiedName Nome qualificado da classe a ser carregada
  * \param environment Ambiente de execucao atual
 * \return Estrutura arqClass preenchida com os dados da classe carregada 
 */
EXT9 JavaClass* loadCLass(const char* qualifiedName, Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Método que aloca todos os espaços de memoria necessarios para os campos de uma classe ou objeto e inicializa os inicializa com os valores default.
 *
 * \param javaClass Referencia para a estrutura de classe com os parametros
 * \param flagsAccept Flags para o tipos de campos aceitos (Ex.: STATIC, FINAL)
 * \param flagsRegect Flags para o tipos de campos rejeitados (Ex.: STATIC, FINAL)
 * \return Estrutura de campos preenchida
 */
EXT9 Fields* classInitializeFields(JavaClass* javaClass, u2 flagsAccept, u2 flagsRegect);


#endif /* I_CLASSLOADER_h */
