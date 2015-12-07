//#################################################################################################
/*! \file I_JAVALANG.c
 *
 *  \brief Modulo simulado da biblioteca java.lang
 *
 *  Modulo responsavel por implementar servicos que simulam os metodos e atributos da
 *  biblioteca java.lang
 */
//##################################################################################################


#define JAVALANG_SERV

#include <stdio.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "../../include/Util/I_JAVALANG.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/Estruturas/JAVASTRING.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/Util/I_TYPECONVERSION.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao de um metodo de java.io.System
 *
 * \param className Nome da classe do metodo
 * \param methodName Nome do metodo a ser executado.
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
void systemExecuteMethod(const char* className, const char* methodName,
                         const char* descriptorName, Environment* environment){
        popFromOperandStack(environment->thread);
}



//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao do metodo de java.lang.StringBuffer.append
 *
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
void stringBufferAppend(const char* descriptorName, Environment* environment){
    //Se a entrada for uma string
    if (strncmp(descriptorName, "(Ljava/lang/String;)Ljava/lang/StringBuffer;", 44)==0 ||
        strncmp(descriptorName, "(Ljava/lang/Object;)Ljava/lang/StringBuffer;", 44)==0) {
        
        JavaString* string = (JavaString*) popFromOperandStack(environment->thread);
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
        //Se for JavaString
        if(string->tag == CONSTANT_StringJava){
            //Realocacao do buffer
            stringBuffer = (wchar_t*) realloc(stringBuffer,
                                              (wcslen(stringBuffer)+string->size+1)*sizeof(wchar_t));
            //Concatenamos
            wcsncat(stringBuffer, string->stringAddress, string->size);
        }
        //Se for referencia de string para o pool de constantes
        else{
            cp_info* stringCP = (cp_info*) string;
            
            wchar_t* unicodeString = getUnicodeFromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool, stringCP->u.String.string_index);
            
            int stringBuferLenght = wcslen(stringBuffer);
            //Realocacao do buffer
            stringBuffer = (wchar_t*) realloc(stringBuffer,
                                              (stringBuferLenght+wcslen(unicodeString)+1)*sizeof(wchar_t));
            //Concatenamos
            wcscat(stringBuffer, unicodeString);
        }
        //Empilhamos o string buffer
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
    
    //Para cada tipo numerico, bool ou char
    else if(strncmp(descriptorName, "(I)Ljava/lang/StringBuffer;", 44)==0 ||
            strncmp(descriptorName, "(S)Ljava/lang/StringBuffer;", 44)==0 ||
            strncmp(descriptorName, "(B)Ljava/lang/StringBuffer;", 44)==0){
        int valor = (int) popFromOperandStack(environment->thread);
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
//        int stringBufferLen = wcslen(stringBuffer);
        
        stringBuffer = (wchar_t*) realloc(stringBuffer,
                                          (wcslen(stringBuffer)+15)*sizeof(wchar_t));
        
        //Procedimento para substiuicao de swprintf
        char buffer[15] = "";
        sprintf(buffer, "%d", valor);
        wchar_t* wbuffer = (wchar_t*) malloc((sizeof(buffer)+1)*sizeof(wchar_t));
        mbstowcs(wbuffer, buffer, (strlen(buffer))+1);
        wcscat(stringBuffer, wbuffer);
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
    
    else if(strncmp(descriptorName, "(C)Ljava/lang/StringBuffer;", 44)==0){
        char valor = (char) popFromOperandStack(environment->thread);
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
        stringBuffer = (wchar_t*) realloc(stringBuffer,
                                          (wcslen(stringBuffer)+2)*sizeof(wchar_t));
        
        //Procedimento para substiuicao de swprintf
        char buffer[3] = "";
        sprintf(buffer, "%c", valor);
        wchar_t* wbuffer = (wchar_t*) malloc((sizeof(buffer)+1)*sizeof(wchar_t));
        mbstowcs(wbuffer, buffer, (strlen(buffer))+1);
        wcscat(stringBuffer, wbuffer);
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
    
    else if(strncmp(descriptorName, "(Z)Ljava/lang/StringBuffer;", 44)==0){
        int valor = (char) popFromOperandStack(environment->thread);
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
        stringBuffer = (wchar_t*) realloc(stringBuffer,
                                          (wcslen(stringBuffer)+6)*sizeof(wchar_t));
        
        //Procedimento para substiuicao de swprintf
        char buffer[6] = "";
        sprintf(buffer, "%s", valor == 0 ? "false" : "true");
        wchar_t* wbuffer = (wchar_t*) malloc((sizeof(buffer)+1)*sizeof(wchar_t));
        mbstowcs(wbuffer, buffer, (strlen(buffer))+1);
        wcscat(stringBuffer, wbuffer);
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }

    else if(strncmp(descriptorName, "(F)Ljava/lang/StringBuffer;", 44)==0){
        float valor = u4ToFLoat(popFromOperandStack(environment->thread));
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
        stringBuffer = (wchar_t*) realloc(stringBuffer,
                                          (wcslen(stringBuffer)+20)*sizeof(wchar_t));
        
        //Procedimento para substiuicao de swprintf
        char buffer[30] = "";
        sprintf(buffer, "%.2f", valor);
        wchar_t* wbuffer = (wchar_t*) malloc((sizeof(buffer)+1)*sizeof(wchar_t));
        mbstowcs(wbuffer, buffer, (strlen(buffer))+1);
        wcscat(stringBuffer, wbuffer);
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
    
    else if(strncmp(descriptorName, "(J)Ljava/lang/StringBuffer;", 44)==0){
        u8 valor = popFromOperandStack(environment->thread);
        u8 low_Bytes = popFromOperandStack(environment->thread);
        valor = valor << 32 | low_Bytes;
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
        stringBuffer = (wchar_t*) realloc(stringBuffer,
                                          (wcslen(stringBuffer)+30)*sizeof(wchar_t));
        
        //Procedimento para substiuicao de swprintf
        char buffer[30] = "";
        sprintf(buffer, "%lld", valor);
        wchar_t* wbuffer = (wchar_t*) malloc((sizeof(buffer)+1)*sizeof(wchar_t));
        mbstowcs(wbuffer, buffer, (strlen(buffer))+1);
        wcscat(stringBuffer, wbuffer);
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
    
    else if(strncmp(descriptorName, "(D)Ljava/lang/StringBuffer;", 44)==0){
        u4 high = popFromOperandStack(environment->thread);
        u4 low = popFromOperandStack(environment->thread);
        double valor = u4ToDouble(high, low);
        
        wchar_t* stringBuffer = (wchar_t*) popFromOperandStack(environment->thread);
        
        
        stringBuffer = (wchar_t*) realloc(stringBuffer,
                                          (wcslen(stringBuffer)+15)*sizeof(wchar_t));
        
        //Procedimento para substiuicao de swprintf
        char buffer[30] = "";
        sprintf(buffer, "%.2f", valor);
        wchar_t* wbuffer = (wchar_t*) malloc((sizeof(buffer)+1)*sizeof(wchar_t));
        mbstowcs(wbuffer, buffer, (strlen(buffer))+1);
        wcscat(stringBuffer, wbuffer);
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
}

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que decodifica e simula a execucao de um metodo de java.lang.StringBuffer
 *
 * \param className Nome da classe do metodo
 * \param methodName Nome do metodo a ser executado.
 * \param descriptor Descritor do metodo a ser executado.
 * \param environment Ambiente de execucao atual.
 */
void stringBufferExecuteMethod(const char* className, const char* methodName,
                         const char* descriptorName, Environment* environment){

    if (strncmp(methodName, "<init>", 6)==0) {
        popFromOperandStack(environment->thread);
    }

    else if (strncmp(methodName, "toString", 6)==0){
        wchar_t* stringBuffer = (wchar_t*)(popFromOperandStack(environment->thread));
        JavaString* string = newJavaString(stringBuffer);
        pushInOperandStack(environment->thread, (u4) string);
    }

    else if (strncmp(methodName, "append", 6)==0) {
        stringBufferAppend(descriptorName,environment);
    }
    
    else
        popFromOperandStack(environment->thread);

}


//--------------------------------------------------------------------------------------------------
void javaLangExecuteMethod(const char* className, const char* methodName, const char* descriptorName,
                          Environment* environment){
    
    //Metodos de java/lang/System
    if (strncmp(className, "System", 6)==0) {
        systemExecuteMethod(&className[6], methodName, descriptorName, environment);
    }
    //Metodos de java/lang/StringBuffer
    else if (strncmp(className, "StringBuffer", 12)==0) {
        stringBufferExecuteMethod(&className[12], methodName, descriptorName, environment);
    }
    //Metodos de java/lang/Object
    else if ((strncmp(className, "Object", 6)==0)){
        if(strncmp(methodName, "getClass", 8)==0)
            return;
        else
            popFromOperandStack(environment->thread);
    }
    else
        popFromOperandStack(environment->thread);
}


//--------------------------------------------------------------------------------------------------
void javaLangGetStatic(const char* className, const char* fieldName,
                      const char* fieldDescriptor, Environment* environment){
    
    //Metodos de java/lang/System
    if (strncmp(className, "System", 6)==0) {
        pushInOperandStack(environment->thread, 0);
    }
    //Metodos de java/lang/StringBuffer
    else if (strncmp(className, "StringBuffer", 12)==0) {
        pushInOperandStack(environment->thread, 0);
    }
    else
        pushInOperandStack(environment->thread, 0);
}


//--------------------------------------------------------------------------------------------------
void javaLangNewObject(const char* className, Environment* environment){
    //Metodos de java/lang/System
    if (strncmp(className, "System", 6)==0) {
        pushInOperandStack(environment->thread, 0);
    }
    //Metodos de java/lang/StringBuffer
    else if (strncmp(className, "StringBuffer", 12)==0) {
        wchar_t* stringBuffer = (wchar_t*)malloc(sizeof(wchar_t));
        wcscpy(stringBuffer, L"");
        pushInOperandStack(environment->thread, (u4) stringBuffer);
    }
    else
        pushInOperandStack(environment->thread, 0);
}