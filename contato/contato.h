#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX_TAM 30
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

typedef struct aux_C {
    CONTATO contato;
    struct aux_C *prox;
} ELEMENTO_C;

typedef ELEMENTO_C *PONT_C;

typedef struct {
    PONT_C inicio;
} LISTA_DE_CONTATOS;

//Lista
void LCONTATO_inicializarLista(LISTA_DE_CONTATOS* l){
    l->inicio = NULL;
}

int LCONTATO_tamanho(LISTA_DE_CONTATOS* l) {
    PONT_C end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam;
}

void LCONTATO_exibirLista(LISTA_DE_CONTATOS* l){
    PONT_C end = l->inicio;
    printf("    +-------------------------------+-----------+\n");
    printf("    | Nome                          | Telefone  |\n");
    printf("    +-------------------------------+-----------+\n");


    while (end != NULL) {

        //Nome
        if(strlen(end->contato.nome) == 1) {
            printf("    | %s                             |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 2) {
            printf("    | %s                            |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 3) {
            printf("    | %s                           |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 4) {
            printf("    | %s                          |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 5) {
            printf("    | %s                         |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 6) {
            printf("    | %s                        |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 7) {
            printf("    | %s                       |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 8) {
            printf("    | %s                      |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 9) {
            printf("    | %s                     |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 10) {
            printf("    | %s                    |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 11) {
            printf("    | %s                   |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 12) {
            printf("    | %s                  |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 13) {
            printf("    | %s                 |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 14) {
            printf("    | %s                |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 15) {
            printf("    | %s               |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 16) {
            printf("    | %s              |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 17) {
            printf("    | %s             |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 18) {
            printf("    | %s            |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 19) {
            printf("    | %s           |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 20) {
            printf("    | %s          |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 21) {
            printf("    | %s         |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 22) {
            printf("    | %s        |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 23) {
            printf("    | %s       |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 24) {
            printf("    | %s      |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 25) {
            printf("    | %s     |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 26) {
            printf("    | %s    |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 27) {
            printf("    | %s   |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 28) {
            printf("    | %s  |", end->contato.nome);
        } else if (strlen(end->contato.nome) == 29) {
            printf("    | %s |", end->contato.nome);
        }  else if (strlen(end->contato.nome) == 30) {
            printf("    | %s|", end->contato.nome);
        }

        //Telefone
        if(strlen(end->contato.numero_de_telefone) == 9) {
            printf(" %s |\n", end->contato.numero_de_telefone);
        } else if(strlen(end->contato.numero_de_telefone) == 8) {
            printf(" %s  |\n", end->contato.numero_de_telefone);
        }

        printf("    +-------------------------------+-----------+\n");
        end = end->prox;
    }
}

//Função de procura por um nome específico
PONT_C LCONTATO_buscaSequencial(LISTA_DE_CONTATOS* l, char *nome) {
    PONT_C pos = l->inicio;
    while (pos != NULL) {
        if (strcmp(pos->contato.nome,nome) == 0) return pos;
        pos = pos->prox;
    }
    return NULL;
}

int LCONTATO_atualizaContato(LISTA_DE_CONTATOS* l, CONTATO contato) {
    //Procura pelo nome do elemento
    PONT_C elem = LCONTATO_buscaSequencial(l,contato.nome);
    if(elem == NULL) return false;

    //Atualiza o elemento
    strcpy(elem->contato.numero_de_telefone,contato.numero_de_telefone);

    return true;
}

PONT_C LCONTATO_buscaSequencialExc(LISTA_DE_CONTATOS* l, char *nome, PONT_C* ant){
    *ant = NULL;
    PONT_C atual = l->inicio;
    
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
    PONT_C ant, i;
    i = LCONTATO_buscaSequencialExc(l,nome,&ant);
    if (i != NULL) return false;
    i = (PONT_C) malloc(sizeof(ELEMENTO_C));
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
    PONT_C ant, i;
    i = LCONTATO_buscaSequencialExc(l,nome,&ant);
    if (i == NULL) return false;
    if (ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;
    free(i);
    return true;
}

//MYSQL
void contatos_leituraDoBanco_construcaoDaLista(MYSQL *conexao, LISTA_DE_CONTATOS *l) {
    MYSQL_RES *result;
    MYSQL_ROW row;

    if(mysql_query(conexao, "SELECT * FROM contatos")) {
        mysql_error(conexao);
    }

    result = mysql_store_result(conexao);
    if(result == NULL) {
        mysql_error(conexao);
    }

    //Configuração da Lista de Contatos 
    LCONTATO_inicializarLista(l);

    //Contato auxiliar 
    CONTATO aux_C;

    while((row = mysql_fetch_row(result)) != NULL) {
        strcpy(aux_C.nome,row[0]);
        strcpy(aux_C.numero_de_telefone,row[1]);

        //Insere elemento da lsita ligada do programa
        LCONTATO_inserirElemListaOrd(l,aux_C);
    }

    mysql_free_result(result);
}

void contatos_insereNoBanco(MYSQL *conexao, char *nome, char * numero_de_telefone) {

    char query[100];
    sprintf(query, "INSERT INTO contatos(nome,tel) VALUES ('%s', '%s');", nome, numero_de_telefone);

    if(mysql_query(conexao,query)) {
        mysql_error(conexao);
    }
}

void contatos_atualizarContato(MYSQL *conexao, char *nome, char * numero_de_telefone) {

    char query[100];
    sprintf(query, "UPDATE contatos SET tel = '%s' WHERE nome = '%s';",numero_de_telefone, nome);

    if(mysql_query(conexao,query)) {
        mysql_error(conexao);
    }
}

void contatos_apagarDoBanco(MYSQL *conexao, char *nome) {
    
    char query[100];
    sprintf(query, "DELETE FROM contatos WHERE nome = '%s';", nome);

    if(mysql_query(conexao,query)) {
        
        mysql_error(conexao);
    }
}