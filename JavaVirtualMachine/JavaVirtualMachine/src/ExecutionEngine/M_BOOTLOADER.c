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
#include "../../include/Estruturas/E_JVM.h"
#include "../../include/MemoryUnit/I_MEMORYUNIT.h"
#include "../../include/ClassLoader/I_LECLASS.h"
#include "../../include/ExecutionEngine/I_INTERPRETER.h"

int main(int argc, const char * argv[]) {

    //Alocamos espaco para o ambiente de execucao
    Environment* environment = (Environment*) malloc(sizeof(Environment));
    
    //Criamos a area de metodos e a thread e as associamos ao enviroment
    environment->methodArea = newMethodArea();
    environment->thread = newThread();
    
    //Empilhamos o metodo main a ser inicializado
    pushFrame(environment, argv[1], "main", "([Ljava/lang/String;)V");
    
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
