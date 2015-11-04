//#################################################################################################
/*! \file M_INTUSU.c
 *
 *  \brief Modulo de Interacao com o Usuário.
 *
 *  Modulo responsavel por implementar os metodos relacionados a interacao com o usuario.
 */
//##################################################################################################

#define INTUSU_SERV

#define BUFFER_ARQ 100
#define MIN_ENTR   2

#include "../include/I_INTUSU.h"
#include <string.h>


//--------------------------------------------------------------------------------------------------
void INTUSU_executar(int argc, char **argv){
    
    char* arq_entrada = (char *) malloc(BUFFER_ARQ * sizeof(char));

    //Se a chamada do programa foi feita de forma incorreta
    if(argc > 1 && argc < MIN_ENTR){

        printf("\n>> Para executar digite:\n$ ./lclass <nome_do_arquivo.class> \n\n");
        return;
    }
    
    //Inicializamos uma estrutura ArqClass
    ArqClass* arq_class = (ArqClass *) malloc(sizeof(ArqClass));
    
    //Executamos a leitura do arquivo
    LECLASS_leitor(arq_class, argv[1]);
    
    
    //Exibimos as informacoes na tela
    LECLASS_exibidor(arq_class);
    
    free(arq_entrada);
    
    //Liberamos recursivamente as estruturas de arq_class
    LECLASS_free(arq_class);
}
