//#################################################################################################
/*! \file M_DECODER.h
 *
 *  \brief Modulo do Decodificador da JVM.
 *
 *  Interface responsavel pela implementacao os servicos relacionados a decodificacao de bytecodes
 *  em instrucoes.
 */
//##################################################################################################

#define DECODER_SERV

#include <stdio.h>
#include <stdlib.h>
#include "../../include/ExecutionEngine/I_DECODER.h"
#include "../../include/Estruturas/OPCODES.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ExecutionEngine/I_INSTLOGARITH.h"

//Gambiarra de instrucao
void iadd_GAMBIARRA(Thread* thread){
    
    int a = popFromOperandStack(thread);
    int b = popFromOperandStack(thread);
    
    pushInOperandStack(thread, a+b);
}

//--------------------------------------------------------------------------------------------------
instruction decode(u1 bytecode){
    
    switch (bytecode) {
        case OP_iadd:
            return iadd;
            break;
        case OP_ladd:
            return ladd;
            break;
        case OP_fadd:
            return fadd;
            break;
        case OP_dadd:
            return dadd;
            break;
        case OP_isub:
            return isub;
            break;
        case OP_lsub:
            return lsub;
            break;
        case OP_fsub:
            return fsub;
            break;
        case OP_dsub:
            return dsub;
            break;
        case OP_imul:
            return imul;
            break;
        case OP_lmul:
            return lmul;
            break;
        case OP_fmul:
            return fmul;
            break;
        case OP_dmul:
            return dmul;
            break;
        case OP_idiv:
            return idiv;
            break;
        case OP_ldiv:
            return Ldiv;
            break;
        case OP_fdiv:
            return fdiv;
            break;
        case OP_ddiv:
            return ddiv;
            break;
        case OP_irem:
            return irem;
            break;
        case OP_lrem:
            return lrem;
            break;
        case OP_frem:
            return frem;
            break;
        case OP_drem:
            return Drem;
            break;
        case OP_ineg:
            return ineg;
            break;
        case OP_lneg:
            return lneg;
            break;
        case OP_fneg:
            return fneg;
            break;
        case OP_dneg:
            return dneg;
            break;
        case OP_ishl:
            return ishl;
            break;
        case OP_lshl:
            return lshl;
            break;
        case OP_ishr:
            return ishr;
            break;
        case OP_lshr:
            return lshr;
            break;
        case OP_iushr:
            return iushr;
            break;
        case OP_lushr:
            return lushr;
            break;
        case OP_iand:
            return iand;
            break;
        case OP_land:
            return land;
            break;
        case OP_ior:
            return ior;
            break;
        case OP_lor:
            return lor;
            break;
        case OP_ixor:
            return ixor;
            break;
        case OP_lxor:
            return lxor;
            break;
        case OP_iinc:
            return iinc;
            break;
        default:
            break;
    }
    
    return NULL;

}
