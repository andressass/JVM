//#################################################################################################
/*! \file OPCODES.h
 *
 *  \brief Biblioteca de servicos de Opcodes
 *
 *  Bliblioteca responsavel por prover as definicoes e metodos relacionados aos opcodes de uma JVM
 */
//##################################################################################################

#ifndef OPCODES_H
#define OPCODES_H

#include<stdio.h>
#include<stdlib.h>
#include "../include/E_LECLASS.h"


//--------------------------------------------------------------------------------------------------
// Definicoes de opcodes

#define OP_aaload 0x32
#define OP_aastore 0x53
#define OP_aconst_null 0x1
#define OP_aload 0x19
#define OP_aload_0 0x2a
#define OP_aload_1 0x2b
#define OP_aload_2 0x2c
#define OP_aload_3 0x2d
#define OP_anewarray 0xbd
#define OP_areturn 0xb0
#define OP_arraylength 0xbe
#define OP_astore 0x3a
#define OP_astore_0 0x4b
#define OP_astore_1 0x4c
#define OP_astore_2 0x4d
#define OP_astore_3 0x4e
#define OP_athrow 0xbf
#define OP_baload 0x33
#define OP_bastore 0x54
#define OP_bipush 0x10
#define OP_breakpoint 0xca
#define OP_caload 0x34
#define OP_castore 0x55
#define OP_checkcast 0xc0
#define OP_d2f 0x90
#define OP_d2i 0x8e
#define OP_d2l 0x8f
#define OP_dadd 0x63
#define OP_daload 0x31
#define OP_dastore 0x52
#define OP_dcmpg 0x98
#define OP_dcmpl 0x97
#define OP_dconst_0 0x0e
#define OP_dconst_1 0x0f
#define OP_ddiv 0x6f
#define OP_dload 0x18
#define OP_dload_0 0x26
#define OP_dload_1 0x27
#define OP_dload_2 0x28
#define OP_dload_3 0x29
#define OP_dmul 0x6b
#define OP_dneg 0x77
#define OP_drem 0x73
#define OP_dreturn 0xaf
#define OP_dstore 0x39
#define OP_dstore_0 0x47
#define OP_dstore_1 0x48
#define OP_dstore_2 0x49
#define OP_dstore_3 0x4a
#define OP_dsub 0x67
#define OP_dup 0x59
#define OP_dup_x1 0x5a
#define OP_dup_x2 0x5b
#define OP_dup2 0x5c
#define OP_dup2_x1 0x5d
#define OP_dup2_x2 0x5e
#define OP_f2d 0x8d
#define OP_f2i 0x8b
#define OP_f2l 0x8c
#define OP_fadd 0x62
#define OP_faload 0x30
#define OP_fastore 0x51
#define OP_fcmpg 0x96
#define OP_fcmpl 0x95
#define OP_fconst_0 0x0b
#define OP_fconst_1 0x0c
#define OP_fconst_2 0x0d
#define OP_fdiv 0x6e
#define OP_fload 0x17
#define OP_fload_0 0x22
#define OP_fload_1 0x23
#define OP_fload_2 0x24
#define OP_fload_3 0x25
#define OP_fmul 0x6a
#define OP_fneg 0x76
#define OP_frem 0x72
#define OP_freturn 0xae
#define OP_fstore 0x38
#define OP_fstore_0 0x43
#define OP_fstore_1 0x44
#define OP_fstore_2 0x45
#define OP_fstore_3 0x46
#define OP_fsub 0x66
#define OP_getfield 0xb4
#define OP_getstatic 0xb2
#define OP_goto 0xa7
#define OP_goto_w 0xc8
#define OP_i2b 0x91
#define OP_i2c 0x92
#define OP_i2d 0x87
#define OP_i2f 0x86
#define OP_i2l 0x85
#define OP_i2s 0x93
#define OP_iadd 0x60
#define OP_iaload 0x2e
#define OP_iand 0x7e
#define OP_iastore 0x4f
#define OP_iconst_m1 0x2
#define OP_iconst_0 0x3
#define OP_iconst_1 0x4
#define OP_iconst_2 0x5
#define OP_iconst_3 0x6
#define OP_iconst_4 0x7
#define OP_iconst_5 0x8
#define OP_idiv 0x6c
#define OP_if_acmpeq 0xa5
#define OP_if_acmpne 0xa6
#define OP_if_icmpeq 0x9f
#define OP_if_icmpge 0xa2
#define OP_if_icmpgt 0xa3
#define OP_if_icmple 0xa4
#define OP_if_icmplt 0xa1
#define OP_if_icmpne 0xa0
#define OP_ifeq 0x99
#define OP_ifge 0x9c
#define OP_ifgt 0x9d
#define OP_ifle 0x9e
#define OP_iflt 0x9b
#define OP_ifne 0x9a
#define OP_ifnonnull 0xc7
#define OP_ifnull 0xc6
#define OP_iinc 0x84
#define OP_iload 0x15
#define OP_iload_0 0x1a
#define OP_iload_1 0x1b
#define OP_iload_2 0x1c
#define OP_iload_3 0x1d
#define OP_impdep1 0xfe
#define OP_impdep2 0xff
#define OP_imul 0x68
#define OP_ineg 0x74
#define OP_instanceof 0xc1
#define OP_invokedynamic 0xba
#define OP_invokeinterface 0xb9
#define OP_invokespecial 0xb7
#define OP_invokestatic 0xb8
#define OP_invokevirtual 0xb6
#define OP_ior 0x80
#define OP_irem 0x70
#define OP_ireturn 0xac
#define OP_ishl 0x78
#define OP_ishr 0x7a
#define OP_istore 0x36
#define OP_istore_0 0x3b
#define OP_istore_1 0x3c
#define OP_istore_2 0x3d
#define OP_istore_3 0x3e
#define OP_isub 0x64
#define OP_iushr 0x7c
#define OP_ixor 0x82
#define OP_jsr 0xa8
#define OP_jsr_w 0xc9
#define OP_l2d 0x8a
#define OP_l2f 0x89
#define OP_l2i 0x88
#define OP_ladd 0x61
#define OP_laload 0x2f
#define OP_land 0x7f
#define OP_lastore 0x50
#define OP_lcmp 0x94
#define OP_lconst_0 0x9
#define OP_lconst_1 0x0a
#define OP_ldc 0x12
#define OP_ldc_w 0x13
#define OP_ldc2_w 0x14
#define OP_ldiv 0x6d
#define OP_lload 0x16
#define OP_lload_0 0x1e
#define OP_lload_1 0x1f
#define OP_lload_2 0x20
#define OP_lload_3 0x21
#define OP_lmul 0x69
#define OP_lneg 0x75
#define OP_lookupswitch 0xab
#define OP_lor 0x81
#define OP_lrem 0x71
#define OP_lreturn 0xad
#define OP_lshl 0x79
#define OP_lshr 0x7b
#define OP_lstore 0x37
#define OP_lstore_0 0x3f
#define OP_lstore_1 0x40
#define OP_lstore_2 0x41
#define OP_lstore_3 0x42
#define OP_lsub 0x65
#define OP_lushr 0x7d
#define OP_lxor 0x83
#define OP_monitorenter 0xc2
#define OP_monitorexit 0xc3
#define OP_multianewarray 0xc5
#define OP_new 0xbb
#define OP_newarray 0xbc
#define OP_nop 0x0
#define OP_pop 0x57
#define OP_pop2 0x58
#define OP_putfield 0xb5
#define OP_putstatic 0xb3
#define OP_ret 0xa9
#define OP_return 0xb1
#define OP_saload 0x35
#define OP_sastore 0x56
#define OP_sipush 0x11
#define OP_swap 0x5f
#define OP_tableswitch 0xaa
#define OP_wide 0xc4


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que retorna uma string com o nome do opcode
 *
 * \param u1 opcode Codigo do opcode.
 * \return String contendo o nome do opcode.
 */
