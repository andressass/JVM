//#################################################################################################
/*! \file I_MEMORYUNIT.h
 *
 *  \brief Interface da Unidade de Memoria da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a unidade de memoria da JVM.
 */
//##################################################################################################

#ifndef I_MEMORYUNIT_h
#define I_MEMORYUNIT_h
#ifdef M_MEMORYUNIT_SERV
#define EX10
#else
#define EXT10 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por criar, inicializar e retornar uma uma referencia para uma estrutura Thread
 *
 * \return Referencia para uma estrutura Thread inicializada
 */
EXT10 Thread* newThread();


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por criar, inicializar e retornar uma uma referencia para uma estrutura 
 * MethodArea
 *
 * \return Referencia para uma estrutura MethodArea inicializada
 */
EXT10 MethodArea* newMethodArea();


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por criar e inicializar um novo frame para um metodo e o empilhar na pilha da
 * thread.
 *
 * \param thread Thread contendo a pilha JVM a ser utilizada no empilhamento do frame
 * \param className Nome qualificado da classe que contem o metodo a ser empilhado
 * \param methodName Nome do metodo a ser empilhado
 * \param methodDescriptor Descritor do metodo a ser executado (polimorfismo)
 */
EXT10 void pushFrame(Thread* thread, const char* className, const char* methodName,
                            const char*  MethodDescriptor);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por desempilhar o frame que está no topo da pilha da thread.
 *
 * \param thread Thread contendo a pilha JVM a ser utilizada no desempilhamento do frame
 */
EXT10 void popFrame(Thread* thread);



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por retornar uma referencia para o frame que está no topo da pilha da thread. 
 *
 * \param thread Thread contendo a pilha JVM com os frames
 * \return Endereco do frame que esta no topo da pilha
 */
EXT10 Frame* getCurrentFrame(Thread* thread);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que recebe o nome de uma classe como parametro e retorna uma referencia para esta 
 * estrutura na area de metodos. Caso a classe nao seja encontrada, retorna nulo.
 *
 * \param qualifiedName Nome qualificado da classe a ser procurada
 * \return Endereco da estrutura JavaClass (ou nulo se nao existe)
 */
EXT10 JavaClass* findJavaClass(const char* qualifiedName);



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que retorna o byte do atributo CODE apontado por PC da estrutura MethodInfo passada como
 * parametro.
 *
 * \param method Endereco da estrutura MethodInfo contendo o atributo CODE a ser utilizado
 * \param pc Endereco da intrucao (indice do byte no vetor de bytes PC)
 * \return Opcode que esta na posicao apontada por PC
 */
EXT10 u1 getByteCodeFromMethod(method_info* method, void* pc);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que obtem o endereco de memoria do atributo de classe (static field) cujo nome eh passado
 * por parametro.
 *
 * \param className Nome qualificado da classe que possui o atributo
 * \param attributeName Nome do atributo de classe
 * \return Endereco de memoria contendo o valor do atributo
 */
EXT10 void* getClassAttributeReference(const char* className, const char* attributeName);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que obtem o endereco de memoria do atributo de objeto (instancia de classe) cujo nome eh 
 * passado por parametro.
 *
 * \param object Endereco do objeto que contem o atributo
 * \param attributeName Nome do atributo do bjeto
 * \return Endereco contendo o valor do atributo
 */
EXT10 void* getObjectAttributeReference(Object* object, const char* attributeName);


//--------------------------------------------------------------------------------------------------
/*!
 * Método que cria e inicializa e retorna uma nova instancia da classe passada como parametro. 
 * A estrutura JavaClass que define o objeto recebe um ponteiro para o mesmo na sua lista de 
 * objetos.
 *
 * \param className Nome qualificado da classe que possui o atributo
 * \return Endereco do objeto
 */
EXT10 Object* newObjectFromClass(const char* className);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que empilha um valor na pilha de operandos do frame atual da thread passada como parametro
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 * \param value Valor a ser empilhado
 */
EXT10 void pushInOperandStack(Thread* thread, u4 value);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que desempilha e retorna um valor na pilha de operandos do frame atual da thread passada 
 * como parametro
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 * \return Valor que foi desempilhado
 */
EXT10 u4 popFromOperandStack(Thread* thread);

#endif /* I_MEMORYUNIT_h */
