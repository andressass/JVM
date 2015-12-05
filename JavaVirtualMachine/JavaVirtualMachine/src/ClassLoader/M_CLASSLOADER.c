//#################################################################################################
/*! \file M_CLASSLOADER.c
 *
 *  \brief Modulo do Carregador de Classes da JVM.
 *
 *  Modulo responsavel por implementar os servicos relacionados ao carregamento de classes da
 *  JVM.
 */
//##################################################################################################

#include <stdio.h>
#include <string.h>
#include "../../include/ClassLoader/I_CLASSLOADER.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ExecutionEngine/I_EXCEPTION.h"

#define M_CLASSLOADER_SERV


//--------------------------------------------------------------------------------------------------
/*!
 * Método que executa o processo de verificacao da corretude do codigo e compatibilidade da classe
 *
 * \param arqClass Referencia para uma estrutura de arquvo .class
 * \return Resultado de sucesso ou erros
 */
int classVerifier(ArqClass* arqClass){
    
    //Se a classe estiver em uma versao > MajorVersion.MinorVersion
    if (arqClass->major_version > LECLASS_MAJ_Version) return LinkageError_UnsupportedClassVersionError;
    if (arqClass->major_version == LECLASS_MAJ_Version && arqClass->minor_version > LECLASS_MIN_Version)
        return LinkageError_UnsupportedClassVersionError;;
    
    //Se a classe for a sua propria superclasse
    if (strcmp(getClassNameFromConstantPool(arqClass->constant_pool, arqClass->super_class), getClassNameFromConstantPool(arqClass->constant_pool, arqClass->this_class)) == 0)
        return LinkageError_ClassCirculatityError;
    
    return LinkageSuccess;
    
}



//--------------------------------------------------------------------------------------------------
/*!
 * Método que retorna o numero de bytes ocupados pelo descritor de campo
 *
 * \param descriptor Referencia para descritor de campo
 * \return Numero de bytes ocupados pelo descritor
 */
