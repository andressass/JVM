//#################################################################################################
/*! \file M_ECLASS.c
 *
 *  \brief Modulo Exibidor de arquivos ".class".
 *
 *  Modulo responsavel por implementar os metodos relacionados a exibicao de um arquivo ".class".
 */
//##################################################################################################


#define ECLASS_SERV


#include "../include/I_LECLASS.h"
#include <string.h>

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um double em big-endian order
 *
 * \param high_bytes    Bytes de mais alta ordem
 * \param low_bytes     Bytes de mais baixa ordem
 */
double u4ToDouble(u4 high_bytes, u4 low_bytes){
    double resultado;
    unsigned char b[8]; //vetor de 8 Bytes
    
    //Trocamos a ordem dos bytes salvando no vetor de bytes
    for (int i = 0; i < 4; i++) b[i] = low_bytes >> i * 8;
    for (int i = 4; i < 8; i++) b[i] = high_bytes >> i * 8;
    
    
    //Copiamos os bytes do vetor de bytes para o float
    memcpy(&resultado, &b, sizeof(resultado));
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a conversao de um u4 (little-endian) para um float em big-endian order
 *
 * \param bytes    Bytes em u4
 */
float u4ToFLoat(u4 bytes){
    
    float resultado;
    unsigned char b[4]; //vetor de 4 Bytes
    
    //Trocamos a ordem dos bytes salvando no vetor de bytes
    for (int i = 0; i < 4; i++) b[i] = bytes >> i * 8;
    
    //Copiamos os bytes do vetor de bytes para o float
    memcpy(&resultado, &b, sizeof(resultado));
    
    return resultado;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que que realiza a exibicao do pool de constantes de uma estrutura ArqClass
 *
 * \param arq_class Estrutura ArqClass contendo o ponteiro para o pool de constantes a ser exibido
 */
void exibeCtePool(ArqClass* arq_class){

    cp_info* cp;
    
    for (cp = arq_class->constant_pool;
         cp < arq_class->constant_pool + arq_class->constant_pool_count - 1;
         cp++)
    {
        printf("%ld. ", (cp - arq_class->constant_pool +1));
        //Exibimos os campos de acordo com o tipo de estrutura apontada pela tag
        switch (cp->tag) {
                
            case CONSTANT_Class:
                printf("CONSTANT_Class_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 name_index: %d", cp->u.Class.name_index);
                printf("\n}\n");
                break;
                
            case CONSTANT_Fieldref:
                printf("CONSTANT_Fieldref_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 class_index: %d", cp->u.Fieldref.class_index);
                printf("\n\tu2 name_and_type_index: %d", cp->u.Fieldref.name_and_type_index);
                printf("\n}\n");
                break;
                
            case CONSTANT_NameAndType:
                printf("CONSTANT_NameAndType_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 name_index: %d", cp->u.NameAndType.name_index);
                printf("\n\tu2 descriptor_index: %d", cp->u.NameAndType.descriptor_index);
                printf("\n}\n");
                break;
                
            case CONSTANT_Utf8:
                printf("CONSTANT_Utf8_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 lenght: %d", cp->u.Utf8.lenght);
                printf("\n\tu1 bytes[%d]: ", cp->u.Utf8.lenght);
                for(int i=0; i < cp->u.Utf8.lenght; i++) printf ("%c", cp->u.Utf8.bytes[i]);
                printf("\n}\n");
                break;
                
            case CONSTANT_Methodref:
                printf("CONSTANT_Methodref_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 class_index: %d", cp->u.Methodref.class_index);
                printf("\n\tu2 name_and_type_index: %d", cp->u.Methodref.name_and_type_index);
                printf("\n}\n");
                break;
                
            case CONSTANT_InterfaceMethodref:
                printf("CONSTANT_InterfaceMethodref_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 class_index: %d", cp->u.InterfaceMethodref.class_index);
                printf("\n\tu2 name_and_type_index: %d", cp->u.InterfaceMethodref.name_and_type_index);
                printf("\n}\n");
                break;
                
            case CONSTANT_String:
                printf("CONSTANT_String_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu2 string_index: %d", cp->u.String.string_index);
                printf("\n}\n");
                break;
                
            case CONSTANT_Integer:
                printf("CONSTANT_Integer_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu4 bytes: %d", cp->u.Integer.bytes);
                printf("\n}\n");
                break;
                
            case CONSTANT_Float:
                printf("CONSTANT_Float_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu4 bytes: %f", u4ToFLoat(cp->u.Float.bytes));
                printf("\n}\n");
                break;
                
            case CONSTANT_Long:
                printf("CONSTANT_Long_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                
                //Unimos os dois u4 em um long long (u8)
                long long bytesl = cp->u.Long.high_bytes;
                bytesl = bytesl << 32 | cp->u.Long.low_bytes;
                
                printf("\n\tu4 high_bytes: 0x%x", cp->u.Long.high_bytes);
                printf("\n\tu4 low_bytes: 0x%x", cp->u.Long.low_bytes);
                printf("\n\t(u8 bytes: %lld)", bytesl);
                printf("\n}\n");
                cp++; // Ocupa 2 indices
                break;
                
            case CONSTANT_Double:
                printf("CONSTANT_Double_info {");
                printf("\n\tu1 tag: %d", cp->tag);
                printf("\n\tu4 high_bytes: 0x%x", cp->u.Double.high_bytes);
                printf("\n\tu4 low_bytes: 0x%x", cp->u.Double.low_bytes);
                printf("\n\t(u8 bytes: %lf)", u4ToDouble(cp->u.Double.high_bytes, cp->u.Double.low_bytes));
                printf("\n}\n");
                cp++; // Ocupa 2 indices
                break;
                
            default:
                break;
        }
    }
}



//--------------------------------------------------------------------------------------------------
void LECLASS_exibidor(ArqClass* arq_class){
    
    printf("\n####################################################\n");
    printf("DETALHES DO ARQUIVO .CLASS");
    printf("\n####################################################\n");
    printf("MAGIC:\t\t\t 0x%x", arq_class->magic);
    printf("\nMINOR_VERSION:\t\t %d", arq_class->minor_version);
    printf("\nMAJOR_VERSION:\t\t %d", arq_class->major_version);
    printf("\nCONSTANT_POOL_COUNT:\t %d", arq_class->constant_pool_count);
    printf("\n----------------------------------------------------\n");
    printf("CONSTANT POOL:");
    printf("\n----------------------------------------------------\n");
    exibeCtePool(arq_class);
    printf("\n----------------------------------------------------\n");
    printf("\n####################################################\n");
    
}




