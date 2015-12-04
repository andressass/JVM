//#################################################################################################
/*! \file M_TYPECONVERSION.h
 *
 *  \brief Interface de conversoes de tipos.
 *
 *  Modulo responsavel pela implementacao dos servicos relacionados a conversao de tipos.
 */
//##################################################################################################

#define TYPECONVERSION_SERV


#include "../../include/Estruturas/OPCODES.h"
#include <string.h>

//--------------------------------------------------------------------------------------------------
double u4ToDouble(u4 high_bytes, u4 low_bytes){
    double resultado;
    unsigned char b[8]; //vetor de 8 Bytes
    
    //Trocamos a ordem dos bytes salvando no vetor de bytes
    for (int i = 0; i < 4; i++) b[i] = low_bytes >> i * 8;
    for (int i = 4; i < 8; i++) b[i] = high_bytes >> i * 8;
    
    
    //Copiamos os bytes do vetor de bytes para o float
    memcpy(&resultado, &b, sizeof(resultado));
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
float u4ToFLoat(u4 bytes){
    
    float resultado;
    unsigned char b[4]; //vetor de 4 Bytes
    
    //Trocamos a ordem dos bytes salvando no vetor de bytes
    for (int i = 0; i < 4; i++) b[i] = bytes >> i * 8;
    
    //Copiamos os bytes do vetor de bytes para o float
    memcpy(&resultado, &b, sizeof(resultado));
    
    return resultado;
}

