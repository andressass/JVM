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
#define EXT21
#else
#define EXT21 extern
#endif


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um double em big-endian order.
 *
 * \param high_bytes    Bytes de mais alta ordem.
 * \param low_bytes     Bytes de mais baixa ordem.
 */
double u4ToDouble(u4 high_bytes, u4 low_bytes);

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um float em big-endian order.
 *
 * \param bytes    Bytes em u4.
 */
float u4ToFLoat(u4 bytes);

#endif /* I_TYPECONVERSION */
