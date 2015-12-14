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
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass.
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info.
 *
 * 3. Baseado no descritor do metodo, desempilhamos os parametros.
 *
 * 4. Desempilhamos uma referencia para o objeto (Objectref).
 *
 * 5. Se o metodo for protected da classe ou superclasse, verificamos se a classe de Objectref
 *    eh a propria classe ou subclasse do metodo:
 *
 *      1. Se a classe C do objeto for a classe do metodo, buscamos o metodo em C e invocamos.
 *
 *      2. Se a C tiver uma superclasse, procuramos recursivamente e invocamos.
 *
 *      3. Se nao, lancamos a excessao AbstractMethodError.
 *
 *  6. Criamos um novo frame e empilhamos.
 *
 *      6.1. Passamos os argumentos para o vetor de variaveis locais:
 *              1. var_local_0 := Objectref.
 *              2. var_local_1 := argumento_1.
 *              K. var_local_N := argumento_N.
 *
 *
 *  Excessoes:
 *      1. Se Objectref eh nulo, lancamos NullPointerException.
 *      2. Se o metodo nao for encontrado, lancamos AbstractMethodError.
 *      3. Se o metodo for abstrato, lancamos AbstractMethodError.
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
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass.
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info.
 *
 * 4. Baseado no descritor do metodo, desempilhamos os parametros.
 *
 * 5. Desempilhamos uma referencia para o objeto (Objectref).
 *
 * 6. Se o metodo for protected da classe ou superclasse, verificamos se a classe de Objectref
 *    eh a propria classe ou subclasse do metodo.
 *
 * 7. O metodo eh selecionado para invocacao a nao ser que todas as seguintes condicoes sejam
 *    verdadeiras:
 *
 *      1. A flag ACC_SUPER esta setada para a classe atual.
 *      2. A classe do metodo eh superclasse da classe atual.
 *      3. O metodo nao eh um metodo <init>.
 *      4. A classe do metodo eh superclasse da classe atual.
 *
 *  8. Se as condicoes acima forem verdadeiras, o metodo a ser invocado eh selecionado pelo seguinte
 *      procedimento de busca. Consideramos C uma superclasse direta da classe atual:
 *
 *      1. Se C contiver um metodo de instancia com o mesmo nome e descritor do metodo a ser
 *              invocado. Invocamos o metodo e terminamos.
 *      2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
 *              na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
 *      3. Se nao, AbstractMethodError.
 *
 *  9. Criamos um novo frame e empilhamos.
 *
 *      9.1. Passamos os argumentos para o vetor de variaveis locais:
 *              1. var_local_0 := Objectref.
 *              2. var_local_1 := argumento_1.
 *              3. var_local_N := argumento_N.
 *
 *
 *  Excessoes:
 *      1. Se o metodo eh <init> e a classe na qual ele eh declarado nao eh a classe referida pela
 *          instrucao, lancamos NoSuchMethodError.
 *      2. Se o metodo for estatico, lancamos IncompatibleClassChangeError.
 *      3. Se nao encontrarmos o metodo, lacamos AbstractMethodError.
 *      4. Se o metodo for abstrato, lancamos AbstractMethodError.
 *      5. Se Objectref eh nulo, lancamos NullPointerException.
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
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass.
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info.
 *
 * 3. Baseado no descritor do metodo, desempilhamos os parametros.
 *
 * 4. Criamos um novo frame e empilhamos.
 *
 *      1. Passamos os argumentos para o vetor de variaveis locais:
 *              1. var_local_0 := argumento_1.
 *              2. var_local_[N-1] := argumento_N.
 *
 *
 *  Excessoes:
 *      1. Se o metodo nao for estatico, lancamos IncompatibleClassChangeError.
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
 * 1. Resolvemos o a interface do metodo, obtendo uma referencia para javaClass.
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info.
 *
 * 3. Baseado no descritor do metodo, desempilhamos os parametros.
 *
 * 4. Desempilhamos uma referencia para o objeto (Objectref).
 *
 * 5. Se C eh a classe de Objectref, selecionamos o metodo com o seguinte procedimento:
 *
 *      1. Se C contem um metodo de instancia com o mesmo nome e descritor, invocamos e terminamos.
 *      2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
 *              na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
 *      3. Se nao, AbstractMethodError.
 *
 *
 *  6. Criamos um novo frame e empilhamos.
 *
 *      6.1. Passamos os argumentos para o vetor de variaveis locais:
 *              1. var_local_0 := Objectref.
 *              2. var_local_1 := argumento_1.
 *              3. var_local_N := argumento_N.
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


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que lanca uma excessao eu erro.
 *
 * 1. Desempilha uma referencia para um objeto instancia (ou subclasse de) Throwable.
 *
 * 2. O objeto eh lancado atraves de uma busca no metodo corrente pela primeira rotina de tratamento
 *      de excessao que seja compativel com a classe do objeto:
 *
 *      1. Se a rotina for encontrada, PC eh resetado para a localizacao do codigo na qual a 
 *          excessao sera tratada. A pilha de operandos eh limpa e a referencia para o objeto eh
 *          empilhada de volta. A Execucao continua.
 * 
 *      2. Se a rotina nao for encontrada no frame atual, ele eh desempilhado. Se o novo frame do
 *          topo existir, o objeto eh relancado. Se o frame nao existir, a thread atual eh 
 *          encerrada.
 *
 *  3. Excessoes:
        1. Se Objectref for null, NullPointerException eh lancado
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void athrow(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria um novo array. Ele recebe como parametro o tipo do array a ser criado atype e
 * desempilha o numero de elementos no array a ser criado count. O novo array, cujos componentes sao
 * do tipo atype e de tamanho count, eh alocado e uma reference arrayref a ele eh empilhada na pilha
 * de operandos. Cada um dos elementos do novo array sao inicializados para o valor inicial padrao
 * para o tipo do array.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void newarray(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria um novo array de reference. O numero de componentes do array a ser criado count
 * deve ser do tipo int e eh desempilhado da pilha de operandos. O metodo recebe como parametro os
 * unsigned indexbyte1 e indexbyte2 que, quando montados, viram um indice para a constante pool de
 * tempo de execucao da classe corrente, onde o valor do indice eh (indexbyte1 << 8) | indexbyte2. O
 * item da constante pool de tempo de execucao no indice deve ser uma referencia simbolica para um
 * tipo class, array ou interface. O tipo nomeado da classe, array ou interface eh resolvido.
 * Um novo array com componentes daquele tipo, de tamanho count, eh alocado e uma reference arrayref
 * a ele eh empilhada na pilha de operandos. Cada um dos elementos do novo array sao inicializados
 * para null, o valor padrao para tipos reference.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void anewarray(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que obtem o tamanho do array. O arrayref deve ser do tipo reference e deve se referir a um
 * array. Ele eh desempilhado da pilha de operandos. O tamanho do array que ele referencia eh
 * determinado e eh empilhado na pilha de operandos como um int.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void arraylength(Environment* environment);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que cria um novo array multidimensional. O metodo recebe como argumento um numero de
 * dimensoes do array a ser criado dimensions. A pilha de operandos deve conter os valores das
 * dimensoes count1, count2... Cada valor representa o numero de componentes em uma dimensao do
 * array a ser criado e deve ser do tipo int e nao negativo.
 *
 * Todos os valores count sao desempilhados da pilha de operandos. O metodo tambem recebe como
 * parametro os unsigned indexbyte1 e indexbyte2 que, quando montados, viram um indice para a
 * constante pool de tempo de execucao da classe corrente, onde o valor do indice eh
 * (indexbyte1 << 8) | indexbyte2. O item da constante pool de tempo de execucao no indice deve ser
 * uma referencia simbolica para um tipo class, array ou interface. O tipo nomeado da classe, array
 * ou interface esta resolvido. A entrada resultante deve ser um array de tipo class de
 * dimensionalidade maior ou igual a dimensions.
 *
 * Um novo array multidimensional de tipo do array eh alocado. Se qualquer valor count for zero,
 * nenhuma dimensao subsequente eh alocada. Os componentes do array na primeira dimensao sao
 * inicializados para os subarrays do tipo da segunda dimensao, e assim por diante. Os componentes
 * da ultima dimensao alocada do array sao inicializados para o valor inicial padrao pelo tipo dos
 * componentes. Uma reference arrayref para o novo array eh empilhada na pilha de operandos.
 *
 * \param environment Ambiente de execucao atual.
 */
EXT16 void multianewarray(Environment* environment);


#endif /* I_INSTOBJANDINVOKE_h */
