//#################################################################################################
/*! \file M_DECODER.h
 *
 *  \brief Modulo do Decodificador da JVM.
 *
 *  Modulo responsavel pela implementacao os servicos relacionados a decodificacao de bytecodes
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
#include "../../include/ExecutionEngine/I_INSTLOADSTORAGE.h"


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
        case OP_nop:
            return nop;
            break;
        case OP_aconst_null:
            return aconst_null;
            break;
        case OP_iconst_m1:
            return iconst_m1;
            break;
        case OP_iconst_0:
            return iconst_0;
            break;
        case OP_iconst_1:
            return iconst_1;
            break;
        case OP_iconst_2:
            return iconst_2;
            break;
        case OP_iconst_3:
            return iconst_3;
            break;
        case OP_iconst_4:
            return iconst_4;
            break;
        case OP_iconst_5:
            return iconst_5;
            break;
        case OP_lconst_0:
            return lconst_0;
            break;
        case OP_lconst_1:
            return lconst_1;
            break;
        case OP_fconst_0:
            return fconst_0;
            break;
        case OP_fconst_1:
            return fconst_1;
            break;
        case OP_fconst_2:
            return fconst_2;
            break;
        case OP_dconst_0:
            return dconst_0;
            break;
        case OP_dconst_1:
            return dconst_1;
            break;
        case OP_bipush:
            return bipush;
            break;
        case OP_sipush:
            return sipush;
            break;
        case OP_ldc:
            return ldc;
            break;
        case OP_ldc_w:
            return ldc_w;
            break;
        case OP_ldc2_w:
            return ldc2_w;
            break;
        case OP_iload:
            return iload;
            break;
        case OP_lload:
            return lload;
            break;
        case OP_fload:
            return fload;
            break;
        case OP_dload:
            return dload;
            break;
        case OP_aload:
            return aload;
            break;
        case OP_iload_0:
            return iload_0;
            break;
        case OP_iload_1:
            return iload_1;
            break;
        case OP_iload_2:
            return iload_2;
            break;
        case OP_iload_3:
            return iload_3;
            break;
        case OP_lload_0:
            return lload_0;
            break;
        case OP_lload_1:
            return lload_1;
            break;
        case OP_lload_2:
            return lload_2;
            break;
        case OP_lload_3:
            return lload_3;
            break;
        case OP_fload_0:
            return fload_0;
            break;
        case OP_fload_1:
            return fload_1;
            break;
        case OP_fload_2:
            return fload_2;
            break;
        case OP_fload_3:
            return fload_3;
            break;
        case OP_dload_0:
            return dload_0;
            break;
        case OP_dload_1:
            return dload_1;
            break;
        case OP_dload_2:
            return dload_2;
            break;
        case OP_dload_3:
            return dload_3;
            break;
        case OP_aload_0:
            return aload_0;
            break;
        case OP_aload_1:
            return aload_1;
            break;
        case OP_aload_2:
            return aload_2;
            break;
        case OP_aload_3:
            return aload_3;
            break;
        case OP_iaload:
            return iaload;
            break;
        case OP_laload:
            return laload;
            break;
        case OP_faload:
            return faload;
            break;
        case OP_daload:
            return daload;
            break;
        case OP_aaload:
            return aaload;
            break;
        case OP_baload:
            return baload;
            break;
        case OP_caload:
            return caload;
            break;
        case OP_saload:
            return saload;
            break;
        default:
            break;
    }
    
    return NULL;

}
