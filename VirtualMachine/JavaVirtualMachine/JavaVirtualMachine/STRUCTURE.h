//
//  STRUCTURE.h
//  JavaVirtualMachine
//
//  Created by Gabriel Araujo Dantas on 19/11/15.
//  Copyright © 2015 Rondinele Prado. All rights reserved.
//

//#################################################################################################
/*! \file STRUCTURE.h
 *
 *  \brief Estruturas que serão utilizadas na JVM.
 *
 *  Arquivo com a definicao das estruturas, tipos e constantes associadas ao
 *  sistema.
 */
//##################################################################################################

/* 
 Seguindo nossa ideia de generalidade sempre que ha um ponteiro sem um tipo definido
 crio com o tipo void
 */

#ifndef STRUCTURE_h
#define STRUCTURE_h
#define STRING_LENGTH 100

//Estrutura para chamada da String sem a necessidade do char com tamanho limitado sugestao
typedef  char String[STRING_LENGTH];


//ClassTable mesmo sem a criacao do JavaClass
typedef struct ClassTable{
    String name;
    JavaClass *javaClass;
};

/*
 Abstracao da pilha para que ficasse mais simples a estrutura das outra
 Caso seja uma abstracao desnecessaria basta modificar as outras pilhas
 Criando os vetores com seus respectivos tipos
 */
typedef struct Stack{
    void *stk;
    void *top;
};

typedef struct OperandStack{
    Stack *operandStack;
    u4 *top;
};
/*
 Construcao da estrutura de Frame
 */
typedef struct Frame{
    JavaClass *javaClass;
    method_info *method_info;
    void *returnPC;
    u4 *localVariablesVector;
    OperandStack *opStk;
};

typedef struct VMStack{
    Frame *top;
    Stack *stack;
};
/*
 Construcao da estrutura Thread
 */
typedef struct Thread{
    void *PC;
    VMStack *vmStack;
};


#endif /* STRUCTURE_h */
