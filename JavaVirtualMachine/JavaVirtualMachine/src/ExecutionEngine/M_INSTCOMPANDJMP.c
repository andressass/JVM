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
    
    long long operando1 = 0;
    long long operando2 = 0;
    
    u4 operandoPilha1 = 0;
    u4 operandoPilha2 = 0;
    
    u4 resultado = -1000;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando1 = (long long) operandoPilha2;
    operando1 = (long long) operandoPilha1 << 32;
    
    operandoPilha1 = popFromOperandStack(environment->thread);
    operandoPilha2 = popFromOperandStack(environment->thread);
    
    operando2 = (long long) operandoPilha2;
    operando2 = (long long) operando1 << 32;
    
    if (operando2 > operando1) {
        resultado = 1;
    }else if (operando2 == operando1){
        resultado = 0;
    }else{
        resultado = -1;
    }
    pushInOperandStack(environment->thread, resultado);
}