#include <stdio.h>
#include <stdlib.h>

#define true 0
#define false -1

#define MAX_TEXT_SIZE 1000

//Implementação das tarefas com modelagem de um lista ligada

typedef int TIPOCHAVE;

typedef struct {
    char text[1000];
    TIPOCHAVE ch;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

/**
 * A estrutura padrão da lista foi modificada para atender
 * a organização das inserções de tarefas que serão inseridas
 * sempre no final da lista 
*/typedef struct {
    PONT inicio;
    PONT final;
} LISTA;


void inicializarLista(LISTA* l){
    l->inicio = NULL;
    l->final = NULL;
}

void reinicializarLista(LISTA* l) {
    PONT end = l->inicio;
    while (end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }

    l->inicio = NULL;
    l->final = NULL;
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
        printf("[%i] - %s \n",end->reg.ch, end->reg.text);
        end = end->prox;
    }
}

/**
 * Para o contexto dessa implementação os elementos serão 
 * inseridos sempre no fim da lista, por questão de organização.
 * Assim sempre receberão uma chave com o valor da chave de seu 
 * antecessor mais um 
*/int inserirElemListaOrd(LISTA* l, REGISTRO reg) {
    PONT elem;
    TIPOCHAVE ch;

    //Alocação de memória
    elem = (PONT) malloc(sizeof(ELEMENTO));
    elem->reg = reg;

    //inserção no final da lista
    if(l->final == NULL) {
        //inserção do primeiro elemento
        ch = 1;
        elem->reg.ch = ch;

        l->inicio = elem;
        l->final = elem;

        elem->prox = NULL;
    } else {
        //inserção padrão
        ch = (l->final->reg.ch) + 1; ////posivel erro
        elem->reg.ch = ch;

        l->final->prox = elem;
        l->final = elem;
        elem->prox = NULL;
    }

    return true;
}

PONT buscaSequencialExc(LISTA* l, TIPOCHAVE ch, PONT* ant){
    *ant = NULL;
    PONT atual = l->inicio;

    /**
     * Percorre a lista até se deparar com um elemento com
     * a chave maior ou igual a chave passada como parametro
    */while ((atual != NULL) && (atual->reg.ch<ch)) {
        *ant = atual;
        atual = atual->prox;
    }

    if ((atual != NULL) && (atual->reg.ch == ch)) return atual;

    return NULL;
}

void reenumeraChaves(PONT i) {
    PONT end = i->prox;

    while(end != NULL) {
        end->reg.ch-=1;

        end = end->prox;
    }
}

int excluirElemLista(LISTA* l, TIPOCHAVE ch) {
    PONT ant, i;
    i = buscaSequencialExc(l,ch,&ant);

    if (i == NULL) return false;
    if (ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;

    /**
     * Todos os elementos apartir do sucessor do elemento i
     * que será apagado terão que ter suas chaves reenumeradas
    */
    reenumeraChaves(i);

    free(i);

    return true;
}

