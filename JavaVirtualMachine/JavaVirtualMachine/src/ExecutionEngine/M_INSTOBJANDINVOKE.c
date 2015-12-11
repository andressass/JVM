//#################################################################################################
/*! \file M_INSTOBJANDINVOKE.c
 *
 *  \brief Interface de instrucoes de Manipulacao de Objetos e Invokes da JVM.
 *
 *  Interface responsavel por implenetar os servicos relacionados a instrucoes de manupulacao
 * de objetos e chamadas de metodos.
 */
//##################################################################################################


#define INSTOBJANDINVOKE_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/ExecutionEngine/I_INSTOBJANDINVOKE.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/ExecutionEngine/I_EXCEPTION.h"
#include "../../include/Util/I_JAVADECODER.h"
#include "../../include/Estruturas/JAVAARRAY.h"
#include "../../include/Estruturas/E_JVM.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que calcula un indice para o pool de constantes baseado em dois bytes obtidos do codigo,
 * atualizando o valor de PC.
 *
 * \param method Referencia para o metodo contendo o codigo
 * \param method Referencia para o pool de constantes do metodo
 * \param method Referencia para o PC da thread atual
 * \return Indice calculado como byte1 << 8 | byte2
 */
u2 calculatePoolIndexFromCode(method_info* method, cp_info* constant_pool, Thread* thread){
    // Obtemos o primeiro byte argumento para o indice no pool de cte
    thread->PC++;
    u2 index = getByteCodeFromMethod(method, constant_pool, thread->PC);
    // Obtemos o segundo byte argumento
    thread->PC++;
    index = index << 8 | getByteCodeFromMethod(method,
                                              constant_pool,
                                               thread->PC);
    return index;
}


//--------------------------------------------------------------------------------------------------
void getstatic(Environment* environment){
    
    char* attribute_name;
    char* class_name;
    char* attribute_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
   
    //Calculamos o indice do fieldRef no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //Obtemos os nomes da classe, o nome e descritor do field
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                           actual_class->arqClass->constant_pool,
                                           &class_name, &attribute_name, &attribute_descriptor);
    
    //VERIFICACAO DE CAMPO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)) {
        javaLibGetStatic(class_name, attribute_name, attribute_descriptor, environment);
        return;
    }
    
    //TODO: Verifica se campo eh estatico
    
    //Verificamos se eh de 32 ou 64 bits
    if (strcmp(attribute_descriptor, "J") == 0 || strcmp(attribute_descriptor, "D") == 0) {
        u8* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
        u8 value = *value_reference;
        
        u4 high_bytes = value >> 32;
        u8 low_bytes = value & 0xFFFFFFFF;
        pushInOperandStack(environment->thread, (u4) low_bytes);
        pushInOperandStack(environment->thread, (u4) high_bytes);
    }
    else{
        //Se eh de 8bits
        if (strcmp(attribute_descriptor, "B") == 0 || strcmp(attribute_descriptor, "C") == 0 ||
            strcmp(attribute_descriptor, "Z") == 0){
            
            u1* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            u1 value = *value_reference;
            pushInOperandStack(environment->thread, (u4) value);
        }
        
        //Se eh de 16bits
        else if (strcmp(attribute_descriptor, "S") == 0){
            u2* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            u2 value = *value_reference;
            pushInOperandStack(environment->thread, (u4) value);
        }
        //Se eh de 32bits
        else {
            u4* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            u4 value = *value_reference;
            pushInOperandStack(environment->thread, value);
        }
    }
}


