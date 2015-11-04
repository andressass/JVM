//#################################################################################################
/*! \file IP_LECLASS.h
 *
 *  \brief Interface de Persistencia do Leitor e Exibidor de arquivos ".class".
 *
 *  Interface responsavel por prover os metodos responsaveis pela manipulacao de arquivos
 *  ".class".
 */
//##################################################################################################

#ifndef IP_LECLASS
#define IP_LECLASS
#ifdef P_LECLASS_SERV
#define EXT2
#else
#define EXT2 extern
#endif

#include<stdio.h>
#include<stdlib.h>
#include "E_LECLASS.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por abrir e retornar um arquivo em modo de leitura.
 *
 * \param nome_arquivo Nome ou caminho do arquivo a ser aberto.
 */
EXT2 FILE* obter_entrada(const char * nome_arquivo);


//--------------------------------------------------------------------------------------------------
/*!
 * Le um tipo u1 (8bits) do arquivo.
 *
 * \param arquivo Arquivo no qual sera realizada a leitura.
 */
EXT2 u1 u1Le(FILE *arquivo);



//--------------------------------------------------------------------------------------------------
/*!
 * Le um tipo u2 (16bits) do arquivo.
 *
 * \param arquivo Arquivo no qual sera realizada a leitura.
 */
EXT2 u2 u2Le(FILE *arquivo);


//--------------------------------------------------------------------------------------------------
/*!
 * Le um tipo u4 (32bits) do arquivo.
 *
 * \param arquivo Arquivo no qual sera realizada a leitura.
 */
EXT2 u4 u4Le(FILE *arquivo);



#endif