char* getOpcodeName(u1 opcode){
    char * op_name = (char* ) malloc(20* sizeof(char));
    switch (opcode) {
        case OP_aaload:
            op_name = "aaload";
            break;
        case OP_aastore:
            op_name = "aastore";
            break;
        case OP_aconst_null:
            op_name = "aconst_null";
            break;
        case OP_aload:
            op_name = "aload";
            break;
        case OP_aload_0:
            op_name = "aload_0";
            break;
        case OP_aload_1:
            op_name = "aload_1";
            break;
        case OP_aload_2:
            op_name = "aload_2";
            break;
        case OP_aload_3:
            op_name = "aload_3";
            break;
        case OP_anewarray:
            op_name = "anewarray";
            break;
        case OP_areturn:
            op_name = "areturn";
            break;
        case OP_arraylength:
            op_name = "arraylength";
            break;
        case OP_astore:
            op_name = "astore";
            break;
        case OP_astore_0:
            op_name = "astore_0";
            break;
        case OP_astore_1:
            op_name = "astore_1";
            break;
        case OP_astore_2:
            op_name = "astore_2";
            break;
        case OP_astore_3:
            op_name = "astore_3";
            break;
        case OP_athrow:
            op_name = "athrow";
            break;
        case OP_baload:
            op_name = "baload";
            break;
        case OP_bastore:
            op_name = "bastore";
            break;
        case OP_bipush:
            op_name = "bipush";
            break;
        case OP_breakpoint:
            op_name = "breakpoint";
            break;
        case OP_caload:
            op_name = "caload";
            break;
        case OP_castore:
            op_name = "castore";
            break;
        case OP_checkcast:
            op_name = "checkcast";
            break;
        case OP_d2f:
            op_name = "d2f";
            break;
        case OP_d2i:
            op_name = "d2i";
            break;
        case OP_d2l:
            op_name = "d2l";
            break;
        case OP_dadd:
            op_name = "dadd";
            break;
        case OP_daload:
            op_name = "daload";
            break;
        case OP_dastore:
            op_name = "dastore";
            break;
        case OP_dcmpg:
            op_name = "dcmpg";
            break;
        case OP_dcmpl:
            op_name = "dcmpl";
            break;
        case OP_dconst_0:
            op_name = "dconst_0";
            break;
        case OP_dconst_1:
            op_name = "dconst_1";
            break;
        case OP_ddiv:
            op_name = "ddiv";
            break;
        case OP_dload:
            op_name = "dload";
            break;
        case OP_dload_0:
            op_name = "dload_0";
            break;
        case OP_dload_1:
            op_name = "dload_1";
            break;
        case OP_dload_2:
            op_name = "dload_2";
            break;
        case OP_dload_3:
            op_name = "dload_3";
            break;
        case OP_dmul:
            op_name = "dmul";
            break;
        case OP_dneg:
            op_name = "dneg";
            break;
        case OP_drem:
            op_name = "drem";
            break;
        case OP_dreturn:
            op_name = "dreturn";
            break;
        case OP_dstore:
            op_name = "dstore";
            break;
        case OP_dstore_0:
            op_name = "dstore_0";
            break;
        case OP_dstore_1:
            op_name = "dstore_1";
            break;
        case OP_dstore_2:
            op_name = "dstore_2";
            break;
        case OP_dstore_3:
            op_name = "dstore_3";
            break;
        case OP_dsub:
            op_name = "dsub";
            break;
        case OP_dup:
            op_name = "dup";
            break;
        case OP_dup_x1:
            op_name = "dup_x1";
            break;
        case OP_dup_x2:
            op_name = "dup_x2";
            break;
        case OP_dup2:
            op_name = "dup2";
            break;
        case OP_dup2_x1:
            op_name = "dup2_x1";
            break;
        case OP_dup2_x2:
            op_name = "dup2_x2";
            break;
        case OP_f2d:
            op_name = "f2d";
            break;
        case OP_f2i:
            op_name = "f2i";
            break;
        case OP_f2l:
            op_name = "f2l";
            break;
        case OP_fadd:
            op_name = "fadd";
            break;
        case OP_faload:
            op_name = "faload";
            break;
        case OP_fastore:
            op_name = "fastore";
            break;
        case OP_fcmpg:
            op_name = "fcmpg";
            break;
        case OP_fcmpl:
            op_name = "fcmpl";
            break;
        case OP_fconst_0:
            op_name = "fconst_0";
            break;
        case OP_fconst_1:
            op_name = "fconst_1";
            break;
        case OP_fconst_2:
            op_name = "fconst_2";
            break;
        case OP_fdiv:
            op_name = "fdiv";
            break;
        case OP_fload:
            op_name = "fload";
            break;
        case OP_fload_0:
            op_name = "fload_0";
            break;
        case OP_fload_1:
            op_name = "fload_1";
            break;
        case OP_fload_2:
            op_name = "fload_2";
            break;
        case OP_fload_3:
            op_name = "fload_3";
            break;
        case OP_fmul:
            op_name = "fmul";
            break;
        case OP_fneg:
            op_name = "fneg";
            break;
        case OP_frem:
            op_name = "frem";
            break;
        case OP_freturn:
            op_name = "freturn";
            break;
        case OP_fstore:
            op_name = "fstore";
            break;
        case OP_fstore_0:
            op_name = "fstore_0";
            break;
        case OP_fstore_1:
            op_name = "fstore_1";
            break;
        case OP_fstore_2:
            op_name = "fstore_2";
            break;
        case OP_fstore_3:
            op_name = "fstore_3";
            break;
        case OP_fsub:
            op_name = "fsub";
            break;
        case OP_getfield:
            op_name = "getfield";
            break;
        case OP_getstatic:
            op_name = "getstatic";
            break;
        case OP_goto:
            op_name = "goto";
            break;
        case OP_goto_w:
            op_name = "goto_w";
            break;
        case OP_i2b:
            op_name = "i2b";
            break;
        case OP_i2c:
            op_name = "i2c";
            break;
        case OP_i2d:
            op_name = "i2d";
            break;
        case OP_i2f:
            op_name = "i2f";
            break;
        case OP_i2l:
            op_name = "i2l";
            break;
        case OP_i2s:
            op_name = "i2s";
            break;
        case OP_iadd:
            op_name = "iadd";
            break;
        case OP_iaload:
            op_name = "iaload";
            break;
        case OP_iand:
            op_name = "iand";
            break;
        case OP_iastore:
            op_name = "iastore";
            break;
        case OP_iconst_m1:
            op_name = "iconst_m1";
            break;
        case OP_iconst_0:
            op_name = "iconst_0";
            break;
        case OP_iconst_1:
            op_name = "iconst_1";
            break;
        case OP_iconst_2:
            op_name = "iconst_2";
            break;
        case OP_iconst_3:
            op_name = "iconst_3";
            break;
        case OP_iconst_4:
            op_name = "iconst_4";
            break;
        case OP_iconst_5:
            op_name = "iconst_5";
            break;
        case OP_idiv:
            op_name = "idiv";
            break;
        case OP_if_acmpeq:
            op_name = "if_acmpeq";
            break;
        case OP_if_acmpne:
            op_name = "if_acmpne";
            break;
        case OP_if_icmpeq:
            op_name = "if_icmpeq";
            break;
        case OP_if_icmpge:
            op_name = "if_icmpge";
            break;
        case OP_if_icmpgt:
            op_name = "if_icmpgt";
            break;
        case OP_if_icmple:
            op_name = "if_icmple";
            break;
        case OP_if_icmplt:
            op_name = "if_icmplt";
            break;
        case OP_if_icmpne:
            op_name = "if_icmpne";
            break;
        case OP_ifeq:
            op_name = "ifeq";
            break;
        case OP_ifge:
            op_name = "ifge";
            break;
        case OP_ifgt:
            op_name = "ifgt";
            break;
        case OP_ifle:
            op_name = "ifle";
            break;
        case OP_iflt:
            op_name = "iflt";
            break;
        case OP_ifne:
            op_name = "ifne";
            break;
        case OP_ifnonnull:
            op_name = "ifnonnull";
            break;
        case OP_ifnull:
            op_name = "ifnull";
            break;
        case OP_iinc:
            op_name = "iinc";
            break;
        case OP_iload:
            op_name = "iload";
            break;
        case OP_iload_0:
            op_name = "iload_0";
            break;
        case OP_iload_1:
            op_name = "iload_1";
            break;
        case OP_iload_2:
            op_name = "iload_2";
            break;
        case OP_iload_3:
            op_name = "iload_3";
            break;
        case OP_impdep1:
            op_name = "impdep1";
            break;
        case OP_impdep2:
            op_name = "impdep2";
            break;
        case OP_imul:
            op_name = "imul";
            break;
        case OP_ineg:
            op_name = "ineg";
            break;
        case OP_instanceof:
            op_name = "instanceof";
            break;
        case OP_invokedynamic:
            op_name = "invokedynamic";
            break;
        case OP_invokeinterface:
            op_name = "invokeinterface";
            break;
        case OP_invokespecial:
            op_name = "invokespecial";
            break;
        case OP_invokestatic:
            op_name = "invokestatic";
            break;
        case OP_invokevirtual:
            op_name = "invokevirtual";
            break;
        case OP_ior:
            op_name = "ior";
            break;
        case OP_irem:
            op_name = "irem";
            break;
        case OP_ireturn:
            op_name = "ireturn";
            break;
        case OP_ishl:
            op_name = "ishl";
            break;
        case OP_ishr:
            op_name = "ishr";
            break;
        case OP_istore:
            op_name = "istore";
            break;
        case OP_istore_0:
            op_name = "istore_0";
            break;
        case OP_istore_1:
            op_name = "istore_1";
            break;
        case OP_istore_2:
            op_name = "istore_2";
            break;
        case OP_istore_3:
            op_name = "istore_3";
            break;
        case OP_isub:
            op_name = "isub";
            break;
        case OP_iushr:
            op_name = "iushr";
            break;
        case OP_ixor:
            op_name = "ixor";
            break;
        case OP_jsr:
            op_name = "jsr";
            break;
        case OP_jsr_w:
            op_name = "jsr_w";
            break;
        case OP_l2d:
            op_name = "l2d";
            break;
        case OP_l2f:
            op_name = "l2f";
            break;
        case OP_l2i:
            op_name = "l2i";
            break;
        case OP_ladd:
            op_name = "ladd";
            break;
        case OP_laload:
            op_name = "laload";
            break;
        case OP_land:
            op_name = "land";
            break;
        case OP_lastore:
            op_name = "lastore";
            break;
        case OP_lcmp:
            op_name = "lcmp";
            break;
        case OP_lconst_0:
            op_name = "lconst_0";
            break;
        case OP_lconst_1:
            op_name = "lconst_1";
            break;
        case OP_ldc:
            op_name = "ldc";
            break;
        case OP_ldc_w:
            op_name = "ldc_w";
            break;
        case OP_ldc2_w:
            op_name = "ldc2_w";
            break;
        case OP_ldiv:
            op_name = "ldiv";
            break;
        case OP_lload:
            op_name = "lload";
            break;
        case OP_lload_0:
            op_name = "lload_0";
            break;
        case OP_lload_1:
            op_name = "lload_1";
            break;
        case OP_lload_2:
            op_name = "lload_2";
            break;
        case OP_lload_3:
            op_name = "lload_3";
            break;
        case OP_lmul:
            op_name = "lmul";
            break;
        case OP_lneg:
            op_name = "lneg";
            break;
        case OP_lookupswitch:
            op_name = "lookupswitch";
            break;
        case OP_lor:
            op_name = "lor";
            break;
        case OP_lrem:
            op_name = "lrem";
            break;
        case OP_lreturn:
            op_name = "lreturn";
            break;
        case OP_lshl:
            op_name = "lshl";
            break;
        case OP_lshr:
            op_name = "lshr";
            break;
        case OP_lstore:
            op_name = "lstore";
            break;
        case OP_lstore_0:
            op_name = "lstore_0";
            break;
        case OP_lstore_1:
            op_name = "lstore_1";
            break;
        case OP_lstore_2:
            op_name = "lstore_2";
            break;
        case OP_lstore_3:
            op_name = "lstore_3";
            break;
        case OP_lsub:
            op_name = "lsub";
            break;
        case OP_lushr:
            op_name = "lushr";
            break;
        case OP_lxor:
            op_name = "lxor";
            break;
        case OP_monitorenter:
            op_name = "monitorenter";
            break;
        case OP_monitorexit:
            op_name = "monitorexit";
            break;
        case OP_multianewarray:
            op_name = "multianewarray";
            break;
        case OP_new:
            op_name = "new";
            break;
        case OP_newarray:
            op_name = "newarray";
            break;
        case OP_nop:
            op_name = "nop";
            break;
        case OP_pop:
            op_name = "pop";
            break;
        case OP_pop2:
            op_name = "pop2";
            break;
        case OP_putfield:
            op_name = "putfield";
            break;
        case OP_putstatic:
            op_name = "putstatic";
            break;
        case OP_ret:
            op_name = "ret";
            break;
        case OP_return:
            op_name = "return";
            break;
        case OP_saload:
            op_name = "saload";
            break;
        case OP_sastore:
            op_name = "sastore";
            break;
        case OP_sipush:
            op_name = "sipush";
            break;
        case OP_swap:
            op_name = "swap";
            break;
        case OP_tableswitch:
            op_name = "tableswitch";
            break;
        case OP_wide:
            op_name = "wide";
        default:
            op_name = "";
            break;
    }
    return op_name;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que retorna um short com a quantidade de atributos (bytes adicionais) do opcode
 *
 * \param u1 opcode Codigo do opcode.
 * \return Quantidade de bytes adicionais exigidos pelo opcode (-1 significa tamanho variavel).
 */
short getOpcodeAttributesNumber(u1 opcode){
    short result = -1;
    
    switch (opcode) {
            
        case OP_aaload:
            result = 0;
            break; 
       case OP_aastore:
            result = 0;
            break; 
       case OP_aconst_null:
            result = 0;
            break; 
       case OP_aload:
            result = 1;
            break; 
       case OP_aload_0:
            result = 0;
            break; 
       case OP_aload_1:
            result = 0;
            break; 
       case OP_aload_2:
            result = 0;
            break; 
       case OP_aload_3:
            result = 0;
            break; 
       case OP_anewarray:
            result = 2;
            break; 
       case OP_areturn:
            result = 0;
            break; 
       case OP_arraylength:
            result = 0;
            break; 
       case OP_astore:
            result = 1;
            break; 
       case OP_astore_0:
            result = 0;
            break; 
       case OP_astore_1:
            result = 0;
            break; 
       case OP_astore_2:
            result = 0;
            break; 
       case OP_astore_3:
            result = 0;
            break; 
       case OP_athrow:
            result = 0;
            break; 
       case OP_baload:
            result = 0;
            break; 
       case OP_bastore:
            result = 0;
            break; 
       case OP_bipush:
            result = 1;
            break; 
       case OP_breakpoint:
            result = 0;
            break; 
       case OP_caload:
            result = 0;
            break; 
       case OP_castore:
            result = 0;
            break; 
       case OP_checkcast:
            result = 2;
            break; 
       case OP_d2f:
            result = 0;
            break; 
       case OP_d2i:
            result = 0;
            break; 
       case OP_d2l:
            result = 0;
            break; 
       case OP_dadd:
            result = 0;
            break; 
       case OP_daload:
            result = 0;
            break; 
       case OP_dastore:
            result = 0;
            break; 
       case OP_dcmpg:
            result = 0;
            break; 
       case OP_dcmpl:
            result = 0;
            break; 
       case OP_dconst_0:
            result = 0;
            break; 
       case OP_dconst_1:
            result = 0;
            break; 
       case OP_ddiv:
            result = 0;
            break; 
       case OP_dload:
            result = 1;
            break; 
       case OP_dload_0:
            result = 0;
            break; 
       case OP_dload_1:
            result = 0;
            break; 
       case OP_dload_2:
            result = 0;
            break; 
       case OP_dload_3:
            result = 0;
            break; 
       case OP_dmul:
            result = 0;
            break; 
       case OP_dneg:
            result = 0;
            break; 
       case OP_drem:
            result = 0;
            break; 
       case OP_dreturn:
            result = 0;
            break; 
       case OP_dstore:
            result = 1;
            break; 
       case OP_dstore_0:
            result = 0;
            break; 
       case OP_dstore_1:
            result = 0;
            break; 
       case OP_dstore_2:
            result = 0;
            break; 
       case OP_dstore_3:
            result = 0;
            break; 
       case OP_dsub:
            result = 0;
            break; 
       case OP_dup:
            result = 0;
            break; 
       case OP_dup_x1:
            result = 0;
            break; 
       case OP_dup_x2:
            result = 0;
            break; 
       case OP_dup2:
            result = 0;
            break; 
       case OP_dup2_x1:
            result = 0;
            break; 
       case OP_dup2_x2:
            result = 0;
            break; 
       case OP_f2d:
            result = 0;
            break; 
       case OP_f2i:
            result = 0;
            break; 
       case OP_f2l:
            result = 0;
            break; 
       case OP_fadd:
            result = 0;
            break; 
       case OP_faload:
            result = 0;
            break; 
       case OP_fastore:
            result = 0;
            break; 
       case OP_fcmpg:
            result = 0;
            break; 
       case OP_fcmpl:
            result = 0;
            break; 
       case OP_fconst_0:
            result = 0;
            break; 
       case OP_fconst_1:
            result = 0;
            break; 
       case OP_fconst_2:
            result = 0;
            break; 
       case OP_fdiv:
            result = 0;
            break; 
       case OP_fload:
            result = 1;
            break; 
       case OP_fload_0:
            result = 0;
            break; 
       case OP_fload_1:
            result = 0;
            break; 
       case OP_fload_2:
            result = 0;
            break; 
       case OP_fload_3:
            result = 0;
            break; 
       case OP_fmul:
            result = 0;
            break; 
       case OP_fneg:
            result = 0;
            break; 
       case OP_frem:
            result = 0;
            break; 
       case OP_freturn:
            result = 0;
            break; 
       case OP_fstore:
            result = 1;
            break; 
       case OP_fstore_0:
            result = 0;
            break; 
       case OP_fstore_1:
            result = 0;
            break; 
       case OP_fstore_2:
            result = 0;
            break; 
       case OP_fstore_3:
            result = 0;
            break; 
       case OP_fsub:
            result = 0;
            break; 
       case OP_getfield:
            result = 2;
            break; 
       case OP_getstatic:
            result = 2;
            break; 
       case OP_goto:
            result = 2;
            break; 
       case OP_goto_w:
            result = 4;
            break; 
       case OP_i2b:
            result = 0;
            break; 
       case OP_i2c:
            result = 0;
            break; 
       case OP_i2d:
            result = 0;
            break; 
       case OP_i2f:
            result = 0;
            break; 
       case OP_i2l:
            result = 0;
            break; 
       case OP_i2s:
            result = 0;
            break; 
       case OP_iadd:
            result = 0;
            break; 
       case OP_iaload:
            result = 0;
            break; 
       case OP_iand:
            result = 0;
            break; 
       case OP_iastore:
            result = 0;
            break; 
       case OP_iconst_m1:
            result = 0;
            break; 
       case OP_iconst_0:
            result = 0;
            break; 
       case OP_iconst_1:
            result = 0;
            break; 
       case OP_iconst_2:
            result = 0;
            break; 
       case OP_iconst_3:
            result = 0;
            break; 
       case OP_iconst_4:
            result = 0;
            break; 
       case OP_iconst_5:
            result = 0;
            break; 
       case OP_idiv:
            result = 0;
            break; 
       case OP_if_acmpeq:
            result = 2;
            break; 
       case OP_if_acmpne:
            result = 2;
            break; 
       case OP_if_icmpeq:
            result = 2;
            break; 
       case OP_if_icmpge:
            result = 2;
            break; 
       case OP_if_icmpgt:
            result = 2;
            break; 
       case OP_if_icmple:
            result = 2;
            break; 
       case OP_if_icmplt:
            result = 2;
            break; 
       case OP_if_icmpne:
            result = 2;
            break; 
       case OP_ifeq:
            result = 2;
            break; 
       case OP_ifge:
            result = 2;
            break; 
       case OP_ifgt:
            result = 2;
            break; 
       case OP_ifle:
            result = 2;
            break; 
       case OP_iflt:
            result = 2;
            break; 
       case OP_ifne:
            result = 2;
            break; 
       case OP_ifnonnull:
            result = 2;
            break; 
       case OP_ifnull:
            result = 2;
            break; 
       case OP_iinc:
            result = 2;
            break; 
       case OP_iload:
            result = 1;
            break; 
       case OP_iload_0:
            result = 0;
            break; 
       case OP_iload_1:
            result = 0;
            break; 
       case OP_iload_2:
            result = 0;
            break; 
       case OP_iload_3:
            result = 0;
            break; 
       case OP_impdep1:
            result = 0;
            break; 
       case OP_impdep2:
            result = 0;
            break; 
       case OP_imul:
            result = 0;
            break; 
       case OP_ineg:
            result = 0;
            break; 
       case OP_instanceof:
            result = 2;
            break; 
       case OP_invokedynamic:
            result = 4;
            break; 
       case OP_invokeinterface:
            result = 4;
            break; 
       case OP_invokespecial:
            result = 2;
            break; 
       case OP_invokestatic:
            result = 2;
            break; 
       case OP_invokevirtual:
            result = 2;
            break; 
       case OP_ior:
            result = 0;
            break; 
       case OP_irem:
            result = 0;
            break; 
       case OP_ireturn:
            result = 0;
            break; 
       case OP_ishl:
            result = 0;
            break; 
       case OP_ishr:
            result = 0;
            break; 
       case OP_istore:
            result = 1;
            break; 
       case OP_istore_0:
            result = 0;
            break; 
       case OP_istore_1:
            result = 0;
            break; 
       case OP_istore_2:
            result = 0;
            break; 
       case OP_istore_3:
            result = 0;
            break; 
       case OP_isub:
            result = 0;
            break; 
       case OP_iushr:
            result = 0;
            break; 
       case OP_ixor:
            result = 0;
            break; 
       case OP_jsr:
            result = 2;
            break; 
       case OP_jsr_w:
            result = 4;
            break; 
       case OP_l2d:
            result = 0;
            break; 
       case OP_l2f:
            result = 0;
            break; 
       case OP_l2i:
            result = 0;
            break; 
       case OP_ladd:
            result = 0;
            break; 
       case OP_laload:
            result = 0;
            break; 
       case OP_land:
            result = 0;
            break; 
       case OP_lastore:
            result = 0;
            break; 
       case OP_lcmp:
            result = 0;
            break; 
       case OP_lconst_0:
            result = 0;
            break; 
       case OP_lconst_1:
            result = 0;
            break; 
       case OP_ldc:
            result = 1;
            break; 
       case OP_ldc_w:
            result = 2;
            break; 
       case OP_ldc2_w:
            result = 2;
            break; 
       case OP_ldiv:
            result = 0;
            break; 
       case OP_lload:
            result = 1;
            break; 
       case OP_lload_0:
            result = 0;
            break; 
       case OP_lload_1:
            result = 0;
            break; 
       case OP_lload_2:
            result = 0;
            break; 
       case OP_lload_3:
            result = 0;
            break; 
       case OP_lmul:
            result = 0;
            break; 
       case OP_lneg:
            result = 0;
            break; 
       case OP_lookupswitch:
            result = -1;
            break; 
       case OP_lor:
            result = 0;
            break; 
       case OP_lrem:
            result = 0;
            break; 
       case OP_lreturn:
            result = 0;
            break; 
       case OP_lshl:
            result = 0;
            break; 
       case OP_lshr:
            result = 0;
            break; 
       case OP_lstore:
            result = 1;
            break; 
       case OP_lstore_0:
            result = 0;
            break; 
       case OP_lstore_1:
            result = 0;
            break; 
       case OP_lstore_2:
            result = 0;
            break; 
       case OP_lstore_3:
            result = 0;
            break; 
       case OP_lsub:
            result = 0;
            break; 
       case OP_lushr:
            result = 0;
            break; 
       case OP_lxor:
            result = 0;
            break; 
       case OP_monitorenter:
            result = 0;
            break; 
       case OP_monitorexit:
            result = 0;
            break; 
       case OP_multianewarray:
            result = 3;
            break; 
       case OP_new:
            result = 2;
            break; 
       case OP_newarray:
            result = 1;
            break; 
       case OP_nop:
            result = 0;
            break; 
       case OP_pop:
            result = 0;
            break; 
       case OP_pop2:
            result = 0;
            break; 
       case OP_putfield:
            result = 2;
            break; 
       case OP_putstatic:
            result = 2;
            break; 
       case OP_ret:
            result = 1;
            break; 
       case OP_return:
            result = 0;
            break; 
       case OP_saload:
            result = 0;
            break; 
       case OP_sastore:
            result = 0;
            break; 
       case OP_sipush:
            result = 2;
            break; 
       case OP_swap:
            result = 0;
            break; 
       case OP_tableswitch:
            result = -1;
            break; 
       case OP_wide:
            result = -1;
            break;
        default:
            break;
    }
    return result;
}


#endif