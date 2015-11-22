//#################################################################################################
/*! \file I_DECODER.h
 *
 *  \brief Interface do Decodificador da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a decodificacao de bytecodes
 *  em instrucoes
 */
//##################################################################################################

#ifndef I_DECODER_h
#define I_DECODER_h
#ifdef P_LECLASS_SERV
#define EXT7
#else
#define EXT7 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por retornar um ponteiro para uma funcao que realiza as operacoes de um 
 * bytecode
 *
 * \param bytecode  Bytecode a ser decodificado
 * \return Ponteiro para a instrucao referente ao bytecode 
 */
EXT7 instruction decode(u1 bytecode);


#endif /* I_DECODER_h */