//--------------------------------------------------------------------------------------------------
void putstatic(Environment* environment){
    
    char* attribute_name;
    char* class_name;
    char* attribute_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice do fieldRef no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //Obtemos os nomes da classe, o nome e descritor do field
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                           actual_class->arqClass->constant_pool,
                                           &class_name, &attribute_name, &attribute_descriptor);
    
    
    //VERIFICACAO DE CAMPO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)) return;
    
    //TODO: Verifica se campo eh estatico
    
    //Verificamos se eh de 64 bits
    if (strcmp(attribute_descriptor, "J") == 0 || strcmp(attribute_descriptor, "D") == 0) {
        u8* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
        if (value_reference == NULL) JVMThrow(NullPointerException, environment);
        u8 value;
        
        //Obtemos e concatenamos os bytes
        value = popFromOperandStack(environment->thread);
        u8 lowBytes = popFromOperandStack(environment->thread);
        value = value << 32 | lowBytes;
        
        //Atualizamos o campo
        *value_reference = value;
    }

    else{
        
        //Obtemos o valor
        u4 value = popFromOperandStack(environment->thread);
        
        
        //Se eh de 8bits
        if (strcmp(attribute_descriptor, "B") == 0 || strcmp(attribute_descriptor, "C") == 0 ||
                 strcmp(attribute_descriptor, "Z") == 0){
            
            u1* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            if (value_reference == NULL) JVMThrow(NullPointerException, environment);
            *value_reference = (u1) value;
        }

        //Se eh de 16bits
        else if (strcmp(attribute_descriptor, "S") == 0){
            u2* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            if (value_reference == NULL) JVMThrow(NullPointerException, environment);
            *value_reference = (u2) value;
        }
        //Se eh de 32bits
        else {
         u4* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            if (value_reference == NULL) JVMThrow(NullPointerException, environment);
            *value_reference = value;
        }
    }

}



//--------------------------------------------------------------------------------------------------
void getfield(Environment* environment){
    
    char* attribute_name;
    char* class_name;
    char* attribute_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Obtemos a referencia para o objeto
    Object* objectRef = (Object*) popFromOperandStack(environment->thread);
    
    //Calculamos o indice do fieldRef no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //Obtemos os nomes da classe, o nome e descritor do field
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                           actual_class->arqClass->constant_pool,
                                           &class_name, &attribute_name, &attribute_descriptor);
    
    //VERIFICACAO DE CAMPO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)) return;
    
    //Verificamos se eh de 32 ou 64 bits
    if (strcmp(attribute_descriptor, "J") == 0 || strcmp(attribute_descriptor, "D") == 0) {
        u8* value_reference = getObjectAttributeReference(objectRef, attribute_name);
        u8 value = *value_reference;
        
        u4 high_bytes = value >> 32;
        u4 low_bytes = value & 0xFFFFFFFF;
        pushInOperandStack(environment->thread, (u4)low_bytes);
        pushInOperandStack(environment->thread, (u4)high_bytes);
    }
    else{
        //Se eh de 8bits
        if (strcmp(attribute_descriptor, "B") == 0 || strcmp(attribute_descriptor, "C") == 0 ||
            strcmp(attribute_descriptor, "Z") == 0){
            
            u1* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            u1 value = *value_reference;
            pushInOperandStack(environment->thread, (u4) value);
        }
        
        //Se eh de 16bits
        else if (strcmp(attribute_descriptor, "S") == 0){
            u2* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            u2 value = *value_reference;
            pushInOperandStack(environment->thread, (u4) value);
        }
        //Se eh de 32bits
        else {
            u4* value_reference = getObjectAttributeReference(objectRef, attribute_name);   
            u4 value = *value_reference;
            pushInOperandStack(environment->thread, value);
        }
    }
}


