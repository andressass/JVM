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
#include "../../include/ClassLoader/I_CLASSLOADER.h"
#include "../../include/ClassLoader/I_LECLASS.h"

#define M_CLASSLOADER_SERV


//--------------------------------------------------------------------------------------------------
JavaClass* loadCLass(const char* qualifiedName){

    JavaClass* javaClass = (JavaClass*) malloc(sizeof(JavaClass));
    ArqClass* arqClass = (ArqClass*) malloc(sizeof(ArqClass));
    int resultadoOperacao;
    
    
    //Resolvemos o nome qualificado para o endereco da classe
    // TODO

    
    //!LOADING - Fazemos a leitura do arquivo .class
    resultadoOperacao = LECLASS_leitor(arqClass, qualifiedName);
    
    //Caso tenha ocorrido algum erro de leitura, apontamos
    if (resultadoOperacao != LinkageSuccess) {
        LECLASS_exibeErroOperacao(resultadoOperacao);
        return NULL;
    }
    
    //LINKING - Verificamos (e se necessario carregamos) as superclasses e ou superinterfaces
    // diretas e indiretas
    
    //LINKING - VERIFYING - Verificamos a corretude do codigo da classe
    
    //LINKING - PREPARING - Alocamos todos os espacos de memoria necessarios para a classe
    // Campos estaticos sao criados e inicializados com os valores default

    //INITIALIZATION - Executamos o metodo <clinit>
    
    //Retornamos a estrutura criada
    return javaClass;
}
