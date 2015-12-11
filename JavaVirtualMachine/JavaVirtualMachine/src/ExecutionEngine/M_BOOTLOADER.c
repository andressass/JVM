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
#include "../../include/Estruturas/JAVAARRAY.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/ExecutionEngine/I_INTERPRETER.h"
#include "../../include/ExecutionEngine/I_EXCEPTION.h"


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
    
    //Criamos o conteudo do array e o JavaArray a receber o conteudo
    void* arrayAddress;
    u4* stringArray = (u4*) malloc((argc-2)*sizeof(u4));
    JavaArray* array = newJavaArray(T_INT, argc-2, arrayAddress);
    array->arrayAddress = stringArray;

    //Preenchemos o array de strings com cada argumento
    for (int i = 2; i < argc; i++) {
        wchar_t* string = (wchar_t*)malloc((strlen(argv[i])+1)*sizeof(wchar_t));
        mbstowcs(string, argv[i], (strlen(argv[i]))+1);
        JavaString* string_info = newJavaString(string);
        stringArray[i-2] = (u4) string_info;
    }
    //Passamos o argumento argv da main java
    newFrame->localVariablesVector[0] = (u4) array;
}


//--------------------------------------------------------------------------------------------------
/*!
 * Metodo inicial do sistema
 *
 */
int main(int argc, const char * argv[]) {

    char opcoes;
    u1 debugFlags = 0;
    
    //Configuracoes de debug
    printf("Deseja ativar exibidor de .class?[N/s]:");
    scanf("%c", &opcoes);
    getchar();
    if (opcoes == 'S' || opcoes == 's') {
        debugFlags |= DEBUG_ShowClassFiles;
    }
    printf("Modo debug?[N/s]:");
    scanf("%c", &opcoes);
    getchar();
    if (opcoes == 'S' || opcoes == 's') {
        debugFlags |= DEBUG_DebugModus;
    }
    printf("Modo natalino?[N/s]:");
    scanf("%c", &opcoes);
    getchar();
    if (opcoes == 'S' || opcoes == 's') {
        debugFlags |= DEBUG_ShowBonus;
    }
    
    //Alocamos espaco para o ambiente de execucao
    Environment* environment = (Environment*) malloc(sizeof(Environment));
    
    //Criamos a area de metodos e a thread e as associamos ao enviroment
    environment->methodArea = newMethodArea();
    environment->thread = newThread();
    environment->debugFlags = debugFlags;
    
    //Empilhamos o metodo main
    configureClassMain(environment, argc, argv);
    
    //Passamos o ambiente de execucao para o interpretador
    execute(environment);
    
    if (environment->debugFlags & DEBUG_ShowBonus) {
        printf("\n\n\n_____________________");
        printf("\n*   *         *    * ");
        printf("\n  *   /\\ *     *  ");
        printf("\n     /  \\   *      *");
        printf("\n *  /    \\     ");
        printf("\n   /      \\   *  *");
        printf("\n * /      \\    ");
        printf("\n* /        \\ *     *");
        printf("\n  /        \\    *");
        printf("\n /          \\ * ");
        printf("\n/____________\\     *");
        printf("\n     |   |   _v_ * ");
        printf("\n     |___|  |_|_|   *");
        printf("\n_____________________");
        printf("\n    Feliz Natal!");
        printf("\n_____________________");
    }
    printf("\n\n");
    return 0;
}
