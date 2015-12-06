//
//  M_INSTCOMPANDJMP.c
//  JavaVirtualMachine
//
//  Created by Gabriel Araujo Dantas on 04/12/15.
//  Copyright © 2015 Rondinele Prado. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "../../include/ExecutionEngine/I_INSTCOMPANDJMP.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"

void lcmp(Environment *environment){
    
    u8 operando1 = 0;
    u8 operando2 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    u4 resultado = -1000;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1 = (u8) operandoPilha2;
    operando1 = (u8) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2 = (u8) operandoPilha2;
    operando2 = (u8) operando1 << 32;
    
    if (operando2 > operando1) {
        resultado = 1;
    }else if (operando2 == operando1){
        resultado = 0;
    }else{
        resultado = -1;
    }
    pushInOperandStack(environment->thread, resultado);
}

void fcmpl(Environment *environment){
    
    float operando1 = 0;
    float operando2 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 resultado = -1000;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operando1 = u4ToFLoat(operandoPilha1);
    
    operandoPilha2 = popFromOperandStack(environment->thread);
    operando2 = u4ToFLoat(operandoPilha2);
    
    if(operando2 > operando1){
        resultado = 1;
    }else if (operando2 == operando1){
        resultado = 0;
    }else if (operando2 < operando1){
        resultado = -1;
    }else{
        //Caso o valor passado seja um NaN
        resultado = -1;
    }
    pushInOperandStack(environment->thread, resultado);
}

void fcmpg(Environment *environment){
    float operando1 = 0;
    float operando2 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 resultado = -1000;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operando1 = u4ToFLoat(operandoPilha1);
    
    operandoPilha2 = popFromOperandStack(environment->thread);
    operando2 = u4ToFLoat(operandoPilha2);
    
    if(operando2 > operando1){
        resultado = 1;
    }else if (operando2 == operando1){
        resultado = 0;
    }else if (operando2 < operando1){
        resultado = -1;
    }else{
        //Caso o valor passado seja um NaN
        resultado = 1;
    }
    pushInOperandStack(environment->thread, resultado);
}

void dcmpl(Environment *environment){

    double operando1 = 0;
    double operando2 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 resultado = -1000;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment ->thread);
    
    operando1 = u4ToDouble(operandoPilha1, operandoPilha2);
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2 = u4ToDouble(operandoPilha1, operandoPilha2);
    
    if(operando2 > operando1){
        resultado = 1;
    }else if (operando2 == operando1){
        resultado = 0;
    }else if (operando2 < operando1){
        resultado = -1;
    }else{
        resultado = -1;
    }
    pushInOperandStack(environment->thread, resultado);
}
void dcmpg(Environment *environment){
    double operando1 = 0;
    double operando2 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    u4 resultado = -1000;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment ->thread);
    
    operando1 = u4ToDouble(operandoPilha1, operandoPilha2);
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2 = u4ToDouble(operandoPilha1, operandoPilha2);
    
    if(operando2 > operando1){
        resultado = 1;
    }else if (operando2 == operando1){
        resultado = 0;
    }else if (operando2 < operando1){
        resultado = -1;
    }else{
        resultado = 1;
    }
    pushInOperandStack(environment->thread, resultado);

}

void ifeq(Environment *environment){
    u2 offset;
    u4 operando = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;
    
    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando = popFromOperandStack(environment->thread);
    
    if(operando == 0){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void ifne(Environment *environment){
    u2 offset;
    u4 operando = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;

    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando = popFromOperandStack(environment->thread);
    
    if(operando != 0){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void iflt(Environment *environment){
    u2 offset;
    u4 operando = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;

    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando = popFromOperandStack(environment->thread);
    
    //Como u4 eh unsigned fiz um cast para int que contem 4 bytes porem sem unsigned
    int operandoSemUnsigned = (int) operando;
    
    if(operandoSemUnsigned < 0){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void ifge(Environment *environment){
    u2 offset;
    u4 operando = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;

    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando = popFromOperandStack(environment->thread);
    
    //Como u4 eh unsigned fiz um cast para int que contem 4 bytes porem sem unsigned
    int operandoSemUnsigned = (int) operando;
    
    if(operandoSemUnsigned >= 0){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void ifgt(Environment *environment){
    u2 offset;
    u4 operando = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;

    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando = popFromOperandStack(environment->thread);
    
    //Como u4 eh unsigned fiz um cast para int que contem 4 bytes porem sem unsigned
    int operandoSemUnsigned = (int) operando;
    
    if(operandoSemUnsigned > 0){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void ifle(Environment *environment){
    u2 offset;
    u4 operando = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;

    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando = popFromOperandStack(environment->thread);
    
    //Como u4 eh unsigned fiz um cast para int que contem 4 bytes porem sem unsigned
    int operandoSemUnsigned = (int) operando;
    
    if(operandoSemUnsigned <= 0){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void if_icmpeq(Environment *environment){
    u2 offset;
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;

    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando1 = popFromOperandStack(environment->thread);
    operando2 = popFromOperandStack(environment->thread);
    
    if(operando2 == operando1){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void if_icmpne(Environment *environment){

    u2 offset;
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;
    
    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando1 = popFromOperandStack(environment->thread);
    operando2 = popFromOperandStack(environment->thread);
    
    if(operando2 != operando1){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void if_icmplt(Environment *environment){
    u2 offset;
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;
    
    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando1 = popFromOperandStack(environment->thread);
    operando2 = popFromOperandStack(environment->thread);
    
    if(operando2 < operando1){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void if_icmpge(Environment *environment){
    u2 offset;
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;
    
    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando1 = popFromOperandStack(environment->thread);
    operando2 = popFromOperandStack(environment->thread);
    
    if(operando2 >= operando1){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void if_icmpgt(Environment *environment){
    u2 offset;
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;
    
    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando1 = popFromOperandStack(environment->thread);
    operando2 = popFromOperandStack(environment->thread);
    
    if(operando2 > operando1){
        environment->thread->vmStack->top->returnPC += offset;
    }
}

void if_icmple(Environment *environment){
    u2 offset;
    u4 operando1 = 0;
    u4 operando2 = 0;
    u4 pc = 0;
    u1 byte1, byte2;
    u1 *code;
    CodeAttribute *codeAttribute;
    
    codeAttribute = getCodeFromMethodInfo(environment->methodArea->classTable->javaClass->arqClass->methods, environment->methodArea->classTable->javaClass->arqClass->constant_pool);
    
    pc = environment->thread->vmStack->top->returnPC;
    //perguntar como que chego no code com as estruturas criadas
    code = codeAttribute->code;
    
    byte1 = *(code + pc);
    environment->thread->vmStack->top->returnPC++;
    
    byte2 = *(code + (pc + 1));
    environment->thread->vmStack->top->returnPC++;
    
    offset = (u2)byte1;
    offset = offset << 8;
    offset |= byte2;
    offset -= 3;
    
    operando1 = popFromOperandStack(environment->thread);
    operando2 = popFromOperandStack(environment->thread);
    
    if(operando2 <= operando1){
        environment->thread->vmStack->top->returnPC += offset;
    }
}