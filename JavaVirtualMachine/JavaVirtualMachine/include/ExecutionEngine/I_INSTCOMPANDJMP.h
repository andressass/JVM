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
 *  comparando se sao iguais e lanca uma flag na propria
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

//--------------------------------------------------------------------------------------------------
/*!
 *  Faz com que a execucao pule para a instrucao no endereco (pc + branchoffset),
 *  onde pc eh o endereco do opcode no bytecode e branchoffset eh um inteiro 16-bit (u2)
 *  que vem imediatamente após o opcode de goto no bytecode.
 *
 * \param Environment
 * \return void
 */
EXT15 void goto_(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 *  Faz com que a execucao pule para a instrucao no endereco (pc + branchoffset),
 *  onde pc eh o endereco do opcode no bytecode e branchoffset eh um inteiro 16-bit (u2)
 *  que vem imediatamente após o opcode de jsr no bytecode. Após isso, salva o endereco atual no operand stack
 *
 * \param Environment
 * \return void
 */
EXT15 void jsr(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 *  Pela o bytecode seguinte, esse bytecode contem um indice.
 *  Salva o indice no registrador do pc, fazendo com que a execucao continue dali
 *
 * \param Environment
 * \return void
 */
EXT15 void ret(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 * Pega o primeiro opcode entre 0 e 3 bytes após a instrução e salva como seu default,
 * após isso salva os 2 bytecodes seguintes como low e high respectivamente, depois pega
 * um indice salvo na pilha de operandos e compara com o high e o low. Se o indice não estiver
 * entre o low e o high, então o endereço de destino eh calculado como default+opcode inicial,
 * senao adiciona o primeiro offset em 'indice - low' ao opcode inicial e salva no pc
 *
 * \param Environment
 * \return void
 */
EXT15 void tableswitch(Environment *environment);
//--------------------------------------------------------------------------------------------------
/*!
 * Pega o primeiro opcode entre 0 e 3 bytes após a instrução e salva como seu default,
 * após isso salva os 2 bytecodes seguintes como low e high respectivamente, depois pega
 * um indice salvo na pilha de operandos e compara com o high e o low. Se o indice não estiver
 * entre o low e o high, então o endereço de destino eh calculado como default+opcode inicial,
 * senao adiciona o primeiro offset em 'indice - low' ao opcode inicial e salva no pc
 *
 * \param Environment
 * \return void
 */
EXT15 void lookupswitch(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 * Se o valor for nulo, os bytes seguintes são construidos para criar um offset, continuando
 * a execucao no offset do opcode dessa instrucao, senao continua no proximo endereco apos essa instrucao
 *
 * \param Environment
 * \return void
 */
EXT15 void ifnull(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 * Se o valor nao for nulo, os bytes seguintes são construidos para criar um offset, continuando
 * a execucao no offset do opcode dessa instrucao, senao continua no proximo endereco apos essa instrucao
 *
 * \param Environment
 * \return void
 */
EXT15 void ifnonnull(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 *  Faz com que a execucao pule para a instrucao no endereco (pc + branchoffset),
 *  onde pc eh o endereco do opcode no bytecode e branchoffset eh um inteiro 64-bit (u8)
 *  que vem imediatamente após o opcode de goto no bytecode. Mesma operacao de goto, so que 'wide' (offset maior)
 *
 * \param Environment
 * \return void
 */
EXT15 void goto_w(Environment *environment);

//--------------------------------------------------------------------------------------------------
/*!
 *  Faz com que a execucao pule para a instrucao no endereco (pc + branchoffset),
 *  onde pc eh o endereco do opcode no bytecode e branchoffset eh um inteiro 64-bit (u8)
 *  que vem imediatamente após o opcode de jsr no bytecode. Após isso, salva o endereco atual no operand stack
 *  Mesma operacao de jsr, so que 'wide' (com um offset maior)
 * \param Environment
 * \return void
 */
EXT15 void jsr_w(Environment *environment);

#endif /* I_INSTCOMPANDJMP_h */
