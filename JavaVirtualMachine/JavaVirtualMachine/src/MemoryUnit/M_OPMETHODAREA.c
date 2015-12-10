//#################################################################################################
/*! \file M_OPMETHODAREA.c
 *
 *  \brief Modulo da area de metodos da JVM
 *
 *  Modulo responsavel por implementar os metodos relacionados as operacoes que involvam a area de 
 *  metodos
 */
//##################################################################################################


#define OPMETHODAREA_SERV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ClassLoader/I_CLASSLOADER.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/ExecutionEngine/I_EXCEPTION.h"
#include "../../include/Util/I_JAVADECODER.h"

//--------------------------------------------------------------------------------------------------
MethodArea* newMethodArea(){
    
    MethodArea* methodArea = (MethodArea*) malloc(sizeof(MethodArea));
    
    methodArea->classCount = 0;
    methodArea->classTable = (ClassTable*) malloc(sizeof(ClassTable));
    
    return methodArea;
}


//--------------------------------------------------------------------------------------------------
JavaClass* findJavaClassOnMethodArea(const char* qualifiedName, MethodArea* methodArea){

    //Se for uma classe de bibliotecas java
    if (javaLibIsFrom(qualifiedName)) return (JavaClass*) 1;
    
    //Pesquisamos a classe
    for (int i = 0; i < methodArea->classCount; i++)
        if (strcmp(qualifiedName, methodArea->classTable[i].name)==0)
            return methodArea->classTable[i].javaClass;
    
    return NULL;
}


//--------------------------------------------------------------------------------------------------
JavaClass* getClass(const char* qualifiedName, Environment* environment){
    
    JavaClass* class;
    
    //Verificamos se a classe esta na area de metodos
    class = findJavaClassOnMethodArea(qualifiedName, environment->methodArea);
    //Caso nao, carregamos
    if(class == NULL) class = loadCLass(qualifiedName, environment);

    return class;
}


//--------------------------------------------------------------------------------------------------
void addJavaClassToMethodArea(JavaClass* javaClass, MethodArea* methodArea){

    methodArea->classCount ++;
    methodArea->classTable = realloc(methodArea->classTable,
                                                 methodArea->classCount *sizeof(ClassTable));
    //Reportar erro de alocacao
    if(methodArea->classTable == NULL)
        JVMstopAbrupt("Erro de alocacao de memoria na area de metodos.");
    
    //Adicionamos a referencia para a estrutura de classe
    methodArea->classTable[methodArea->classCount-1].javaClass = javaClass;
    
    //Adicionamos a referencia para a o nome da classe
    methodArea->classTable[methodArea->classCount-1].name =
    getClassNameFromConstantPool(javaClass->arqClass->constant_pool, javaClass->arqClass->this_class);
}


//--------------------------------------------------------------------------------------------------
method_info* getMethodInfoFromClass(JavaClass* javaClass,
                                          const char* methodName,
                                          const char* methodDescriptor){
    
    for (int i = 0 ; i< javaClass->arqClass->methods_count; i++) {
        
        //Buscamos nome do metodo
        char* actMethodName =
        getUTF8FromConstantPool(javaClass->arqClass->constant_pool,
                                javaClass->arqClass->methods[i].name_index);
        
        //Buscamos descritor do metodo
        char* actMethodDescriptor =
        getUTF8FromConstantPool(javaClass->arqClass->constant_pool,
                                javaClass->arqClass->methods[i].descriptor_index);
        
        
        //Comparamos para verificar se eh ou nao o metodo. Caso sim, retornamos o metodo.
        if (strcmp(methodName, actMethodName) == 0 &&
            strcmp(methodDescriptor, actMethodDescriptor) == 0) {
            return &javaClass->arqClass->methods[i];
        }
    }
    
    return NULL;
}


//--------------------------------------------------------------------------------------------------
CodeAttribute* getCodeFromMethodInfo(method_info* method, cp_info* constant_pool){
    
    for (int i = 0; i< method->attributes_count; i++) {
        //Obtemos o nome do atributo
        char* attrName = getUTF8FromConstantPool(constant_pool,
                                                 method->attributes[i].attribute_name_index);
        
        //Se for o atributo code, criamos, preenchemos e retornamos uma estrutura CodeAttribute
        if(strcmp(attrName, "Code")==0) {
            free(attrName);
            return parseCode(method->attributes[i].info);
        }
    }

    return NULL;
}


//--------------------------------------------------------------------------------------------------
CodeAttribute* getCodeAttributeFromMethod(JavaClass* javaClass,
                                              const char* methodName,
                                        const char* methodDescriptor){
    method_info* method = getMethodInfoFromClass(javaClass, methodName, methodDescriptor);
    
    
    return getCodeFromMethodInfo(method, javaClass->arqClass->constant_pool);
}


