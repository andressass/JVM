//#################################################################################################
/*! \file M_OPCLASS.c
 *
 *  \brief Modulo Operador de estruturas ".class".
 *
 *  Modulo responsavel por implementar os metodos relacionados a manutencao de uma estrutura 
 *  ArqClass
 */
//##################################################################################################


#define OPCLASS_SERV


#include "../../include/ClassLoader/I_LECLASS.h"

//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que libera as estruturas de um pool de constantes recursivamente.
 *
 * \param arq_class Estrutura contendo o ctePoll a ser liberado.
 */
void freeCtePool(ArqClass* arq_class){
    cp_info* cp;
    
    for (cp = arq_class->constant_pool;
         cp < arq_class->constant_pool + arq_class->constant_pool_count - 1;
         cp++)
    {
        //Liberamos o vetor de caracteres
        if (cp->tag == CONSTANT_Utf8) free(cp->u.Utf8.bytes);
    }
    
    //Liberamos o pool de constantes
    free(arq_class->constant_pool);
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que libera recursivamente uma estrutura de atributo.
 *
 * \param arq Arquivo a ser lido.
 */
void freeAtributo(attribute_info* atributo){

    //Liberamos a informacao do atributo
    free(atributo->info);
    
    //Liberamos o atributo
    free(atributo);
    
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que libera recursivamente uma estrutura de campo ou metodo.
 *
 * \param count     Numero de estruturas a serem liberadas.
 * \param f_or_m    Ponteiro para as estruturas a serem liberadas.
 */
void freeCampMetd(u2 count, field_or_method* f_or_m){
    
    field_or_method* fi;
    
    for (fi = f_or_m; fi < f_or_m + count; fi++) {
        
        //Liberamos cada atributo
        for (int i = 0; i < fi->attributes_count; i++) freeAtributo(&fi->attributes[i]);
        
        //Liberamos o vetor de atributos
        free(fi->attributes);
    }
    
    free(f_or_m);
}


//--------------------------------------------------------------------------------------------------
void LECLASS_free(ArqClass* arq_class){
    
    //Liberamos o pool de constantes
    freeCtePool(arq_class);
    
    //Liberamos as interfaces
    free(arq_class->interfaces);
    
    //Liberamos os campos
    freeCampMetd(arq_class->fields_count, arq_class->fields);
    
    //Liberamos os metodos
    freeCampMetd(arq_class->methods_count, arq_class->methods);
    
    //Liberamos os atributos
    for (int i = 0; i < arq_class->attributes_count; i++) freeAtributo(&arq_class->attributes[i]);
    free(arq_class->attributes);
    
    //Liberamos a estrutura ArqClass
    free(arq_class);
    
}