//#################################################################################################
/*! \file I_INSTOBJANDINVOKE.h
 *
 *  \brief Interface de instrucoes de Manipulacao de Objetos e Invokes da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a instrucoes de manupulacao
 * de objetos e chamadas de metodos.
 */
//##################################################################################################

#ifndef I_INSTOBJANDINVOKE_h
#define I_INSTOBJANDINVOKE_h
#ifdef INSTOBJANDINVOKE_SERV
#define EXT16
#else
#define EXT16 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dada uma referencia de 2bytes para um atributo de classe no pool de constantes,
 * empilha o valor deste na pilha de operandos
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void getstatic(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dada uma referencia de 2bytes para um atributo de classe no pool de constantes,
 * desempilha um valor e seta o atributo da classe para o valor desempilhado.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void putstatic(Environment* environment);



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dada uma referencia de 2bytes para um atributo de objeto no pool de constantes,
 * desempilha uma referencia para um objeto e empilha o valor do atributo deste objeto.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void getfield(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dada uma referencia de 2bytes para um atributo de objeto no pool de constantes,
 * desempilha um valor e uma referencia para um objeto, setando o atributo do objeto para o valor
 * desempilhado.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void putfield(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que invoca um metodo de instancia. Executa baseado na classe. 
 * Recebe 2bytes para montagem de referencia para um metodo no pool de constantes.
 *
 *
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info
 *
 * 4. Baseado no descritor do metodo, desempilhamos os parametros
 *
 * 5. Desempilhamos uma referencia para o objeto (Objectref)
 *
 * 6. Se o metodo for protected da classe ou superclasse, verificamos se a classe de Objectref
 *    eh a propria classe ou subclasse do metodo
 *
 *      6.1. Se a classe C do objeto for a classe do metodo, buscamos o metodo em C e invocamos
 *
 *      6.2. Se a C tiver uma superclasse, procuramos recursivamente e invocamos
 *
 *      6.3. Se nao, lancamos a excessao AbstractMethodError
 *
 *  7. Criamos um novo frame e empilhamos
 *
 *      7.1. Passamos os argumentos para o vetor de variaveis locais
 *              7.1.1 var_local_0 := Objectref
 *              7.1.2 var_local_1 := argumento_1
 *              7.1.K var_local_N := argumento_N
 *
 *
 *  Excessoes:
 *      1. Se Objectref eh nulo, lancamos NullPointerException
 *      2. Se o metodo nao for encontrado, lancamos AbstractMethodError
 *      3. Se o metodo for abstrato, lancamos AbstractMethodError
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void invokevirtual(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que invoca um metodo de instancia. Tratamento especial para superclasse, private e 
 * invocacao de metodos de inicializacao de instancia.
 * Recebe 2bytes para montagem de referencia para um metodo no pool de constantes.
 *
 *
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info
 *
 * 4. Baseado no descritor do metodo, desempilhamos os parametros
 *
 * 5. Desempilhamos uma referencia para o objeto (Objectref)
 *
 * 6. Se o metodo for protected da classe ou superclasse, verificamos se a classe de Objectref
 *    eh a propria classe ou subclasse do metodo
 *
 * 7. O metodo eh selecionado para invocacao a nao ser que todas as seguintes condicoes sejam 
 *    verdadeiras:
 *
 *      7.1. A flag ACC_SUPER esta setada para a classe atual
 *      7.2. A classe do metodo eh superclasse da classe atual
 *      7.3. O metodo nao eh um metodo <init>
 *      7.4. A classe do metodo eh superclasse da classe atual
 *
 *  8. Se as condicoes acima forem verdadeiras, o metodo a ser invocado eh selecionado pelo seguinte
 *      procedimento de busca. Consideramos C uma superclasse direta da classe atual:
 *
 *      8.1. Se C contiver um metodo de instancia com o mesmo nome e descritor do metodo a ser 
 *              invocado. Invocamos o metodo e terminamos.
 *      8.2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
 *              na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
 *      8.3. Se nao, AbstractMethodError.
 *
 *  9. Criamos um novo frame e empilhamos
 *
 *      9.1. Passamos os argumentos para o vetor de variaveis locais
 *              9.1.1 var_local_0 := Objectref
 *              9.1.2 var_local_1 := argumento_1
 *              9.1.. var_local_N := argumento_N
 *
 *
 *  Excessoes:
 *      1. Se o metodo eh <init> e a classe na qual ele eh declarado nao eh a classe referida pela
 *          instrucao, lancamos NoSuchMethodError.
 *      2. Se o metodo for estatico, lancamos IncompatibleClassChangeError
 *      3. Se nao encontrarmos o metodo, lacamos AbstractMethodError
 *      4. Se o metodo for abstrato, lancamos AbstractMethodError
 *      5. Se Objectref eh nulo, lancamos NullPointerException
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void invokespecial(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que invoca um metodo de classe.
 * Recebe 2bytes para montagem de referencia para um metodo no pool de constantes.
 *
 *
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info
 *
 * 4. Baseado no descritor do metodo, desempilhamos os parametros
 *
 *  7. Criamos um novo frame e empilhamos
 *
 *      7.1. Passamos os argumentos para o vetor de variaveis locais
 *              7.7.1 var_local_0 := argumento_1
 *              7.7.K var_local_[N-1] := argumento_N
 *
 *
 *  Excessoes:
 *      2. Se o metodo nao for estatico, lancamos IncompatibleClassChangeError
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void invokestatic(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que invoca um metodo de interface.
 * Recebe 2bytes para montagem de referencia para um metodo no pool de constantes.
 * Recebe um unsigned byte count != 0.
 * Recebe um unsigned byte 0.
 *
 *
 * 1. Resolvemos o a interface do metodo, obtendo uma referencia para javaClass
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info
 *
 * 4. Baseado no descritor do metodo, desempilhamos os parametros
 *
 * 5. Desempilhamos uma referencia para o objeto (Objectref)
 *
 * 6. Se C eh a classe de Objectref, selecionamos o metodo com o seguinte procedimento:
 *
 *      6.1. Se C contem um metodo de instancia com o mesmo nome e descritor, invocamos e terminamos.
 *      6.2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
 *              na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
 *      6.3. Se nao, AbstractMethodError.
 *
*
 *  7. Criamos um novo frame e empilhamos
 *
 *      7.1. Passamos os argumentos para o vetor de variaveis locais
 *              7.1.1 var_local_0 := Objectref
 *              7.1.2 var_local_1 := argumento_1
 *              7.1.. var_local_N := argumento_N
 *
 *
 *  Excessoes:
 *      1. Se Objectref eh nulo, lancamos NullPointerException
 *      2. Se a classe de Objectref nao implementa a interface, IncompatibleClassChangeError
 *      3. Se nao encontrarmos o metodo, lacamos AbstractMethodError
 *      4. Se o metodo nao for publico, IllegalAccessError
 *      5. Se o metodo for abstrato, lancamos AbstractMethodError
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void invokeinterface(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria uma nova instancia de classe e empilha a referencia na pilha de operandos.
 * Recebe 2bytes para montagem de referencia para uma classe no pool de constantes.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void New(Environment* environment);


#endif /* I_INSTOBJANDINVOKE_h */
