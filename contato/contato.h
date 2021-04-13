#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX_TAM 50

#define true 0
#define false -1

/**
 * A organização dos contatos será feita através
 * da estrutura de dados Lista com implementção dinâmica
*/
typedef struct {
    char nome[NOME_MAX_TAM];
    char numero_de_telefone[11];
} CONTATO;

typedef struct aux {
    CONTATO contato;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
    PONT inicio;
} LISTA;

void inicializarLista(LISTA* l){
    l->inicio = NULL;
}

int tamanho(LISTA* l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam;
}

void exibirLista(LISTA* l){
    PONT end = l->inicio;
    printf("Lista: \n");
    while (end != NULL) {
        printf("%s %s\n", end->contato.nome, end->contato.numero_de_telefone);
        end = end->prox;
    }
}

//Função de procura por um nome específico
PONT buscaSequencial(LISTA* l, char *nome) {
    PONT pos = l->inicio;
    while (pos != NULL) {
        if (strcmp(pos->contato.nome,nome) == 0) return pos;
        pos = pos->prox;
    }
    return NULL;
}

PONT buscaSequencialExc(LISTA* l, char *nome, PONT* ant){
    *ant = NULL;
    PONT atual = l->inicio;
    /**
     * Organização por chaves crescentes
     * A dinâmica precisa ser mudada pra organização em ordem 
     * alfabética
    */
    while ((atual != NULL) && (strcmp(atual->contato.nome,nome) < 0)) {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (strcmp(atual->contato.nome,nome) == 0)) return atual;
    return NULL;
}

int inserirElemListaOrd(LISTA* l, CONTATO contato) {
    char nome[NOME_MAX_TAM];
    //copiar o nome passado como parametro
    //para uma variavel de controle
    strcpy(nome,contato.nome);
    PONT ant, i;
    i = buscaSequencialExc(l,nome,&ant);
    if (i != NULL) return false;
    i = (PONT) malloc(sizeof(ELEMENTO));
    i->contato = contato;
    if (ant == NULL) {
        i->prox = l->inicio;
        l->inicio = i;
    } else {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}

int excluirElemLista(LISTA* l, char *nome) {
    PONT ant, i;
    i = buscaSequencialExc(l,nome,&ant);
    if (i == NULL) return false;
    if (ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;
    free(i);
    return true;
}