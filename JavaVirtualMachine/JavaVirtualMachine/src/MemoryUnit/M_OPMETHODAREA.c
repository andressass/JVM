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

//--------------------------------------------------------------------------------------------------
MethodArea* newMethodArea(){
    
    MethodArea* methodArea = (MethodArea*) malloc(sizeof(MethodArea));
    
    methodArea->classCount = 0;
    methodArea->classTable = (ClassTable*) malloc(sizeof(ClassTable));
    
    return methodArea;
}


//--------------------------------------------------------------------------------------------------
JavaClass* findJavaClassOnMethodArea(const char* qualifiedName, MethodArea* methodArea){
    //TODO: Implementar caso as classe sejam java.<...>
    
    //REMOVER________________________________________________
    if (strcmp(qualifiedName,"java/lang/Object") == 0) {
        return (JavaClass*) 1;
    }
    //REMOVER________________________________________________
    
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
    //TODO: Reportar erro de alocacao
    
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
CodeAttribute* getCodeAttributeFromMethod(JavaClass* javaClass,
                                              const char* methodName,
                                        const char* methodDescriptor){
    method_info* method = getMethodInfoFromClass(javaClass, methodName, methodDescriptor);
    
    
    for (int i = 0; i< method->attributes_count; i++) {
        //Obtemos o nome do atributo
        char* attrName = getUTF8FromConstantPool(javaClass->arqClass->constant_pool,
                                                 method->attributes[i]->attribute_name_index);
        
        //Se for o atributo code, criamos, preenchemos e retornamos uma estrutura CodeAttribute
        if(strcmp(attrName, "Code")==0) return parseCode(method->attributes[i]->info);
    }
    
    return NULL;
}


//--------------------------------------------------------------------------------------------------
u1 getByteCodeFromMethod(method_info* methodInfo, void* pc){

    return 0;
}


//--------------------------------------------------------------------------------------------------
void* getClassAttributeReference(const char* className, const char* attributeNamem,
                                 Environment* environment){
    
    return NULL;
}


//--------------------------------------------------------------------------------------------------
void* getObjectAttributeReference(Object* object, const char* attributeName){

    return NULL;
}


//--------------------------------------------------------------------------------------------------
Object* newObjectFromClass(const char* className, Environment* environment ){

    return NULL;
}
