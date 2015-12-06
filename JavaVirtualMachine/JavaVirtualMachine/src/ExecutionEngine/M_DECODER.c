//#################################################################################################
/*! \file M_DECODER.c
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
#include <string.h>
#include "../../include/ExecutionEngine/I_DECODER.h"
#include "../../include/Estruturas/OPCODES.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ExecutionEngine/I_INSTLOGARITH.h"
#include "../../include/ExecutionEngine/I_INSTLOADSTORAGE.h"
#include "../../include/ExecutionEngine/I_INSTOBJANDINVOKE.h"
#include "../../include/ExecutionEngine/I_INSTCONVERSION.h"
#include "../../include/ExecutionEngine/I_INSTRETURN.h"
#include "../../include/ExecutionEngine/I_EXCEPTION.h"


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
        case OP_istore:
            return istore;
            break;
        case OP_lstore:
            return lstore;
            break;
        case OP_fstore:
            return fstore;
            break;
        case OP_dstore:
            return dstore;
            break;
        case OP_astore:
            return astore;
            break;
        case OP_istore_0:
            return istore_0;
            break;
        case OP_istore_1:
            return istore_1;
            break;
        case OP_istore_2:
            return istore_2;
            break;
        case OP_istore_3:
            return istore_3;
            break;
        case OP_lstore_0:
            return lstore_0;
            break;
        case OP_lstore_1:
            return lstore_1;
            break;
        case OP_lstore_2:
            return lstore_2;
            break;
        case OP_lstore_3:
            return lstore_3;
            break;
        case OP_fstore_0:
            return fstore_0;
            break;
        case OP_fstore_1:
            return fstore_1;
            break;
        case OP_fstore_2:
            return fstore_2;
            break;
        case OP_fstore_3:
            return fstore_3;
            break;
        case OP_dstore_0:
            return dstore_0;
            break;
        case OP_dstore_1:
            return dstore_1;
            break;
        case OP_dstore_2:
            return dstore_2;
            break;
        case OP_dstore_3:
            return dstore_3;
            break;
        case OP_astore_0:
            return astore_0;
            break;
        case OP_astore_1:
            return astore_1;
            break;
        case OP_astore_2:
            return astore_2;
            break;
        case OP_astore_3:
            return astore_3;
            break;
        case OP_iastore:
            return iastore;
            break;
        case OP_lastore:
            return lastore;
            break;
        case OP_fastore:
            return fastore;
            break;
        case OP_dastore:
            return dastore;
            break;
        case OP_aastore:
            return aastore;
            break;
        case OP_bastore:
            return bastore;
            break;
        case OP_castore:
            return castore;
            break;
        case OP_sastore:
            return sastore;
            break;
        case OP_wide:
            return wide;
            break;
        case OP_dup:
            return Dup;
        case OP_pop:
            return pop;
            break;
        case OP_getstatic:
            return getstatic;
            break;
        case OP_putstatic:
            return putstatic;
            break;
        case OP_getfield:
            return getfield;
            break;
        case OP_putfield:
            return putfield;
            break;
        case OP_invokevirtual:
            return invokevirtual;
            break;
        case OP_invokespecial:
            return invokespecial;
            break;
        case OP_invokestatic:
            return invokestatic;
            break;
        case OP_invokeinterface:
            return invokeinterface;
            break;
        case OP_new:
            return New;
            break;
        case OP_ireturn:
            return ireturn;
            break;
        case OP_lreturn:
            return lreturn;
            break;
        case OP_freturn:
            return freturn;
            break;
        case OP_dreturn:
            return dreturn;
            break;
        case OP_areturn:
            return areturn;
            break;
        case OP_return:
            return return_;
            break;
        case OP_i2l:
            return i2l;
            break;
        case OP_i2f:
            return i2f;
            break;
        case OP_i2d:
            return i2d;
            break;
        case OP_l2i:
            return l2i;
            break;
        case OP_l2f:
            return l2f;
            break;
        case OP_l2d:
            return l2d;
            break;
        case OP_f2i:
            return f2i;
            break;
        case OP_f2l:
            return f2l;
            break;
        case OP_f2d:
            return f2d;
            break;
        case OP_d2i:
            return d2i;
            break;
        case OP_d2l:
            return d2l;
            break;
        case OP_d2f:
            return d2f;
            break;
        case OP_i2b:
            return i2b;
            break;
        case OP_i2c:
            return i2c;
            break;
        case OP_i2s:
            return i2s;
            break;
        default:
            break;
    }
    char buffer[100];
    sprintf(buffer, "Instrucao \"%s\" nao encontrada.", getOpcodeName(bytecode));
    JVMstopAbrupt(buffer);
    return NULL;

}