//--------------------------------------------------------------------------------------------------
u1 getByteCodeFromMethod(method_info* methodInfo, cp_info* constant_pool, int pc){
    
    u1 result;
    
    CodeAttribute* code = getCodeFromMethodInfo(methodInfo, constant_pool);
    
    result = code->code[pc];
    
    free(code);
    
    return result;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dado um ponteiro para uma estrutura field_info e o pool de constantes contendo as
 * constantes relativas ao campo, busca e retorna uma referencia para o atributo constant_value,
 * o qual estara preenchido.
 *
 * \param field Referencia para o field_info contendo a referencia para constant_value
 * \param cp Referencia para o pool de constantes da classe do campo
 * \return Referencia para uma estrutura ConstantValueAttribute referente ao campo buscado
 */
ConstantValueAttribute* getConstantValueAtrributeFromField(field_info* field, cp_info* cp){
    
    for (int j = 0; j < field->attributes_count; j++) {
        
        if (strcmp(getUTF8FromConstantPool(cp, field->attributes[j].attribute_name_index), "ConstantValue")==0) {
            ConstantValueAttribute* constantValue = parseConstantValue(field->attributes[j].info);
            return constantValue;
        }
    }

    return NULL;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, da uma referencia para uma estrtutura javaClass e um nome de um atributo, busca
 * um atributo final na classe com este nome. Caso exista, retonamos uma referencia para o valor
 * do atributo no pool de constantes. Caso nao exista, retorna nulo.
 *
 * \param javaClass Referencia para a Estrutura javaClass
 * \param attributeName Nome do atributo a ser pesquisado
 * \return Referencia para o valor do atributo final
 */
void* getClassFinalStaticAttributeReference(JavaClass* javaClass, const char* attributeName){
    
    for (int i = 0; i< javaClass->arqClass->fields_count; i++) {
        
        field_info* field = &javaClass->arqClass->fields[i];
        
        if ( strcmp(getUTF8FromConstantPool(javaClass->arqClass->constant_pool, field->name_index), attributeName) == 0 &&
            field->access_flags & ACC_FINAL &&
            field->access_flags & ACC_STATIC ) {
            
            //Procuramos o atributo constant value
            ConstantValueAttribute* contantValue =
            getConstantValueAtrributeFromField(field, javaClass->arqClass->constant_pool);
            
            //Retornamos a referencia para o valor (sempre se encontra apos a tag, nao importa o tipo)
            if (contantValue) return &javaClass->arqClass->constant_pool[contantValue->constantvalue_index].u.Float.bytes;
        }
    }
    return NULL;
}


//--------------------------------------------------------------------------------------------------
void* getClassAttributeReference(const char* className, const char* attributeName,
                                 Environment* environment){
    
    JavaClass* class = getClass(className, environment);
    
    //TODO: Checar restricao de acesso ao atributo
    
    for (int i = 0 ; i < class->staticFields->fieldsCount; i++)
        if (strcmp(attributeName, class->staticFields->fieldsTable[i].name) == 0)
            return class->staticFields->fieldsTable[i].memoryAddress;
    
    //Verificamos se é final
    return getClassFinalStaticAttributeReference(class, attributeName);
}


//--------------------------------------------------------------------------------------------------
void* getObjectAttributeReference(Object* object, const char* attributeName){
    
    //TODO: Checar restricao de acesso ao atributo
    
    for (int i = 0; i < object->handler->fields->fieldsCount; i++) {
        if (strcmp(attributeName, object->handler->fields->fieldsTable[i].name)==0) {
            return object->handler->fields->fieldsTable[i].memoryAddress;
        }
    }
    return NULL;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, da uma referencia para uma estrutura javaClass e uma referencia a um objeto, adiciona
 * este objeto na lista de objetos da classe. A adicao acontece na forma de empilhamento.
 *
* \param object Referencia ao objeto adicionado
 * \param javaClass Referencia para a Estrutura javaClass
 */
void addObjectReferenceToJavaClass(Object* object, JavaClass* javaClass){
    
    ObjectList* newObject = (ObjectList*)malloc(sizeof(ObjectList));
    
    newObject->object = object;

    //Caso a lista esteja vazia, simplesmente adicionamos o objeto.
    if (!javaClass->objectList) {
        javaClass->objectList = newObject;
        newObject->next = NULL;
    }
    //Caso nao, adicionamos o na lista (em forma de pilha)
    else{
        newObject->next = javaClass->objectList;
        javaClass->objectList = newObject;
    }
}

//--------------------------------------------------------------------------------------------------
Object* newObjectFromClass(const char* className, Environment* environment ){

    JavaClass* javaClass = getClass(className, environment);
    
    Object* object = (Object*) malloc(sizeof(Object));
    object->handler = (Handler*) malloc(sizeof(Handler));
    
    object->handler->javaClass = javaClass;
    
    //Alocamos espaco na tabela de campos para o numero de campos
    object->handler->fields = classInitializeFields(javaClass, 0xFFFF, ACC_STATIC);
    
    //Adicionamos uma referencia ao objeto na lista de objetos da classe
    addObjectReferenceToJavaClass(object, javaClass);

    return object;
}
