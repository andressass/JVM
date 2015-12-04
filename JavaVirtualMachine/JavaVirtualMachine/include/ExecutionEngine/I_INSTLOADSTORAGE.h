//#################################################################################################
/*! \file I_INSTLOADSTORAGE.h
 *
 *  \brief Interface de instrucoes de carga e armazenamento da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a instrucoes que transferem
 *  valores entre o vetor de variaveis locais e a pilha de operandos de um frame de um metodo.
 */
//##################################################################################################

#ifndef I_INSTLOADSTORAGE_h
#define I_INSTLOADSTORAGE_h
#ifdef INSTLOADSTORAGE_SERV
#define EXT14
#else
#define EXT14 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que faz nada
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void nop(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos uma referencia ao
 * objeto null
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aconst_null(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro -1
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_m1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro 0
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro 1
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro 2
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro 3
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro 4
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_4(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor inteiro 5
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iconst_5(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor long 0
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lconst_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor long 1
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lconst_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor float 0
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fconst_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor float 1
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fconst_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor float 2
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fconst_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor double 0
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dconst_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que empilha na pilha de operandos o valor double 1
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dconst_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que estende com sinal o byte imediato para um valor
 * int e, então, o empilha na pilha de operandos
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void bipush(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que estende com sinal o valor imediato short 
 * (byte1 << 8) | byte2 para um valor int e, então, o empilha na pilha de operandos
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void sipush(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o 
 * qual eh um indice valido para o pool de constantes da classe corrente. O valor no pool de 
 * constantes pode ser uma constante do tipo int ou float ou uma referencia simbolica para um 
 * literal string. Caso for do tipo int ou float, deve emplilhar na pilha de operandos o valor
 * numerico da constante e, caso seja uma referencia para uma instancia da classe String, esta
 * referencia deve ser empilhada.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void ldc(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento os unsigned byte 
 * indexbyte1 e indexbyte2 que, quando montados em um unsigned de 16 bits, viram um indice valido 
 * para o pool de constantes da classe corrente. O valor no pool de
 * constantes pode ser uma constante do tipo int ou float ou uma referencia simbolica para um
 * literal string. Caso for do tipo int ou float, deve emplilhar na pilha de operandos o valor
 * numerico da constante e, caso seja uma referencia para uma instancia da classe String, esta
 * referencia deve ser empilhada.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void ldc_w(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento os unsigned byte
 * indexbyte1 e indexbyte2 que, quando montados em um unsigned de 16 bits, viram um indice valido
 * para o pool de constantes da classe corrente. O valor no pool de constantes pode ser uma 
 * constante do tipo long ou double. O valor numerico da constante eh empilhado na pilha de 
 * operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void ldc2_w(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o
 * qual eh um indice valido para o vetor de variaveis locais do frame corrente. A variavel local no 
 * index deve conter um inteiro. O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, 
 * onde ambos os index e index+1 sao indices validos para o vetor de variaveis locais do frame
 * corrente. A variavel local no index deve conter um long. O valor da variavel local no index eh
 * empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o
 * qual eh um indice valido para o vetor de variaveis locais do frame corrente. A variavel local no
 * index deve conter um float. O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index,
 * onde ambos os index e index+1 sao indices validos para o vetor de variaveis locais do frame
 * corrente. A variavel local no index deve conter um double. O valor da variavel local no index eh
 * empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o
 * qual eh um indice valido para o vetor de variaveis locais do frame corrente. A variavel local no
 * index deve conter uma referencia. O objectref da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis 
 * locais do frame corrente eh o 0. A variavel local no index deve conter um inteiro. O valor da 
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 1. A variavel local no index deve conter um inteiro. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 2. A variavel local no index deve conter um inteiro. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 3. A variavel local no index deve conter um inteiro. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor 
 * de variaveis locais do frame corrente sao o 0 e 1. A variavel local no index deve conter um long. 
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 1 e 2. A variavel local no index deve conter um long.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 2 e 3. A variavel local no index deve conter um long.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 3 e 4. A variavel local no index deve conter um long.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lload_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 0. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 1. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 2. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 3. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 0 e 1. A variavel local no index deve conter um double.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 1 e 2. A variavel local no index deve conter um double.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 2 e 3. A variavel local no index deve conter um double.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 3 e 4. A variavel local no index deve conter um double.
 * O valor da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dload_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 0. A variavel local no index deve conter uma referencia. O objectref 
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 1. A variavel local no index deve conter uma referencia. O objectref
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 2. A variavel local no index deve conter uma referencia. O objectref
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 3. A variavel local no index deve conter uma referencia. O objectref
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref, 
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo int. 
 * O index tambem eh desempilhado e deve ser do tipo int. O valor int no componente do vetor eh 
 * recuperado no index e empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iaload(Thread* thread);

#endif /* I_INSTLOADSTORAGE_h */
