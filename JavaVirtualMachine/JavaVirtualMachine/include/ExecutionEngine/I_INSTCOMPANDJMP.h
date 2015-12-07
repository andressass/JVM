//#################################################################################################
/*! \file I_INSTCOMPANDJMP.h
 *
 *  \brief Interface de instrucoes de comparacao e desvio da JVM.
 *
 *  Interface responsavel por disponibilizar os servicos relacionados a instrucoes que realizam 
 *  comparacoes e desvios.
 */
//##################################################################################################

#ifndef I_INSTCOMPANDJMP_h
#define I_INSTCOMPANDJMP_h
#ifdef M_INSTCOMPANDJMP_SERV
#define EXT15
#else
#define EXT15 extern
#endif

#include "../Estruturas/E_JVM.h"
#include "../Util/I_TYPECONVERSION.h"
#include "../MemoryUnit/I_MEMORYUNIT.h"

//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar dois longs vindos da pilha de operando 
 *  comparando se são iguais e lanca uma flag na propria
 *  pilha de operando
 *
 * \param Environment
 * \return void
 */
EXT15 void lcmp(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar dois floats vindos da pilha de operando 
 *  compara vendo se segundo eh menor que o primeiro lanca uma flag na propria
 *  pilha de operando
 *
 * \param Environment
 * \return void
 */

EXT15 void fcmpl(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar dois floats vindos da pilha de operando
 *  compara vendo se o segundo eh maior que o primeiro lanca uma flag na propria
 *  pilha de operando
 *
 * \param Environment
 * \return void
 */

EXT15 void fcmpg(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar dois doubles vindos da pilha de operando
 *  compara vendo se o segundo eh menor que o primeiro lanca uma flag na propria
 *  pilha de operando
 *
 * \param Environment
 * \return void
 */

EXT15 void dcmpl(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar dois doubles vindos da pilha de operando
 *  compara vendo se o segundo eh maior que o primeiro lanca uma flag na propria 
 *  pilha de operando
 *
 * \param Environment
 * \return void
 */

EXT15 void dcmpg(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar o topo da pilha de operando
 *  comparar com zero e lancar a flag na pilha de operando
 *
 * \param Environment
 * \return void
 */

EXT15 void ifeq(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar o topo da pilha de operando
 *  comparar com zero e lancar a flag na pilha de operando
 *
 * \param Environment
 * \return void
 */
EXT15 void ifne(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar o topo da pilha de operando
 *  comparar com zero e lancar a flag na pilha de operando
 *
 * \param Environment
 * \return void
 */
EXT15 void iflt(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar o topo da pilha de operando
 *  comparar com zero e lancar a flag na pilha de operando
 *
 * \param Environment
 * \return void
 */
EXT15 void ifge(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar o topo da pilha de operando
 *  comparar com zero e lancar a flag na pilha de operando
 *
 * \param Environment
 * \return void
 */
EXT15 void ifgt(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao responsavel por comparar o topo da pilha de operando
 *  comparar com zero e lancar a flag na pilha de operando
 *
 * \param Environment
 * \return void
 */
EXT15 void ifle(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se dois numeros sao iguais e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_icmpeq(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se dois numeros sao diferentes e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_icmpne(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se o segundo numero eh menor que o primeiro e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_icmplt(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se o segundo numero eh maior ou igual ao primeiro 
 *  e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_icmpge(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se o segundo numero eh maior que o primeiro e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_icmpgt(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se o segundo numero eh menor ou igual ao primeiro
 *  e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */

EXT15 void if_icmple(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se duas referencias sao iguais e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_acmpeq(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 *  Instrucao que compara se duas referencias sao iguais e salta para a posicao
 *  determinada pelo indice
 *
 * \param Environment
 * \return void
 */
EXT15 void if_acmpne(Environment *environment);

#endif /* I_INSTCOMPANDJMP_h */
