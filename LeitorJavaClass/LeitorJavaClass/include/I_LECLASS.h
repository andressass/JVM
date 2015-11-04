//#################################################################################################
/*! \file I_LECLASS.h
 *
 *  \brief Interface do Leitor e Exibidor de arquivos ".class".
 *
 *  Interface responsavel por prover os metodos relacionados a leitura e exibicao de um arquivo
 *  ".class".
 */
//##################################################################################################


#ifndef I_LECLASS
#define I_LECLASS
#if defined(LCLASS_SERV) && defined(ECLASS_SERV) && defined(OPCLASS_SERV)
#define EXT4
#else
#define EXT4 extern
#endif

#include<stdio.h>
#include<stdlib.h>
#include "IP_LECLASS.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por prover o servico de leitura de um arquivo ".class", preenchendo uma 
 * estrutura ArqClass.
 *
 * \param arq_class         Estrutura inicializada do tipo ArqClass a ser preenchida.
 * \param arquivo_entrada   Arquivo ".class" a ser lido.
 */
EXT4 void LECLASS_leitor(ArqClass* arq_class, const char* arquivo_entrada);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por prover o servico de exibicao de uma estrutura ".class"
 *
 * \param arq_class         Estrutura inicializada do tipo ArqClass a ser exibida.
 */
EXT4 void LECLASS_exibidor(ArqClass* arq_class);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por prover o servico de liberacao recursiva de uma estrutura ".class"
 *
 * \param arq_class         Estrutura inicializada do tipo ArqClass a ser liberada.
 */
EXT4 void LECLASS_free(ArqClass* arq_class);

#endif
