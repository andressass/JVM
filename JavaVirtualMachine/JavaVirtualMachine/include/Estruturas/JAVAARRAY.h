//#################################################################################################
/*! \file JAVAARRAY.h
 *
 *  \brief Biblioteca de arrays Java
 *
 *  Biblioteca responsavel por prover as definicoes e metodos relacionados aos arrays da JVM
 */
//##################################################################################################

#ifndef JAVAARRAY_h
#define JAVAARRAY_h

#ifdef JAVAARRAY_SERV
#define EXT23
#else
#define EXT23 extern
#endif

#include<stdio.h>
#include<stdlib.h>
#include "../../include/Estruturas/E_JVM.h"



//--------------------------------------------------------------------------------------------------
//Tags do Pool de Constantes

#define CONSTANT_ARRAY_Integer      1
#define CONSTANT_ARRAY_Float        2
#define CONSTANT_ARRAY_Long         3
#define CONSTANT_ARRAY_Double       4
#define CONSTANT_ARRAY_Reference    5
#define CONSTANT_ARRAY_Byte         6
#define CONSTANT_ARRAY_Boolean      7
#define CONSTANT_ARRAY_Char         8
#define CONSTANT_ARRAY_Short        9



//--------------------------------------------------------------------------------------------------
//! Estrutura de Array Java
/*!
 * Estrutura utilizada para a representacao de um Array Java
 */
typedef struct ArrayRef{
    u1 type;
    u2 length;
    u4* arrayAddress;
} JavaArray;



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo responsavel por inicializar e retornar uma estrutura de array java preenchida a partir
 * de um vetor de char
 *
 * \param value Value de tipo int, long, float, double, reference, byte, boolean, char ou short a
 * ser carregado na estrutura java array
 * \return estrutura JavaArray preenchida
 */
EXT23 JavaArray* newJavaArray(u1 n_type, u2 n_length, u4* n_arrayAddress);


#endif /* JAVAARRAY_h */
