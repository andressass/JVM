//#################################################################################################
/*! \file M_LCLASS.c
 *
 *  \brief Modulo Leitor de arquivos ".class".
 *
 *  Modulo responsavel por implementar os metodos relacionados a exibicao de um arquivo ".class".
 */
//##################################################################################################


#define LCLASS_SERV

#include "../include/I_LECLASS.h"

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que le o pool de constantes de constantes de um arquivo, retornando um ponteiro para uma
 * estrutura inicializada de pool de constantes.
 *
 * \param constant_pool_count   Contador do pool de constantes.
 * \param arq                   Arquivo a ser lido.
 */
cp_info* leCtePool(u2 constant_pool_count, FILE* arq){

    cp_info* constant_pool = (cp_info *) malloc(constant_pool_count * sizeof(cp_info));
    cp_info* cp;
    
    for (cp = constant_pool; cp < constant_pool + constant_pool_count - 1; cp++) {

        cp->tag = u1Le(arq); //Leitura da tag
        
        //Preenchemos os campos de acordo com o tipo de estrutura apontada pela tag
        switch (cp->tag) {
        
            case CONSTANT_Class:
                cp->u.Class.name_index = u2Le(arq);
                break;
                
            case CONSTANT_Fieldref:
                cp->u.Fieldref.class_index = (u2) (malloc(sizeof(u2)));
                cp->u.Fieldref.class_index = u2Le(arq);
                cp->u.Fieldref.name_and_type_index = u2Le(arq);
                break;
                
            case CONSTANT_NameAndType:
                cp->u.NameAndType.name_index = u2Le(arq);
                cp->u.NameAndType.descriptor_index = u2Le(arq);
                break;
                
            case CONSTANT_Utf8:
                cp->u.Utf8.lenght = u2Le(arq);
                //Alocamos espaco para o vetor de caracteres
                cp->u.Utf8.bytes = (u1 *) malloc(cp->u.Utf8.lenght * sizeof(u1));
                //Lemos cada um dos caracteres
                for (int i = 0; i < cp->u.Utf8.lenght; i++) cp->u.Utf8.bytes[i] = u1Le(arq);
                break;
                
            case CONSTANT_Methodref:
                cp->u.Methodref.class_index = u2Le(arq);
                cp->u.Methodref.name_and_type_index = u2Le(arq);
                break;
                
            case CONSTANT_InterfaceMethodref:
                cp->u.InterfaceMethodref.class_index = u2Le(arq);
                cp->u.InterfaceMethodref.name_and_type_index = u2Le(arq);
                break;
                
            case CONSTANT_String:
                cp->u.String.string_index = u2Le(arq);
                break;
                
            case CONSTANT_Integer:
                cp->u.Integer.bytes = u4Le(arq);
                break;
                
            case CONSTANT_Float:
                cp->u.Float.bytes = u4Le(arq);
                break;
                
            case CONSTANT_Long:
                cp->u.Long.high_bytes = u4Le(arq);
                cp->u.Long.low_bytes = u4Le(arq);
                cp++; //Long ocupa 2 indices no pool de constantes
                break;
                
            case CONSTANT_Double:
                cp->u.Double.high_bytes = u4Le(arq);
                cp->u.Double.low_bytes = u4Le(arq);
                cp++; //Double ocupa 2 indices no pool de constantes
                break;
                
            default:
                break;
        }
    }
    return constant_pool;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que le o um atributo de um arquivo ".class", retornando um ponteiro para uma
 * estrutura inicializada de atributo.
 *
 * \param arq Arquivo a ser lido.
 */
attribute_info* leAtributo(FILE* arq){
    attribute_info* atributo = (attribute_info *) malloc(sizeof(attribute_info));
    
    atributo->attribute_name_index = u2Le(arq);
    atributo->attribute_length = u4Le(arq);
    atributo->info = (u1 *) malloc(atributo->attribute_length * sizeof(u1));
    for (int i = 0; i < atributo->attribute_length; i++) atributo->info[i] = u1Le(arq);
    
    return atributo;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que le o uma estrutura referente a um campo ou metodo de um arquivo ".class", retornando
 * um ponteiro para uma estrutura inicializada de campo ou metodo.
 *
 * \param count Numero de metodos ou campos a serem lidos.
 * \param arq   Arquivo a ser lido.
 */
field_or_method* leCampMetd(u2 count, FILE* arq){
    
    field_or_method* resultado = (field_or_method * ) malloc(count * sizeof(field_or_method));
    field_or_method* fi;
    
    for (fi = resultado; fi < resultado + count; fi++) {
        fi->access_flags = u2Le(arq);
        fi->name_index = u2Le(arq);
        fi->descriptor_index = u2Le(arq);
        fi->attributes_count = u2Le(arq);

        //Lemos os atributos
        fi->attributes = (attribute_info **) malloc(fi->attributes_count * sizeof(attribute_info*));
        for (int i = 0; i < fi->attributes_count; i++) fi->attributes[i] = leAtributo(arq);
        
    }
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que realiza a leitura de um arquivo ".class" preeenchendo uma estrutura ArqClass.
 *
 * \param arq_class Estrutura de arquivo ".class" a ser preenchida
 * \param arq       Arquivo ".class" a ser lido.
 * \return          Resultado da operacao
 */
resultado arquivoParaArqClass(ArqClass* arq_class, FILE* arq){
    
    //Lemos e verificamos o Magic e as versoes
    arq_class->magic = u4Le(arq);
    if (arq_class->magic != 0xcafebabe) return LECLASS_ERRO_ArqInvalido;
    arq_class->minor_version = u2Le(arq);
    if (arq_class->minor_version < LECLASS_MIN_Version) return LECLASS_ERRO_ArqVersIncmp;
    arq_class->major_version = u2Le(arq);
    if (arq_class->major_version > LECLASS_MAJ_Version) return LECLASS_ERRO_ArqVersIncmp;
    
    //Constant pool
    arq_class->constant_pool_count = u2Le(arq);
    arq_class->constant_pool = leCtePool(arq_class->constant_pool_count, arq); //Lemos o constant pool

    arq_class->access_flags = u2Le(arq);
    arq_class->this_class = u2Le(arq);
    arq_class->super_class = u2Le(arq);
    
    //Lemos as interfaces
    arq_class->interfaces_count = u2Le(arq);
    arq_class->interfaces = (u2 *) malloc(arq_class->interfaces_count* sizeof(u2));
    for (int i = 0; i < arq_class->interfaces_count; i++) arq_class->interfaces[i]=u2Le(arq);

    //Lemos os campos
    arq_class->fields_count = u2Le(arq);
    arq_class->fields = leCampMetd(arq_class->fields_count, arq);
    
    //Lemos os metodos
    arq_class->methods_count = u2Le(arq);
    arq_class->methods = leCampMetd(arq_class->methods_count, arq);
    
    //Lemos os atributos
    arq_class->attributes_count = u2Le(arq);
    arq_class->attributes = (attribute_info **)
                            malloc(arq_class->attributes_count * sizeof(attribute_info*));
    for (int i = 0; i < arq_class->attributes_count; i++) arq_class->attributes[i] = leAtributo(arq);
    
    return LECLASS_SUCESSO;
}


//--------------------------------------------------------------------------------------------------
resultado LECLASS_leitor(ArqClass* arq_class, const char* arq){

    FILE *entrada;

    //Obtemos o arquivo de entrada
    entrada = obter_entrada(arq);
    
    //Erro de abertura de arquivo
    if (!entrada) return LECLASS_ERRO_ArqAbertura;

    //Lemos os dados e salvamos na estrutura ArqClass
    resultado result = arquivoParaArqClass(arq_class, entrada);
    
    fclose(entrada);
    
    return result;

}