//--------------------------------------------------------------------------------------------------
void putfield(Environment* environment){
    
    char* attribute_name;
    char* class_name;
    char* attribute_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice do fieldRef no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //Obtemos os nomes da classe, o nome e descritor do field
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                           actual_class->arqClass->constant_pool,
                                           &class_name, &attribute_name, &attribute_descriptor);
    
    
    //VERIFICACAO DE CAMPO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)) return;
    
    //TODO: Verifica se campo eh estatico
    
    //Verificamos se eh de 32 ou 64 bits
    if (strcmp(attribute_descriptor, "J") == 0 || strcmp(attribute_descriptor, "D") == 0) {
        //Obtemos e concatenamos os bytes
        u8 value;
        value = popFromOperandStack(environment->thread);
        value = value << 32 | popFromOperandStack(environment->thread);
        //Obtemos a referencia para o objeto
        Object* objectRef = (Object*) popFromOperandStack(environment->thread);
        
        u8* value_reference = getObjectAttributeReference(objectRef, attribute_name);
        if (value_reference == NULL) JVMThrow(NullPointerException, environment);
        //Atualizamos o campo
        *value_reference = value;
    }
    else{
        //Obtemos o valor
        u4 value = popFromOperandStack(environment->thread);
        Object* objectRef = (Object*) popFromOperandStack(environment->thread);
        
        //Se eh de 8bits
        if (strcmp(attribute_descriptor, "B") == 0 || strcmp(attribute_descriptor, "C") == 0 ||
            strcmp(attribute_descriptor, "Z") == 0){
            
            u1* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            if (value_reference == NULL) JVMThrow(NullPointerException, environment);
            *value_reference = (u1) value;
        }
        
        //Se eh de 16bits
        else if (strcmp(attribute_descriptor, "S") == 0){
            u2* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            if (value_reference == NULL) JVMThrow(NullPointerException, environment);
            *value_reference = (u2) value;
        }
        //Se eh de 32bits
        else {
            u4* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            if (value_reference == NULL) JVMThrow(NullPointerException, environment);
            *value_reference = value;
        }
    }
}

//--------------------------------------------------------------------------------------------------
/*! Metodo que retorna a quanitdade de parametros (de U4s) sao passados como parametro de um 
 *  desctritor de metodo.
 * 
 * \param descriptor Descritor do metodo
 *
 */
