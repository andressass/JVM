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
 * para o pool de constantes da classe corrente, onde o valor do indice eh 
 * (indexbyte1 << 8) | indexbyte2. O valor no pool de constantes pode ser uma constante do tipo long 
 * ou double. O valor numerico da constante eh empilhado na pilha de operandos.
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
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis 
 * locais do frame corrente eh o 0. A variavel local no index deve conter um inteiro. O valor da 
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 1. A variavel local no index deve conter um inteiro. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 2. A variavel local no index deve conter um inteiro. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
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
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 0. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 1. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 2. A variavel local no index deve conter um float. O valor da
 * variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
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
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 0. A variavel local no index deve conter uma referencia. O objectref 
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 1. A variavel local no index deve conter uma referencia. O objectref
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh o 2. A variavel local no index deve conter uma referencia. O objectref
 * da variavel local eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aload_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
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

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo long.
 * O index tambem eh desempilhado e deve ser do tipo int. O valor long no componente do vetor eh
 * recuperado no index e empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void laload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo float.
 * O index tambem eh desempilhado e deve ser do tipo int. O valor float no componente do vetor eh
 * recuperado no index e empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void faload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo double.
 * O index tambem eh desempilhado e deve ser do tipo int. O valor double no componente do vetor eh
 * recuperado no index e empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void daload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo reference.
 * O index tambem eh desempilhado e deve ser do tipo int. O valor reference no componente do vetor eh
 * recuperado no index e empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aaload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo byte
 * ou do tipo boolean. O index tambem eh desempilhado e deve ser do tipo int. O valor no componente 
 * do vetor eh recuperado no index e, caso seja do tipo byte, ele eh estendido com sinal ou, caso o
 * valor seja do tipo booleano, ele eh estendido sem sinal. Nos dois casos ele eh empilhado na pilha 
 * de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void baload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo char e fazer referencia a um vetor cujo os componentes sao do tipo char.
 * O index tambem eh desempilhado e deve ser do tipo int. O valor char no componente do vetor eh
 * recuperado no index e estendido sem sinal. Ele eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void caload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo char e fazer referencia a um vetor cujo os componentes sao do tipo short.
 * O index tambem eh desempilhado e deve ser do tipo int. O valor short no componente do vetor eh
 * recuperado no index e estendido com sinal para um valor int. Ele eh empilhado na pilha de operandos.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void saload(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o
 * qual eh um indice valido para o vetor de variaveis locais do frame corrente. O valor no topo da 
 * pilha de operandos deve ser do tipo int e eh desempilhado. O valor da variavel local no index eh 
 * setado para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void istore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index,
 * onde ambos os index e index+1 sao indices validos para o vetor de variaveis locais do frame
 * corrente. O valor no topo da pilha de operandos deve ser do tipo long e eh desempilhado. Os 
 * valores das variavel locais no index e index+1 sao setados para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lstore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o
 * qual eh um indice valido para o vetor de variaveis locais do frame corrente. O valor no topo da
 * pilha de operandos deve ser do tipo float e eh desempilhado e passa pela "value set conversion", 
 * resultando em valor'. O valor da variavel local no index eh setado para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fstore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index,
 * onde ambos os index e index+1 sao indices validos para o vetor de variaveis locais do frame
 * corrente. O valor no topo da pilha de operandos deve ser do tipo double e eh desempilhado e passa 
 * pela "value set conversion", resultando em valor'. Os valores das variavel locais no index e 
 * index+1 sao setados para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dstore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao que recebe como argumento o unsigned byte index, o
 * qual eh um indice valido para o vetor de variaveis locais do frame corrente. O objectref no topo 
 * da pilha de operandos deve ser do tipo returnAddress ou reference e eh desempilhado. O valor da 
 * variavel local no index eh setado para este objectref desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void astore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 0. O valor no topo da pilha de operandos deve ser do tipo int e eh 
 * desempilhado. O valor da variavel local no index eh setado para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void istore_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 1. O valor no topo da pilha de operandos deve ser do tipo int e eh
 * desempilhado. O valor da variavel local no index eh setado para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void istore_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 2. O valor no topo da pilha de operandos deve ser do tipo int e eh
 * desempilhado. O valor da variavel local no index eh setado para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void istore_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 3. O valor no topo da pilha de operandos deve ser do tipo int e eh
 * desempilhado. O valor da variavel local no index eh setado para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void istore_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor 
 * de variaveis locais do frame corrente sao o 0 e 1. O valor no topo da pilha de operandos deve ser 
 * do tipo long e eh desempilhado. Os valores das variavel locais no index e index+1 sao setados 
 * para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lstore_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 1 e 2. O valor no topo da pilha de operandos deve ser
 * do tipo long e eh desempilhado. Os valores das variavel locais no index e index+1 sao setados
 * para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lstore_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 2 e 3. O valor no topo da pilha de operandos deve ser
 * do tipo long e eh desempilhado. Os valores das variavel locais no index e index+1 sao setados
 * para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lstore_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 3 e 4. O valor no topo da pilha de operandos deve ser
 * do tipo long e eh desempilhado. Os valores das variavel locais no index e index+1 sao setados
 * para este valor desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lstore_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 0. O valor no topo da pilha de operandos deve ser do tipo float e eh
 * desempilhado e passa pela "value set conversion", resultando em valor'. O valor da variavel local 
 * no index eh setado para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fstore_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 1. O valor no topo da pilha de operandos deve ser do tipo float e eh
 * desempilhado e passa pela "value set conversion", resultando em valor'. O valor da variavel local
 * no index eh setado para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fstore_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 2. O valor no topo da pilha de operandos deve ser do tipo float e eh
 * desempilhado e passa pela "value set conversion", resultando em valor'. O valor da variavel local
 * no index eh setado para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fstore_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 3. O valor no topo da pilha de operandos deve ser do tipo float e eh
 * desempilhado e passa pela "value set conversion", resultando em valor'. O valor da variavel local
 * no index eh setado para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fstore_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 0 e 1. O valor no topo da pilha de operandos deve ser
 * do tipo double e eh desempilhado e passa pela "value set conversion", resultando em valor'. Os 
 * valores das variavel locais no index e index+1 sao setados para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dstore_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 1 e 2. O valor no topo da pilha de operandos deve ser
 * do tipo double e eh desempilhado e passa pela "value set conversion", resultando em valor'. Os
 * valores das variavel locais no index e index+1 sao setados para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dstore_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 2 e 3. O valor no topo da pilha de operandos deve ser
 * do tipo double e eh desempilhado e passa pela "value set conversion", resultando em valor'. Os
 * valores das variavel locais no index e index+1 sao setados para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dstore_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde os indices validos index e index+1 para o vetor
 * de variaveis locais do frame corrente sao o 3 e 4. O valor no topo da pilha de operandos deve ser
 * do tipo double e eh desempilhado e passa pela "value set conversion", resultando em valor'. Os
 * valores das variavel locais no index e index+1 sao setados para este valor'.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dstore_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 0. O objectref no topo da pilha de operandos deve ser do tipo 
 * returnAddress ou reference e eh desempilhado. O valor da variavel local no index eh setado para 
 * este objectref desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void astore_0(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 1. O objectref no topo da pilha de operandos deve ser do tipo
 * returnAddress ou reference e eh desempilhado. O valor da variavel local no index eh setado para
 * este objectref desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void astore_1(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 2. O objectref no topo da pilha de operandos deve ser do tipo
 * returnAddress ou reference e eh desempilhado. O valor da variavel local no index eh setado para
 * este objectref desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void astore_2(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por relizar uma instrucao onde o indice valido index para o vetor de variaveis
 * locais do frame corrente eh 3. O objectref no topo da pilha de operandos deve ser do tipo
 * returnAddress ou reference e eh desempilhado. O valor da variavel local no index eh setado para
 * este objectref desempilhado.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void astore_3(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo int.
 * O index e value tambem sao desempilhados e devem ser do tipo int. O int value eh armazenado como 
 * o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void iastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo 
 * long. O index deve ser do tipo int e value deve ser do tipo long e tambem sao desempilhados. O 
 * long value eh armazenado como o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void lastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo
 * float. O index deve ser do tipo int e value deve ser do tipo float e tambem sao desempilhados. O
 * float value passa pela "value set conversion", resultando em value', e value' eh armazenado como 
 * o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void fastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo
 * double. O index deve ser do tipo int e value deve ser do tipo double e tambem sao desempilhados. 
 * O double value passa pela "value set conversion", resultando em value', e value' eh armazenado 
 * como o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void dastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo
 * reference. O index deve ser do tipo int e value deve ser do tipo reference e tambem sao 
 * desempilhados. O reference value eh armazenado como o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void aastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo byte
 * ou do tipo boolean. O index e value tambem sao desempilhados e devem ser do tipo int. Caso os 
 * componentes do vetor forem do tipo byte, o int value eh truncado para um byte ou, caso os 
 * componentes do vetor forem do tipo boolean, o int value eh truncado para seu bit de ordem baixa 
 * e, entao, estendido sem sinal para o tamanho de armazenamento para componentes de vetores boolen 
 * usados pela implementacao. O resultado eh armazenado como o componente do vetor indexado pelo 
 * index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void bastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo
 * char. O index e value tambem sao desempilhados e devem ser do tipo int. O int value eh truncado 
 * para um char e armazenado como o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void castore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que desempilha da pilha de operandos o arrayref,
 * que deve ser do tipo reference e fazer referencia a um vetor cujo os componentes sao do tipo
 * short. O index e value tambem sao desempilhados e devem ser do tipo int. O int value eh truncado
 * para um short e armazenado como o componente do vetor indexado pelo index.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void sastore(Thread* thread);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por realizar uma instrucao que estende o indice de variavel local por bytes 
 * adicionais. Ela modifica o comportamento de outras instrucoes e assume um de dois formatos, 
 * dependendo da instrucao a ser modificada. O primeiro formato modifica uma das instrucoes iload, 
 * fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, ou ret. O segundo formato se 
 * aplica apenas para a instrucao iinc. Em qualquer caso a instrucao wide eh seguida pelo opcode da 
 * instrucao a ser modificada e, logo apos ele, segue-se os unsigned bytes indexbyte1 e indexbyte2 
 * que, quando montados em um unsigned de 16 bits, viram um indice valido para um vetor de variaveis 
 * locais no frame corrente, onde o valor do indice eh (indexbyte1 << 8) | indexbyte2. Para as 
 * instrucoes lload, dload, lstore, or dstore, o indice index+1 seguinte ao calculo tambem eh um 
 * indice valido para o vetor de variaveis locais. No segundo formato, dois imediatos unsigned bytes 
 * constbyte1 e constbyte2 seguem indexbyte1 e indexbyte2. Eles tambem sao montados em uma constante 
 * signed 16-bit, onde o valor da constante eh (constbyte1 << 8) | constbyte2.
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
EXT14 void wide(Thread* thread);

#endif /* I_INSTLOADSTORAGE_h */
