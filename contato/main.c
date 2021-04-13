#include <stdio.h>
#include <stdlib.h>
#include "contato.h"

int main(void)
{
    LISTA contatos;
    inicializarLista(&contatos);

    //Contato auxiliar
    CONTATO aux;

    //Inserções manuais
        strcpy(aux.nome,"João");
        strcpy(aux.numero_de_telefone,"99987-9067");
        inserirElemListaOrd(&contatos,aux);

        strcpy(aux.nome,"Acanda");
        strcpy(aux.numero_de_telefone,"67584-7823");
        inserirElemListaOrd(&contatos,aux);

        strcpy(aux.nome,"Abanda");
        strcpy(aux.numero_de_telefone,"98787-5262");
        inserirElemListaOrd(&contatos,aux);

        strcpy(aux.nome,"Caio");
        strcpy(aux.numero_de_telefone,"97745-3726");
        inserirElemListaOrd(&contatos,aux);
    //

    //Exclusões manuais
        excluirElemLista(&contatos,"Acanda");
    //
    

    exibirLista(&contatos);

    return 0;
}