int getParameterNumberFromMethodDescriptor(char* descriptor){
    
    int nParams = 0;
    
    if (descriptor[0] != '(') return -1;
    
    //Pulamos o '(' e procuramos o numero de parametros
    for (int i = 1; i < strlen(descriptor); i++) {
        //Fim de parametros
        if (descriptor[i] == ')') break;
        
        //Se for L<Name>;
        if (descriptor[i] == 'L') {
            while (descriptor[i]!=';'){
                i++; //Procuramos o ';'
                if (i > strlen(descriptor)) return -1;
            }
            nParams++;
        }
        //Se for long ou double
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') nParams += 2;
        //Se forem de 32bits
        else nParams ++;
    }
    return nParams;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que verifica se uma classe eh subclasse de outra
 *
 * \param className Nome da classe a ser verificada
 * \param supClassName Nome da possivel superclasse
 * \param environment Ambiente de execucao
 * \return 1 se sim, 0 se nao
 */
int isClassSubClassFromClass(char* className, char* supClassName, Environment* environment){
    
    if(strcmp(className, supClassName) == 0) return 1;
    
    JavaClass* class = getClass(className, environment);
    char* superName = getClassNameFromConstantPool(class->arqClass->constant_pool, class->arqClass->super_class);
    
    if (javaLibIsFrom(superName)) return 0;
    else isClassSubClassFromClass(superName, supClassName, environment);
    
    return 0;
}

//--------------------------------------------------------------------------------------------------
/*!
 *  Metodo que verifica se existe o metodo existe na classe ou superclasse de uma classe passada e
 * retorna uma referencia para o method_info e o nome da classe do metodo eh copiada para o 
 * parametro method_class_name
 *
 * \param objectClass Referencia para a classe do objeto
 * \param method_name nome do metodo atual
 * \param method_descriptor descritor do metodo atual
 * \param environment Ambiente de execucao
 * \param method_class_name Nome da classe do metodo encontrado
 * \return method_info do metodo, se nao lanca excessao
 */
method_info* isMethodInClassOrSuperClass(JavaClass* objectClass, char* method_name, char* method_descriptor, Environment* environment, char** method_class_name){
    
    method_info* method = getMethodInfoFromClass(objectClass, method_name, method_descriptor);
    if (method){
        *method_class_name = getClassNameFromConstantPool(objectClass->arqClass->constant_pool,
                                     objectClass->arqClass->this_class);
        return method;
    }
    
    char* superClassName = getClassNameFromConstantPool(objectClass->arqClass->constant_pool,
                                                        objectClass->arqClass->super_class);
    
    if (javaLibIsFrom(superClassName)) {
        JVMThrow(AbstractMethodError, environment);
        return NULL;
    }
    //Verificamos recursivamente
    else return isMethodInClassOrSuperClass(getClass(superClassName, environment), method_name, method_descriptor, environment, method_class_name);
}


//--------------------------------------------------------------------------------------------------
void invokevirtual(Environment* environment){
    
    char* method_name;
    char* class_name;
    char* method_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice do method_info no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //2. Resolvemos o nome do metodo, obtendo a referencia do method_info
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                                   actual_class->arqClass->constant_pool,
                                                   &class_name, &method_name, &method_descriptor);
    
    //VERIFICACAO DE METODO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)){
        javaLibExecuteMethod(class_name, method_name, method_descriptor, environment);
        return;
    }
    
    //4. Baseado no descritor do metodo, desempilhamos os parametros
    //Obtemos a quantidade de parametros a serem desempilhados
    int nParams = getParameterNumberFromMethodDescriptor(method_descriptor);
    //Criamos um vetor de u4 para os parametros
    u4* params = (u4*) malloc(nParams*sizeof(u4));
    //Desempilhamos os parametros e salvamos no vetor
    for (int i = 0; i < nParams; i++) params[i] = popFromOperandStack(environment->thread);
    
    //5. Desempilhamos uma referencia para o objeto (Objectref)
    Object* objectRef = (Object*) popFromOperandStack(environment->thread);
    if (objectRef == NULL) JVMThrow(NullPointerException, environment);
    

    //6. Buscamos o metodo recursivamente na classe e superclasses do objeto
    method_info* method = isMethodInClassOrSuperClass(objectRef->handler->javaClass, method_name, method_descriptor, environment, &class_name);
    
    if ((method->access_flags & ACC_ABSTRACT)) JVMThrow(AbstractMethodError, environment);
    
    //7. Criamos um novo frame e empilhamos
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    environment->thread->PC--; //Pc é colocado para -1 devido ao incremento do interpretador
    
    //7.1. Passamos os argumentos para o vetor de variaveis locais
    newFrame->localVariablesVector[0] = (u4) objectRef;
    for (int i = 0; i < nParams; i++) newFrame->localVariablesVector[i+1] = params[i];
}


//--------------------------------------------------------------------------------------------------
/*!
 * O metodo eh selecionado para invocacao a nao ser que todas as seguintes condicoes sejam
 *    verdadeiras:
 *
 *      7.1. A flag ACC_SUPER esta setada para a classe atual
 *      7.2. A classe do metodo eh superclasse da classe atual
 *      7.3. O metodo nao eh um metodo <init>
 *
 * \param object Referencia para o objeto
 * \param method_class Referencia para a classe do metodo invocado
 * \param method_name nome do metodo atual
 * \param method_descriptor descritor do metodo atual
 * \param environment Ambiente de execucao
 */
void verifyInvokeSpecial(Object* objectRef, JavaClass* method_class, char* method_name,
                         char*method_descriptor, Environment* environment){
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    char* actual_class_name = getClassNameFromConstantPool(actual_class->arqClass->constant_pool,
                                                           actual_class->arqClass->this_class);
    char* method_class_name = getClassNameFromConstantPool(method_class->arqClass->constant_pool,
                                                           method_class->arqClass->this_class);
    
    int isSuper = actual_class->arqClass->access_flags & ACC_SUPER;
    
    int isSub = isClassSubClassFromClass(actual_class_name, method_class_name, environment);
    
    int isInit = strcmp(method_name, "<init>") == 0;
    
    if (!(isSuper && isSub && isInit)) return;
}


