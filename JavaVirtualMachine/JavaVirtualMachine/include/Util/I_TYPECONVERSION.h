//#################################################################################################
/*! \file I_TYPECONVERSION.h
 *
 *  \brief Interface de conversoes de tipos.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a conversao de tipos.
 */
//##################################################################################################

#ifndef I_TYPECONVERSION_h
#define I_TYPECONVERSION_h
#ifdef TYPECONVERSION
#define EXT22
#else
#define EXT22 extern
#endif

#include "../Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um double em big-endian order.
 *
 * \param high_bytes    Bytes de mais alta ordem.
 * \param low_bytes     Bytes de mais baixa ordem.
 */
EXT22 double u4ToDouble(u4 high_bytes, u4 low_bytes);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um float em big-endian order.
 *
 * \param bytes    Bytes em u4.
 */
EXT22 float u4ToFLoat(u4 bytes);


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que concatena 2bytes em um u2
 *
 * \param high_bytes    Bytes mais siginificativos.
 * \param low_bytes    Bytes menos siginificativos.
 * \return high_bytes << 8 | low_bytes
 */
EXT22 u2 concat2Bytes(u1 high_bytes, u1 low_bytes);




#endif /* I_TYPECONVERSION */