int classGetFieldDescriptorSize(char* descriptor){
    
    if (strcmp(descriptor, "B")== 0){
        return 1;
    }
    else if (strcmp(descriptor, "C")== 0){
        return 1;
    }
    else if (strcmp(descriptor, "D")== 0){
        return 8;
    }
    else if (strcmp(descriptor, "F")== 0){
        return 4;
    }
    else if (strcmp(descriptor, "I")== 0){
        return 4;
    }
    else if (strcmp(descriptor, "J")== 0){
        return 8;
    }
    else if (strcmp(descriptor, "S")== 0){
        return 2;
    }
    else if (strcmp(descriptor, "Z")== 0){
        return 1;
    }
    //    //Arrays
    //    else if (descriptor[0] == '['){
    //        int dimension;
    //        //Calculamos a dimensao do array
    //        for (dimension = 1; dimension < strlen(descriptor) ; dimension++) {
    //            if(descriptor[dimension] != '[') break;
    //        }
    //        //verificamos o tamanho do elemento do array e multiplicamos pela dimensao dele
    //        return dimension * classGetFieldDescriptorSize(&descriptor[dimension]);
    //    }
    //    //Referencias
    else return 4;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que aloca o espaco de memoria necessarios para um determinado campo baseado no descritor
 *
 * \param descriptor Descritor do campo
 * \return Referencia para o ponteiro de memoria a receber o endereco do espaco alocado
 */
void* classInitializeField(char* descriptor){
    
    //Alocamos o espaco de memoria
    void* memoryAddress = (void*) malloc(classGetFieldDescriptorSize(descriptor)*sizeof(void));
    
    //Inicializamos o atributo com o valor default
    if (strcmp(descriptor, "B") == 0){
        u1* byte = memoryAddress;
        *byte = 0;
    }
    else if (strcmp(descriptor, "C")== 0){
        char* c = memoryAddress;
        *c = '0';
    }
    else if (strcmp(descriptor, "D")== 0){
        double* d = memoryAddress;
        *d = 0;
    }
    else if (strcmp(descriptor, "F")== 0){
        float* f = memoryAddress;
        *f = 0;
    }
    else if (strcmp(descriptor, "I")== 0){
        int* i = memoryAddress;
        *i = 0;
    }
    else if (strcmp(descriptor, "J")== 0){
        u8* l = memoryAddress;
        *l = 0;
    }
    else if (strcmp(descriptor, "Z")== 0){
        u1* b = memoryAddress;
        *b = 0;
    }
    else if (strcmp(descriptor, "S")== 0){
        u2* s = memoryAddress;
        *s = 0;
    }
    return memoryAddress;
}


//--------------------------------------------------------------------------------------------------
Fields* classInitializeFields(JavaClass* javaClass, u2 flagsAccept, u2 flagsRegect){
    
    //Numero de campos
    int fieldsCount = javaClass->arqClass->fields_count;
    
    //Resultado
    Fields* fields;
    
    //Alocamos espaco na tabela de campos para o numero de campos
    fields = (Fields*) malloc(sizeof(Fields));
    fields->fieldsCount = 0;
    
    fields->fieldsTable = (FieldsTable*) malloc(sizeof(FieldsTable));
    
    //Inicializamos cada campo estatico da classe
    for (int i = 0; i < fieldsCount; i++) {
        
        //Verificamos as condicoes das flags
        if (javaClass->arqClass->fields[i].access_flags & flagsAccept &&
            !(javaClass->arqClass->fields[i].access_flags & flagsRegect)){
            
            //Redimensionamos a tabela de atributos estaticos da classe
            fields->fieldsTable = (FieldsTable*) realloc(fields->fieldsTable, (fields->fieldsCount+1) * sizeof(FieldsTable));
            
            //Referencia para as informacoes do campo na estrutura de .class
            field_info* fieldInfo = &javaClass->arqClass->fields[i];
            fields->fieldsTable[fields->fieldsCount].fieldInfo = fieldInfo;
            
            
            //Passamos uma referencia para o nome
            fields->fieldsTable[fields->fieldsCount].name =
            getUTF8FromConstantPool(javaClass->arqClass->constant_pool,
                                    fieldInfo->name_index);
            
            //Passamos uma referencia para o descritor do campo
            fields->fieldsTable[fields->fieldsCount].descriptor =
            getUTF8FromConstantPool(javaClass->arqClass->constant_pool,
                                    fieldInfo->descriptor_index);
            
            //Alocamos o espaco de memoria para o campo
            fields->fieldsTable[fields->fieldsCount].memoryAddress = classInitializeField(fields->fieldsTable[fields->fieldsCount].descriptor);
            
            //Atualizamos a quantidade de fields
            fields->fieldsCount++;
        }
    }
    return fields;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Método que aloca todos os espaços de memoria necessarios para a classe e inicializa os campos
 * estaticos com os valores default
 *
 * \param javaClass Referencia para a estrutura de classe a ser inicializada
 * \return Resultado de sucesso ou erros
 */
int classPreparing(JavaClass* javaClass){
    
    javaClass->staticFields = classInitializeFields(javaClass, ACC_STATIC, ACC_FINAL);
    javaClass->objectList = NULL;
    return LinkageSuccess;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que, dada uma estrutura de arquivo .class, verifica se todas as suas superclasses ou
 * superinterfaces foram carregadas. Caso não, carrega as mesmas de forma recursiva.
 *
 * \param arqClass Nome qualificado da classe ou interface a ser carregada
 * \param environment ambiente atual de execucao
 * \return Estrutura arqClass preenchida com os dados da classe carregada
 */
void classSuperClassChecker(ArqClass* arqClass, Environment* enviroment){
    
    char* superClassName = getClassNameFromConstantPool(arqClass->constant_pool, arqClass->super_class);
    JavaClass* superClass;
    //Verificamos se a superclasse ja fora carregada. Caso nao, carregamos recursivamente
    if(findJavaClassOnMethodArea(superClassName, enviroment->methodArea) == NULL)
        superClass = loadCLass(superClassName, enviroment);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Método que executa o processo de inicializacao de uma classe ou interface.
 *
 * Passos:
 *
 * 1. Verifica e, se necessario, carrega recursivamente todas as suas superclasse ou interfaces
 * 2. Executa o inicializador de campos estáticos (exceto os final static, que são definidos em tempo
 *     de compilacao)
 *
 * \param javaClass Referencia para a estrutura de classe a ser inicializada
 * \param environment ambiente atual de execucao
 * \return Estrutura arqClass preenchida com os dados da classe carregada
 */
int classInitializer(JavaClass* javaClass, Environment* environment){
    
    //Verificacao e carregamento de superclasses
    classSuperClassChecker(javaClass->arqClass, environment);
    
    //Empilhamos o metodo <clinit> da classe
    environment->thread->PC--; //Metodo eh invocado sem ser chamado, precisa decrementar PC
    pushFrame(environment, getClassNameFromConstantPool(javaClass->arqClass->constant_pool, javaClass->arqClass->this_class), "<clinit>", "()V");
    
    return InitializerSuccess;
    
}


//--------------------------------------------------------------------------------------------------
JavaClass* loadCLass(const char* qualifiedName, Environment* environment){
    
    JavaClass* javaClass = (JavaClass*) malloc(sizeof(JavaClass));
    ArqClass* arqClass = (ArqClass*) malloc(sizeof(ArqClass));
    int opResult; //!< Resultado das operacoes (checagem de erros)
    
    //!LOADING - Fazemos a leitura do arquivo .class
    char* classExtension = ".class";
    
    //Nome completo do arquivo
    char* fileName = (char*)malloc((strlen(qualifiedName)+strlen(classExtension)+1) * sizeof(char));
    strcpy(fileName, qualifiedName);
    strcat(fileName, classExtension);
    
    //Lemos o arquivo .class
    opResult = LECLASS_leitor(arqClass, fileName);
    
    //Caso tenha ocorrido algum erro de leitura, apontamos
    if (opResult != LinkageSuccess) {
        LECLASS_exibeErroOperacao(opResult, fileName);
        JVMstopAbrupt(NULL);
        return NULL;
    }
    javaClass->arqClass = arqClass;
    
    //LINKING - VERIFYING - Verificamos a corretude do codigo da classe
    // Parte ja realizada na leitura do arquivo
    opResult = classVerifier(arqClass);
    if (opResult != LinkageSuccess) {
        LECLASS_exibeErroOperacao(opResult, fileName);
        JVMstopAbrupt(NULL);
        return NULL;
    }
    
    //LINKING - PREPARING - Alocamos todos os espacos de memoria necessarios para a classe
    // Campos estaticos sao criados e inicializados com os valores default
    classPreparing(javaClass);
    
    //INITIALIZATION - Executamos o o inicializador estatico <clinit>
    
    //Adicionamos a classe carregada na area de metodos
    addJavaClassToMethodArea(javaClass, environment->methodArea);
    
    classInitializer(javaClass, environment);
    
    LECLASS_exibidor(javaClass->arqClass);
    
    //Retornamos a estrutura inicializada
    return javaClass;
}