//--------------------------------------------------------------------------------------------------
void invokespecial(Environment* environment){
    
    char* method_name;
    char* class_name;
    char* method_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice do method_info no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //2. Resolvemos o nome do metodo, obtendo a referencia do method_info
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                                   actual_class->arqClass->constant_pool,
                                                   &class_name, &method_name, &method_descriptor);
    
    //VERIFICACAO DE METODO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)){
        javaLibExecuteMethod(class_name, method_name, method_descriptor, environment);
        return;
    }
    
    //1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass
    JavaClass* method_class = getClass(class_name, environment);
    
    
    //4. Baseado no descritor do metodo, desempilhamos os parametros
    
    //Obtemos a quantidade de parametros a serem desempilhados
    int nParams = getParameterNumberFromMethodDescriptor(method_descriptor);
    
    //Criamos um vetor de u4 para os parametros
    u4* params = (u4*) malloc(nParams*sizeof(u4));
    
    //Desempilhamos os parametros e salvamos no vetor
    for (int i = 0; i < nParams; i++) params[i] = popFromOperandStack(environment->thread);
    
    
    //5. Desempilhamos uma referencia para o objeto (Objectref)
    Object* objectRef = (Object*) popFromOperandStack(environment->thread);
    if (objectRef == NULL) JVMThrow(NullPointerException, environment);
    
    
    //6. Verificacoes de invokespecial
    verifyInvokeSpecial(objectRef, method_class, method_name, method_descriptor, environment);
    
    
    //Buscamos o metodo recursivamente na classe e superclasses do objeto
    method_info* method = isMethodInClassOrSuperClass(objectRef->handler->javaClass, method_name, method_descriptor, environment, &class_name);
    
    
    if ((method->access_flags & ACC_STATIC)) JVMThrow(IncompatibleClassChangeError, environment);
    if ((method->access_flags & ACC_ABSTRACT)) JVMThrow(AbstractMethodError, environment);
    
    
    //7. Criamos um novo frame e empilhamos
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    environment->thread->PC--; //Pc é colocado para -1 devido ao incremento do interpretador
    
    //7.1. Passamos os argumentos para o vetor de variaveis locais
    newFrame->localVariablesVector[0] = (u4) objectRef;
    for (int i = 0; i < nParams; i++) newFrame->localVariablesVector[i+1] = params[i];
}


//--------------------------------------------------------------------------------------------------
void invokestatic(Environment* environment){
    
    char* method_name;
    char* class_name;
    char* method_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice do method_info no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //2. Resolvemos o nome do metodo, obtendo a referencia do method_info
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                                   actual_class->arqClass->constant_pool,
                                                   &class_name, &method_name, &method_descriptor);
    
    //VERIFICACAO DE METODO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)){
        javaLibExecuteMethod(class_name, method_name, method_descriptor, environment);
        return;
    }
    
    //1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass
    JavaClass* method_class = getClass(class_name, environment);
    
    
    //4. Baseado no descritor do metodo, desempilhamos os parametros
    //Obtemos a quantidade de parametros a serem desempilhados
    int nParams = getParameterNumberFromMethodDescriptor(method_descriptor);
    //Criamos um vetor de u4 para os parametros
    u4* params = (u4*) malloc(nParams*sizeof(u4));
    //Desempilhamos os parametros e salvamos no vetor
    for (int i = 0; i < nParams; i++) params[i] = popFromOperandStack(environment->thread);
    
    
    //Verificamos se o metodo eh estatico
    method_info* method = getMethodInfoFromClass(method_class, method_name, method_descriptor);
    if ((method->access_flags & ACC_STATIC) == 0) JVMThrow(IncompatibleClassChangeError, environment);
    
    
    //7. Criamos um novo frame e empilhamos
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    environment->thread->PC--; //Pc é colocado para -1 devido ao incremento do interpretador
    
    //7.1. Passamos os argumentos para o vetor de variaveis locais
    for (int i = 0; i < nParams; i++) newFrame->localVariablesVector[i] = params[i];
}


