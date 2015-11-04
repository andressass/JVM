//#################################################################################################
/*! \file MP_LECLASS.c
 *
 *  \brief Modulo de Persistencia do Leitor e Exibidor de arquivos ".class".
 *
 *  Modulo responsavel pela implementacao dos metodos responsaveis pela manipulacao de arquivos
 *  ".class".
 */
//##################################################################################################

#define P_LECLASS_SERV

#include "../include/IP_LECLASS.h"


//--------------------------------------------------------------------------------------------------
FILE* obter_entrada(const char *arq){

   FILE *arquivo; // Arquivo a ser carregado e retornado

   arquivo = fopen(arq, "rb");

return arquivo;

}


//--------------------------------------------------------------------------------------------------
u1 u1Le(FILE *arquivo){

    return getc(arquivo);
}


//--------------------------------------------------------------------------------------------------
u2 u2Le(FILE *arquivo){
    
    u2 resultado = getc(arquivo);
    
    resultado = (resultado << 8) | (getc(arquivo));
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
u4 u4Le(FILE *arquivo){
    
    u4 resultado = u2Le(arquivo);

    resultado = (resultado << 16 | u2Le(arquivo));
    
    return resultado;
}
