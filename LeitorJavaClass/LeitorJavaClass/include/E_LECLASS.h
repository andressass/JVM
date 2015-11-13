//#################################################################################################
/*! \file E_LECLASS.h
 *
 *  \brief Estruturas do Leitor e Exibidor de arquivos ".class".
 * 
 *  Arquivo com a definicao das estruturas, tipos e constantes associadas ao
 *  sistema.
 */
//##################################################################################################

#ifndef E_LECLASS_H
#define E_LECLASS_H


//--------------------------------------------------------------------------------------------------
// Definicoes de sucesso e erro de operacoes

//Erros do leitor .class
#define LinkageError_ClassFormatError                   1 //!< Arquivo em corrompido
#define LinkageError_UnsupportedClassVersionError       2 //!< Arquivo possui versao nao suportada
#define LinkageError_ClassCirculatityError              3 //!< Classe seria a sua propria superclasse
#define LinkageError_NoClassDefFoundError               4 //!< Erro de abertura do arquivo
#define LinkageSuccess                                  0 //!< Sucesso na operacao


//--------------------------------------------------------------------------------------------------
// Definicoes de prerequisitos do sistema

//Erros de arquivo
#define LECLASS_MIN_Version        0
#define LECLASS_MAJ_Version        48


//--------------------------------------------------------------------------------------------------
//Tags do Pool de Constantes

#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1


//--------------------------------------------------------------------------------------------------
//Tipos de dados

typedef unsigned char u1; //!< Representa 1 byte
typedef unsigned short u2; //!< Representa 2 bytes
typedef unsigned int  u4; //!< Representa 3 bytes
typedef unsigned short resultado; //!< Representa o resultado de uma operacao


//--------------------------------------------------------------------------------------------------
//! Estrutura do Pool de Constantes
/*! 
 * Estrutura utilizada para a representacao de um pool de constantes.
 */
typedef struct constPool{
    u1 tag;
    union{
        struct{
            u2 name_index;
        } Class;
        struct{
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref;
        struct{
            u2 name_index;
            u2 descriptor_index;
        } NameAndType;
        struct{
            u2 lenght;
            u1* bytes; //!< bytes[length]
        } Utf8;
        struct{
            u2 class_index;
            u2 name_and_type_index;
        } Methodref;
        struct{
            u2 class_index;
            u2 name_and_type_index;
        } InterfaceMethodref;
        struct{
            u2 string_index;
        } String;
        struct{
            u4 bytes;
        } Integer;
        struct{
            u4 bytes;
        } Float;
        struct{
            u4 high_bytes;
            u4 low_bytes;
        } Long;
        struct{
            u4 high_bytes;
            u4 low_bytes;
        } Double;
    } u;
} cp_info;


//--------------------------------------------------------------------------------------------------
//! Estrutura de Atributos
/*!
 * Estrutura utilizada para a representacao de um atributo de um arquivo ".class".
 */
typedef struct attribute{
    u2 attribute_name_index;
    u4  attribute_length;
    u1* info;   

} attribute_info;

//--------------------------------------------------------------------------------------------------
//! Estrutura de Campos e Metodos
/*!
 * Estrutura utilizada para a representacao de um campo ou metodo.
 */
typedef struct fieldAndMethod{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info** attributes;

} field_or_method;
typedef struct fieldAndMethod field_info; //!< Estrutura utilizada para a representacao de um campo.
typedef struct fieldAndMethod method_info; //!< Estrutura utilizada para a representacao de
                                           //!um metodo.


//--------------------------------------------------------------------------------------------------
//! Estrutura de Arquivo .class
/*!
 * Estrutura utilizada para a representacao de um arquivo ".class".
 */
typedef struct arqClass {
    u4                  magic;
    u2                  minor_version;
    u2                  major_version;
    u2                  constant_pool_count;
    cp_info*            constant_pool;
    u2                  access_flags;
    u2                  this_class;
    u2                  super_class;
    u2                  interfaces_count;
    u2*                 interfaces;
    u2                  fields_count;
    field_info*         fields;
    u2                  methods_count;
    method_info*        methods;
    u2                  attributes_count;
    attribute_info**    attributes;


} ArqClass;

#endif