//--------------------------------------------------------------------------------------------------
void invokeinterface(Environment* environment){

    char* method_name;
    char* class_name;
    char* method_descriptor;
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice do method_info no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //2. Resolvemos o nome do metodo, obtendo a referencia do method_info
    getFieldOrMethodInfoAttributesFromConstantPool(index,
                                                   actual_class->arqClass->constant_pool,
                                                   &class_name, &method_name, &method_descriptor);
    
    //VERIFICACAO DE METODO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(class_name)){
        javaLibExecuteMethod(class_name, method_name, method_descriptor, environment);
        return;
    }
    
    
    //4. Baseado no descritor do metodo, desempilhamos os parametros
    //Obtemos a quantidade de parametros a serem desempilhados
    int nParams = getParameterNumberFromMethodDescriptor(method_descriptor);
    //Criamos um vetor de u4 para os parametros
    u4* params = (u4*) malloc(nParams*sizeof(u4));
    //Desempilhamos os parametros e salvamos no vetor
    for (int i = 0; i < nParams; i++) params[i] = popFromOperandStack(environment->thread);
    
    
    //5. Desempilhamos uma referencia para o objeto (Objectref)
    Object* objectRef = (Object*) popFromOperandStack(environment->thread);
    
    environment->thread->PC++; //COUNT
    environment->thread->PC++; //Byte 0
    
    if (objectRef == NULL) JVMThrow(NullPointerException, environment);
    //TODO: Se a classe de Objectref nao implementa a interface, IncompatibleClassChangeError
    
    
    //6. Verificacoes de invokeinterface
    
    // 6.2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
    //   na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
    //   6.3. Se nao, AbstractMethodError.
    method_info* method = isMethodInClassOrSuperClass(objectRef->handler->javaClass, method_name, method_descriptor, environment, &class_name);
    
    if ((method->access_flags & ACC_ABSTRACT)) JVMThrow(AbstractMethodError, environment);
    if (!(method->access_flags & ACC_PUBLIC)) JVMThrow(IllegalAccessError, environment);
    
    
    //7. Criamos um novo frame e empilhamos
    //VERIFICAR METODO EM SUPERCLASSES DE FORMA RECURSIVA
    class_name = getClassNameFromConstantPool(objectRef->handler->javaClass->arqClass->constant_pool, objectRef->handler->javaClass->arqClass->this_class);
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    environment->thread->PC--; //Pc é colocado para -1 devido ao incremento do interpretador
    
    //7.1. Passamos os argumentos para o vetor de variaveis locais
    newFrame->localVariablesVector[0] = (u4) objectRef;
    for (int i = 0; i < nParams; i++) newFrame->localVariablesVector[i+1] = params[i];
}


//--------------------------------------------------------------------------------------------------
void New(Environment* environment){
    
    JavaClass* actual_class = environment->thread->vmStack->top->javaClass;
    method_info* actual_method = environment->thread->vmStack->top->method_info;
    
    //Calculamos o indice para a classe no pool
    u2 index = calculatePoolIndexFromCode(actual_method,
                                          actual_class->arqClass->constant_pool,
                                          environment->thread);
    
    //Obtemos o nome da classe
    char* className = getClassNameFromConstantPool(actual_class->arqClass->constant_pool, index);
    
    //VERIFICACAO DE METODO DE BIBLIOTECA JAVA
    if (javaLibIsFrom(className)){
        javaLibNewObject(className, environment);
        return;
    }
    
    //Criamos uma nova instancia de classe
    Object* instance = newObjectFromClass(className, environment);

    //Empilhamos na pilha de operandos
    pushInOperandStack(environment->thread, (u4) instance);
}


