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
#include "../../include/ClassLoader/I_CLASSLOADER.h"
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

    //Separamos o path do diretorio raiz do nome da classe
    int pathLen = 0;
    char* path = (char*) malloc((strlen(argv[1]) +1) * sizeof(char));
    strcpy(path, argv[1]);
    
    for (int i = 0; i < strlen(path); i++)
        if (path[i] == '/' || path[i] == '\\') pathLen = i+1;
    
    path[pathLen] = '\0';
    argv[1] = & argv[1][pathLen];
    environment->path = path;
    
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
    
    //!Apresentamos e configuramos as opcoes de debug
    printf("Executar (1) JVM ou (2) exibidor de .class?[1/2]:");
    scanf("%c", &opcoes);
    getchar();
    if (opcoes == '2') {
        JavaClass* javaClass = loadCLass(argv[1], NULL);
        free(javaClass);
        return 0;
    }
    printf("Modo debug?[N/s]:");
    scanf("%c", &opcoes);
    getchar();
    if (opcoes == 'S' || opcoes == 's') {
        debugFlags |= DEBUG_DebugModus;
    }
    
    //!Alocamos espaco para o ambiente de execucao
    Environment* environment = (Environment*) malloc(sizeof(Environment));
    
    //!Criamos a area de metodos e a thread e as associamos ao enviroment
    environment->methodArea = newMethodArea();
    environment->thread = newThread();
    environment->debugFlags = debugFlags;
    
    //!Empilhamos o metodo main da classe passada como argumento
    configureClassMain(environment, argc, argv);
    
    //!Passamos o ambiente de execucao para o interpretador
    execute(environment);

    printf("\n\n");
    return 0;
}
