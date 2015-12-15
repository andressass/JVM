//#################################################################################################
/*! \file M_JAVAIO.c
 *
 *  \brief Modulo simulado da biblioteca java.io
 *
 *  Modulo responsavel por implementar servicos que simulam os metodos e atributos da
 *  biblioteca java.io
 */
//##################################################################################################


#define JAVAIO_SERV

#include <stdio.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "../../include/Util/I_JAVAIO.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/Estruturas/JAVASTRING.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/Util/I_TYPECONVERSION.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao do metodo de java.io.java.io.PrintStream.println
 *
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
void printStreamPrintln(const char* descriptorName, Environment* environment){
    //Strings
    if (strncmp(descriptorName, "(Ljava/lang/String;)V", 21)==0) {
        
        JavaString* string = (JavaString*) popFromOperandStack(environment->thread);
        
        //Se for JavaString
        if(string->tag == CONSTANT_StringJava){
            printf("\n%ls", string->stringAddress);
        }
        //Se for referencia de string para o pool de constantes
        else{
            cp_info* stringCP = (cp_info*) string;
            
            wchar_t* unicodeString = getUnicodeFromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool, stringCP->u.String.string_index);
            
            printf("\n%ls", unicodeString);
        }
    }
    //Decodificamos pelos tipos numericos, char e bool
    else if (strncmp(descriptorName, "(I)V", 4)==0 ||
             strncmp(descriptorName, "(S)V", 4)==0 ||
             strncmp(descriptorName, "(B)V", 4)==0)
        printf("\n%d", (int) popFromOperandStack(environment->thread));
    
    else if (strncmp(descriptorName, "(C)V", 4)==0)
        printf("\n%c", (char) popFromOperandStack(environment->thread));
    
    else if (strncmp(descriptorName, "(F)V", 4)==0)
        printf("\n%.2f",  u4ToFLoat(popFromOperandStack(environment->thread)));
    
    else if (strncmp(descriptorName, "(J)V", 4)==0){
        u8 bytesl = popFromOperandStack(environment->thread);
        u8 low_Bytes = popFromOperandStack(environment->thread);
        bytesl = bytesl << 32 | low_Bytes;
        printf("\n%lld", bytesl);
    }
    
    else if (strncmp(descriptorName, "(D)V", 4)==0){
        u4 high = popFromOperandStack(environment->thread);
        u4 low = popFromOperandStack(environment->thread);
        printf("\n%.2f", u4ToDouble(high, low));
    }
    
    else if (strncmp(descriptorName, "(Z)V", 4)==0)
        printf("\n%s", ((int) popFromOperandStack(environment->thread)) == 0 ? "false" : "true");
    
    else
        popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula os metodos de java.io.PrintStream
 *
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
void printStreamExecuteMethod(const char* className, const char* methodName, const char* descriptorName,
                         Environment* environment){
    
    //Metodos de java.io.PrintStream.prinln
    if (strncmp(methodName, "println", 7)==0) {
        printStreamPrintln(descriptorName, environment);
        popFromOperandStack(environment->thread); //PrintStream nao utilizado
    }
    else
        popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
void javaIOExecuteMethod(const char* className, const char* methodName, const char* descriptorName,
                           Environment* environment){
    
    //Metodos de java.io.PrintStream
    if (strncmp(className, "PrintStream", 11)==0) {
        printStreamExecuteMethod(&className[11],methodName,descriptorName,environment);
    }
    else
        popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
void javaIOGetStatic(const char* className, const char* fieldName,
                       const char* fieldDescriptor, Environment* environment){
    
    pushInOperandStack(environment->thread, 0);
}


//--------------------------------------------------------------------------------------------------
void javaIONewObject(const char* className, Environment* environment){
    pushInOperandStack(environment->thread, 0);
}