//--------------------------------------------------------------------------------------------------
void newarray(Environment* environment){
    
    void* array;
    int i;
    
    environment->thread->PC++;
    u1 atype_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    int count = (u4)popFromOperandStack(environment->thread);
    
    if (count < 0) JVMThrow(NegativeArraySizeException, environment);
    
    if (atype_argument == T_BYTE || atype_argument == T_BOOLEAN) {
        array = (u1*) malloc(sizeof(u1) * count);
        for(i = 0; i < count; i++){
            u1* b = (u1*) array+i;
            *b = 0;
        }
    }
    else if (atype_argument == T_CHAR) {
        array = (u1*) malloc(sizeof(u1) * count);
        for(i = 0; i < count; i++){
            u1* b = (u1*) array+i;
            *b = '\0';
        }
    }
    else if (atype_argument == T_SHORT) {
        array = (u2*) malloc(sizeof(u2) * count);
        for(i = 0; i < count; i++){
            u2* s = (u2*) array+i;
            *s = 0;
        }
    }
    else if (atype_argument == T_INT) {
        array = (u4*) malloc(sizeof(u4) * count);
        for(i = 0; i < count; i++){
            u4* i_f = (u4*) array+i;
            *i_f = 0;
        }
    }
    else if (atype_argument == T_FLOAT) {
        array = (u4*) malloc(sizeof(u4) * count);
        for(i = 0; i < count; i++){
            u4* i_f = (u4*) array+i;
            *i_f = 0;
        }
    }
    else if (atype_argument == T_LONG) {
        array = (u8*) malloc(sizeof(u8) * count);
        for(i = 0; i < count; i++){
            u8* l_d  = (u8*) array+i;
            *l_d = 0;
        }
    }
    else if (atype_argument == T_DOUBLE) {
        array = (u8*) malloc(sizeof(u8) * count);
        for(i = 0; i < count; i++){
            double* l_d  = (double*) array+i;
            *l_d = 0.0;
        }
    }
    
    JavaArray* arrayref = newJavaArray(atype_argument, count, array);
    
    pushInOperandStack(environment->thread, (u4) arrayref);

}


//--------------------------------------------------------------------------------------------------
void anewarray(Environment* environment){
    
    int i;
    
    u2 index_result = calculatePoolIndexFromCode(environment->thread->vmStack->top->method_info, environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread);
    
    u4 atype = (u4) getClassNameFromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool, index_result);
    
    int count = (u4)popFromOperandStack(environment->thread);
    
    if (count < 0) JVMThrow(NegativeArraySizeException, environment);
    
    u4* array = (u4*) malloc(sizeof(u4) * count);
    
    for(i = 0; i < count; i++){
        array[i] = (u4) NULL;
    }
    
    JavaArray* arrayref = newJavaArray(atype, count, array);
    
    pushInOperandStack(environment->thread, (u4) arrayref);
}


//--------------------------------------------------------------------------------------------------
void arraylength(Environment* environment){
    
    JavaArray* arrayref = (JavaArray*)popFromOperandStack(environment->thread);
    
    if (arrayref->arrayAddress == NULL) JVMThrow(NullPointerException, environment);
    
    pushInOperandStack(environment->thread, arrayref->count);
}


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que inicializa um array multidimensional.
 *
 * \param total_dimensions Total de dimensoes do array a ser inicializado.
 * \param current_dimension A dimensao atual do array a ser inicializado.
 * \param count O vetor count que possui o quantidade de componentes em cada dimensao do array a ser inicializado.
 * \param posicao A posicao do array em que sera inicializada com o valor inicial padrao do tipo dos componentes.
 * \param type_array O tipo dos componentes do array a ser inicializado.
 * \param array O array a ser inicializado.
 */
