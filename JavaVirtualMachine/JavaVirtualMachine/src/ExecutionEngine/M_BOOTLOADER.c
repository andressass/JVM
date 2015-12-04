//#################################################################################################
/*! \file M_BOOTLOADER.c
 *
 *  \brief Modulo de Inicializacao da JVM.
 *
 *  Modulo responsavel por implementar os metodos relacionados a inicializacao de estruturas e 
 * da execucao do sistema.
 */
//##################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/Estruturas/E_JVM.h"
#include "../../include/Estruturas/JAVASTRING.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/ExecutionEngine/I_INTERPRETER.h"


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo que configura e empilha um novo frame para o metodo main da classe chamada pela JVM
 *
 * \param environment Ambiente de execucao atual
 * \param argc Numero de argumentos do programa
 * \param argv Vetor de vetores de char passados pelo usuario
 */
void configureClassMain(Environment* environment, int argc, const char* argv[]){

    //Empilhamos o metodo main a ser inicializado
    Frame* newFrame = pushFrame(environment, argv[1], "main", "([Ljava/lang/String;)V");
    
    //Obtemos a quantidade de caracteres a partir de argv[1]
    int argv_size = argc;
    for(int i = 1; i < argc; i++) argv_size += strlen(argv[i]);
    
    //Concatenamos argv em uma unica string
    char* argv_parsed = (char*)malloc(argv_size*sizeof(char));
    strcpy(argv_parsed, argv[1]);
    for (int i = 2; i < argc; i++) {
        strcat(argv_parsed, " ");
        strcat(argv_parsed, argv[i]);
    }
    
    //Criamos uma estrutura de String Java para receber o argv_parsed
    JavaString* string_info = newJavaString(argv_parsed);
    
    newFrame->localVariablesVector[0] = (u4) string_info; //Passamos o argumento argv
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo inicial do sistema
 *
 */
int main(int argc, const char * argv[]) {

    //Alocamos espaco para o ambiente de execucao
    Environment* environment = (Environment*) malloc(sizeof(Environment));
    
    //Criamos a area de metodos e a thread e as associamos ao enviroment
    environment->methodArea = newMethodArea();
    environment->thread = newThread();
    
    //Empilhamos o metodo main
    configureClassMain(environment, argc, argv);
    
    //Passamos o ambiente de execucao para o interpretador
    execute(environment);
    
    printf("\n_____________________");
    printf("\n❆   ❆         ❆    ❆ ");
    printf("\n  ❆   /\\ ❆     ❆  ");
    printf("\n     /  \\   ❆      ❆");
    printf("\n ❆  /    \\     ");
    printf("\n   /      \\   ❆  ❆");
    printf("\n ❆ /      \\    ");
    printf("\n❆ /        \\ ❆     ❆");
    printf("\n  /        \\    ❆");
    printf("\n /          \\ ❆ ");
    printf("\n/____________\\     ❆");
    printf("\n     |   |   _v_ ❆ ");
    printf("\n     |___|  |_|_|   ❆");
    printf("\n_____________________");
    printf("\nFeliz Natal, Ladeira!\n\n");

    return 0;
}
