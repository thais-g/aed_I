#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefas.h"

int main(void) {
    LISTA tarefas;
    inicializarLista(&tarefas);

    //REGISTRO auxiliar
    REGISTRO aux;

    //Inserções manuais para teste
    strcpy(aux.text,"Passear com o cachorro");
    inserirElemListaOrd(&tarefas,aux);
    //
    strcpy(aux.text,"Comprar pão no mercado");
    inserirElemListaOrd(&tarefas,aux);
    //
    strcpy(aux.text,"Terminar de ler um livro");
    inserirElemListaOrd(&tarefas,aux);

    //Exclusões manuais para teste
    excluirElemLista(&tarefas,3);

    exibirLista(&tarefas);

    return 0;
}