void initializeNDArray(int total_dimensions, int current_dimension, int* count ,int posicao,
                     char type_array, void* array){
    int i;
    current_dimension++;
    // Enquanto ainda nao chegar na ultima dimensao, continua na recusividade
    for (i = 0; i < count[current_dimension]; i++) {
        posicao += i*count[current_dimension+1];
        if (current_dimension != total_dimensions-1) {
            initializeNDArray(total_dimensions, current_dimension, count, posicao, type_array, array);
        }
        else {
            if (type_array == 'B' || type_array == 'Z') {
                u1* b = (u1*) array+posicao+i;
                *b = 0;
            }
            else if (type_array == 'C') {
                u1* b = (u1*) array+posicao+i;
                *b = '\0';
            }
            else if (type_array == 'S') {
                u2* s = (u2*) array+posicao+i;
                *s = 0;
            }
            else if (type_array == 'I') {
                u4* i_f = (u4*) array+posicao+i;
                *i_f = 0;
            }
            else if (type_array == 'F') {
                u4* i_f = (u4*) array+posicao+i;
                *i_f = 0.0f;
            }
            else if (type_array == 'J') {
                u8* l_d  = (u8*) array+posicao+i;
                *l_d = 0L;
            }
            else if (type_array == 'D') {
                u8* l_d  = (u8*) array+posicao+i;
                *l_d = 0.0;
            }
            return;
        }
    }
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
void multianewarray(Environment* environment){
    
    u2 index_result = calculatePoolIndexFromCode(environment->thread->vmStack->top->method_info, environment->thread->vmStack->top->javaClass->arqClass->constant_pool, environment->thread);
    
    u4 atype = (u4) getClassNameFromConstantPool(environment->thread->vmStack->top->javaClass->arqClass->constant_pool, index_result);
    
    
    
    //TODO: RESOLVER A REFERENCIA SIMBOLICA DOS TIPO CLASS, ARRAY E INTERFACE
    
    //TODO: During resolution of the symbolic reference to the class, array, or interface type, any of the exceptions documented in Section 5.4.3.1 can be thrown.
    
    //TODO: Otherwise, if the current class does not have permission to access the element type of the resolved array class, multianewarray throws an IllegalAccessError.
    
    //TODO: Otherwise, if any of the dimensions values on the operand stack are less than zero, the multianewarray instruction throws a NegativeArraySizeException.
    
    environment->thread->PC++;
    u1 dimensions_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    //Vetor que armazena o tamanho de cada dimensao do array
    int *count = (int*) malloc(sizeof(int) * dimensions_argument);
    
    //Desloca-se de todos os caracteres '[' que representam uma dimensao de array, para obter o caracter seguinte, que representara o tipo dos componentes do array.
    char type_components = atype+dimensions_argument;
    
    //O primeiro count a ser desempilhado eh quantidade de componentes na ultima dimensao do array
    for (int i = ((u1)dimensions_argument)-1; i >= 0; i--) {
        
        count[i] = popFromOperandStack(environment->thread);
    }
    
    //Variavel auxiliar para se obter o tamanho total do array
    int total = 1;
    
    //Saira do loop quando for a ultima dimensao a ser alocada, pois n eh o numero de dimensoes menos uma.
    for (int i = 1; i < ((u1)dimensions_argument); i++) {
        //Se count igual a zero, nenhuma dimensao subsequente sera alocada.
        if (count[i] != 0) {
            //Cada dimensao sera multiplicada pela proxima dimensao, obtendo o tamanho total em um componente na primeira dimensao
            total *= count[i];
        }
        else break;
    }
    
    //O array multidimensional
    void* array;
    
    if (type_components == 'B' || type_components == 'Z' || type_components == 'C') {
        array = (u1*) malloc(count[0] * total * sizeof(u1));
        initializeNDArray(dimensions_argument, -1, count, 0, type_components, array);
    }
    else if (type_components == 'S') {
        array = (u2*) malloc(count[0] * total * sizeof(u2));
        initializeNDArray(dimensions_argument, -1, count, 0, type_components, array);
    }
    else if (type_components == 'I' || type_components == 'F') {
        array = (u4*) malloc(count[0] * total * sizeof(u4));
        initializeNDArray(dimensions_argument, -1, count, 0, type_components, array);
    }
    else if (type_components == 'J' || type_components == 'D') {
        array = (u8*) malloc(count[0] * total * sizeof(u8));
        initializeNDArray(dimensions_argument, -1, count, 0, type_components, array);
    }
}


