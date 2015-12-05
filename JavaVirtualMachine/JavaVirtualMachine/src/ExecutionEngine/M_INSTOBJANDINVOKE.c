//#################################################################################################
/*! \file I_INSTOBJANDINVOKE.c
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
        pushInOperandStack(environment->thread, low_bytes);
        pushInOperandStack(environment->thread, high_bytes);
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
            *value_reference = (u1) value;
        }

        //Se eh de 16bits
        else if (strcmp(attribute_descriptor, "S") == 0){
            u2* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
            *value_reference = (u2) value;
        }
        //Se eh de 32bits
        else {
         u4* value_reference = getClassAttributeReference(class_name, attribute_name, environment);
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
        unsigned long long* value_reference = getObjectAttributeReference(objectRef, attribute_name);
        unsigned long long value = *value_reference;
        
        u4 high_bytes = value >> 32;
        u4 low_bytes = value & 0xFFFFFFFF;
        pushInOperandStack(environment->thread, low_bytes);
        pushInOperandStack(environment->thread, high_bytes);
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
    
    //TODO: Verifica se campo eh estatico
    
    //Verificamos se eh de 32 ou 64 bits
    if (strcmp(attribute_descriptor, "J") == 0 || strcmp(attribute_descriptor, "D") == 0) {
        unsigned long long* value_reference = getObjectAttributeReference(objectRef, attribute_name);
        unsigned long long value;
        
        //Obtemos e concatenamos os bytes
        value = popFromOperandStack(environment->thread);
        value = value << 32 | popFromOperandStack(environment->thread);
        
        //Atualizamos o campo
        *value_reference = value;
    }
    else{
        //Obtemos o valor
        u4 value = popFromOperandStack(environment->thread);
        
        
        //Se eh de 8bits
        if (strcmp(attribute_descriptor, "B") == 0 || strcmp(attribute_descriptor, "C") == 0 ||
            strcmp(attribute_descriptor, "Z") == 0){
            
            u1* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            *value_reference = (u1) value;
        }
        
        //Se eh de 16bits
        else if (strcmp(attribute_descriptor, "S") == 0){
            u2* value_reference = getObjectAttributeReference(objectRef, attribute_name);
            *value_reference = (u2) value;
        }
        //Se eh de 32bits
        else {
            u4* value_reference = getObjectAttributeReference(objectRef, attribute_name);
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
 * Metodo que, dada uma referencia para um objeto e uma estrutura javaClass, verifica se a classe do
 * objeto e a classe ou superclasse do metodo.
 *
 * Se o metodo for protected da classe ou superclasse, verificamos se a classe de Objectref
 *    eh a propria classe ou subclasse do metodo
 *
 *      6.1. Se a classe C do objeto for a classe do metodo, buscamos o metodo em C e invocamos
 *
 *      6.2. Se a C tiver uma superclasse, procuramos recursivamente e invocamos
 *
 *      6.3. Se nao, lancamos a excessao AbstractMethodError
 *
 * \param object Referencia para o objeto
 * \param method_class Referencia para a classe do metodo invocado
 * \param environment Ambiente de execucao
 */
void verifyObjectClasses(Object* object, JavaClass* method_class, Environment* environment){
    
    JavaClass* objectClass = object->handler->javaClass;
    
    char* objectClassName = getClassNameFromConstantPool(objectClass->arqClass->constant_pool,
                                                         objectClass->arqClass->this_class);
    char* methodClassName = getClassNameFromConstantPool(method_class->arqClass->constant_pool, method_class->arqClass->this_class);
    
    //Objeto nao eh da classe ou subclasse da classe do metodo
    if (!isClassSubClassFromClass(objectClassName, methodClassName, environment))
        JVMThrow(AbstractMethodError, environment);
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
    
    //Verificacoes de invokevirtual
    verifyObjectClasses(objectRef, method_class, environment);
    method_info* method = getMethodInfoFromClass(method_class, method_name, method_descriptor);
    if ((method->access_flags & ACC_ABSTRACT)) JVMThrow(AbstractMethodError, environment);
    
    //7. Criamos um novo frame e empilhamos
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    
    //7.1. Passamos os argumentos para o vetor de variaveis locais
    newFrame->localVariablesVector[0] = (u4) objectRef;
    for (int i = 0; i < nParams; i++) newFrame->localVariablesVector[i+1] = params[i];
}


