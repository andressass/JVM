//#################################################################################################
/*! \file I_INTUSU.h
 *
 *  \brief Interface com o Usuário.
 *  
 *  Interface responsavel por prover os metodos relacionados a interacao com o usuario.
 */
//##################################################################################################

#ifndef I_INTUSU
#define I_INTUSU
#ifdef INTUSU_SERV
#define EXT5
#else
#define EXT5 extern
#endif

#include<stdio.h>
#include "I_LECLASS.h"

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel pela execucao das operacoes de interacao com o usuario.
 *
 * \param argc Numero de argumentos passados na chamada do programa.
 * \param argv Ponteiro para os argumentos passados na chamada do programa.
 */
EXT5 void INTUSU_executar(int argc, char ** argv);


#endif

