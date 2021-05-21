#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX_TAM 100
#define TEL_MAX_TAM 15

#define true 0
#define false -1

/**
 * A organização dos contatos será feita através
 * da estrutura de dados Lista com implementção dinâmica
*/
typedef struct {
    char nome[NOME_MAX_TAM];
    char numero_de_telefone[TEL_MAX_TAM];
} CONTATO;

typedef struct aux {
    CONTATO contato;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
    PONT inicio;
} LISTA_DE_CONTATOS;

void LCONTATO_inicializarLista(LISTA_DE_CONTATOS* l){
    l->inicio = NULL;
}

int LCONTATO_tamanho(LISTA_DE_CONTATOS* l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam;
}

void LCONTATO_exibirLista(LISTA_DE_CONTATOS* l){
    PONT end = l->inicio;
    printf("Lista: \n");
    while (end != NULL) {
        printf("%s %s\n", end->contato.nome, end->contato.numero_de_telefone);
        end = end->prox;
    }
}

//Função de procura por um nome específico
PONT LCONTATO_buscaSequencial(LISTA_DE_CONTATOS* l, char *nome) {
    PONT pos = l->inicio;
    while (pos != NULL) {
        if (strcmp(pos->contato.nome,nome) == 0) return pos;
        pos = pos->prox;
    }
    return NULL;
}

int LCONTATO_atualizaContato(LISTA_DE_CONTATOS* l, CONTATO contato) {
    //Procura pelo nome do elemento
    PONT elem = LCONTATO_buscaSequencial(l,contato.nome);
    if(elem == NULL) return false;

    //Atualiza o elemento
    strcpy(elem->contato.numero_de_telefone,contato.numero_de_telefone);

    return true;
}

PONT LCONTATO_buscaSequencialExc(LISTA_DE_CONTATOS* l, char *nome, PONT* ant){
    *ant = NULL;
    PONT atual = l->inicio;
    
    /**
     * Dinâmica de organização por 
     * ordem alfabética
    */
    while ((atual != NULL) && (strcmp(atual->contato.nome,nome) < 0)) {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (strcmp(atual->contato.nome,nome) == 0)) return atual;
    return NULL;
}

int LCONTATO_inserirElemListaOrd(LISTA_DE_CONTATOS* l, CONTATO contato) {
    char nome[NOME_MAX_TAM];
    //copiar o nome passado como parametro
    //para uma variavel de controle
    strcpy(nome,contato.nome);
    PONT ant, i;
    i = LCONTATO_buscaSequencialExc(l,nome,&ant);
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

int LCONTATO_excluirElemLista(LISTA_DE_CONTATOS* l, char *nome) {
    PONT ant, i;
    i = LCONTATO_buscaSequencialExc(l,nome,&ant);
    if (i == NULL) return false;
    if (ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;
    free(i);
    return true;
}