//--------------------------------------------------------------------------------------------------
/*!
 *  Metodo que verifica se existe o metodo existe na classe ou superclasse de uma classe passada
 *
 * \param objectClass Referencia para a classe do objeto
 * \param method_name nome do metodo atual
 * \param method_descriptor descritor do metodo atual
 * \param environment Ambiente de execucao
 * \return 1 caso sim, 0 caso nao
 */
int isMethodInClassOrSuperClass(JavaClass* objectClass, char* method_name, char* method_descriptor,
                                Environment* environment){

    if (getMethodInfoFromClass(objectClass, method_name, method_descriptor)) return 1;
    
    char* superClassName = getClassNameFromConstantPool(objectClass->arqClass->constant_pool,
                                                        objectClass->arqClass->super_class);
    
    if (javaLibIsFrom(superClassName)) return 0;
    //Verificamos recursivamente
    else isMethodInClassOrSuperClass(getClass(superClassName, environment), method_name, method_descriptor, environment);
    
    return 0;
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
 *  8. Se as condicoes acima forem verdadeiras, o metodo a ser invocado eh selecionado pelo seguinte
 *      procedimento de busca. Consideramos C uma superclasse direta da classe atual:
 *
 *      8.1. Se C contiver um metodo de instancia com o mesmo nome e descritor do metodo a ser
 *              invocado. Invocamos o metodo e terminamos.
 *      8.2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
 *              na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
 *      8.3. Se nao, AbstractMethodError.
 *
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
    
    JavaClass* objClass = objectRef->handler->javaClass;
    
    if (!isMethodInClassOrSuperClass(objClass, method_name, method_descriptor, environment))
        JVMThrow(AbstractMethodError, environment);
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
    method_info* method = getMethodInfoFromClass(method_class, method_name, method_descriptor);
    if ((method->access_flags & ACC_STATIC)) JVMThrow(IncompatibleClassChangeError, environment);
    if ((method->access_flags & ACC_ABSTRACT)) JVMThrow(AbstractMethodError, environment);
    
    
    //7. Criamos um novo frame e empilhamos
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    
    
    //7.1. Passamos os argumentos para o vetor de variaveis locais
    newFrame->localVariablesVector[0] = (u4) objectRef;
    for (int i = 0; i < nParams; i++) newFrame->localVariablesVector[i+1] = params[i];
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que invoca um metodo de classe.
 * Recebe 2bytes para montagem de referencia para um metodo no pool de constantes.
 *
 *
 * 1. Resolvemos o a classe do metodo, obtendo uma referencia para javaClass
 *
 * 2. Resolvemos o nome do metodo, obtendo a referencia do method_info
 *
 * 4. Baseado no descritor do metodo, desempilhamos os parametros
 *
 *  7. Criamos um novo frame e empilhamos
 *
 *      7.1. Passamos os argumentos para o vetor de variaveis locais
 *              7.7.1 var_local_0 := argumento_1
 *              7.7.K var_local_[N-1] := argumento_N
 *
 *
 *  Excessoes:
 *      2. Se o metodo nao for estatico, lancamos IncompatibleClassChangeError
 *
 * \param thread Thread que contem a pilha JVM com o frame atual
 */
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
    if (objectRef == NULL) JVMThrow(NullPointerException, environment);
    //TODO: Se a classe de Objectref nao implementa a interface, IncompatibleClassChangeError
    
    
    //6. Verificacoes de invokeinterface
    
    //6.1. Se C contem um metodo de instancia com o mesmo nome e descritor, invocamos e terminamos.
    method_info* method = getMethodInfoFromClass(objectRef->handler->javaClass, method_name, method_descriptor);
    
    // 6.2. Se nao, se C tiver uma superclasse, o procedimento de busca eh realizado recursivamente
    //   na superclasse. O metodo a ser invocado eh o resultado do processo de busca recursiva.
    //   6.3. Se nao, AbstractMethodError.
    if (!isMethodInClassOrSuperClass(objectRef->handler->javaClass, method_name, method_descriptor, environment)) JVMThrow(AbstractMethodError, environment);;
    if ((method->access_flags & ACC_ABSTRACT)) JVMThrow(AbstractMethodError, environment);
    if ((method->access_flags & ACC_PUBLIC)) JVMThrow(IllegalAccessError, environment);
    
    
    //7. Criamos um novo frame e empilhamos
    Frame* newFrame = pushFrame(environment, class_name, method_name, method_descriptor);
    
    
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
    
    environment->thread->PC++;
    u1 atype_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    u4 count = popFromOperandStack(environment->thread);
    
//    if (count < 0) {
//        
//        //TODO:  throws a NegativeArraySizeException.
//    }
    
    JavaArray* arrayref = newJavaArray(atype_argument, count);
    
    pushInOperandStack(environment->thread, (u4) arrayref);

}


//--------------------------------------------------------------------------------------------------
void anewarray(Environment* environment){
    
    environment->thread->PC++;
    u1 indexbyte1_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 indexbyte2_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    u2 index_result = (indexbyte1_argument << 8) | indexbyte2_argument;
    
    u2 atype = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Class.name_index;
    
    //TODO: RESOLVER A REFERENCIA SIMBOLICA DOS TIPO CLASS, ARRAY E INTERFACE
    
    u4 count = popFromOperandStack(environment->thread);
    
    //    if (count < 0) {
    //
    //        //TODO:  throws a NegativeArraySizeException.
    //    }
    
    JavaArray* arrayref = newJavaArray(atype, count);
    
    pushInOperandStack(environment->thread, (u4) arrayref);
}


//--------------------------------------------------------------------------------------------------
void arraylength(Environment* environment){
    
    JavaArray* arrayref = (JavaArray*)popFromOperandStack(environment->thread);
    
        if (arrayref->arrayAddress == NULL) {
    
            //TODO:  throws a NullPointerException.
        }
    
    pushInOperandStack(environment->thread, arrayref->count);
}


//--------------------------------------------------------------------------------------------------
void multianewarray(Environment* environment){
    
    int i;

    environment->thread->PC++;
    u1 indexbyte1_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    environment->thread->PC++;
    u1 indexbyte2_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    u2 index_result = (indexbyte1_argument << 8) | indexbyte2_argument;
    
    u2 atype = environment->thread->vmStack->top->javaClass->arqClass->constant_pool[index_result-1].u.Class.name_index;
    
    //TODO: RESOLVER A REFERENCIA SIMBOLICA DOS TIPO CLASS, ARRAY E INTERFACE
    
    //TODO: During resolution of the symbolic reference to the class, array, or interface type, any of the exceptions documented in Section 5.4.3.1 can be thrown.
    
    //TODO: Otherwise, if the current class does not have permission to access the element type of the resolved array class, multianewarray throws an IllegalAccessError.
    
    //TODO: Otherwise, if any of the dimensions values on the operand stack are less than zero, the multianewarray instruction throws a NegativeArraySizeException.
    
    environment->thread->PC++;
    u1 dimensions_argument = getByteCodeFromMethod(environment->thread->vmStack->top->method_info,
                                                   environment->thread->vmStack->top->javaClass->arqClass->constant_pool
                                                   ,environment->thread->PC);
    
    
    for (i = ((u1)dimensions_argument)-1; i >= 0; i++) {
        
        int *count = (int*) malloc(sizeof(int) * dimensions_argument);
        
        count[i] = popFromOperandStack(environment->thread);
    }
}


