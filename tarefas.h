#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h> // compilar gcc -o main main.c $(mysql_config --libs)

#define true 0
#define false -1

#define MAX_TEXT_SIZE 1000

//Implementação das tarefas com modelagem de um lista ligada

typedef int TIPOCHAVE;

typedef struct {
    char text[1000];
    TIPOCHAVE ch;
} TAREFA;

typedef struct aux_T {
    TAREFA reg;
    struct aux_T *prox;
} ELEMENTO_T;

typedef ELEMENTO_T* PONT_T;

/**
 * A estrutura padrão da lista foi modificada para atender
 * a organização das inserções de tarefas que serão inseridas
 * sempre no final da lista 
*/typedef struct {
    PONT_T inicio;
    PONT_T final;
} LISTA_DE_TAREFAS;

//LISTA
void TAREFAS_inicializarLista(LISTA_DE_TAREFAS* l){
    l->inicio = NULL;
    l->final = NULL;
}

void TAREFAS_reinicializarLista(LISTA_DE_TAREFAS* l) {
    PONT_T end = l->inicio;
    while (end != NULL) {
        PONT_T apagar = end;
        end = end->prox;
        free(apagar);
    }

    l->inicio = NULL;
    l->final = NULL;
}

int TAREFAS_tamanho(LISTA_DE_TAREFAS* l) {
    PONT_T end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam;
}

void TAREFAS_exibirLista(LISTA_DE_TAREFAS* l){
    PONT_T end = l->inicio;


    while (end != NULL) {
        printf("    [%i] - %s \n",end->reg.ch, end->reg.text);
        end = end->prox;
    }
}

/**
 * Para o contexto dessa implementação os elementos serão 
 * inseridos sempre no fim da lista, por questão de organização.
 * Assim sempre receberão uma chave com o valor da chave de seu 
 * antecessor mais um 
*/int TAREFAS_inserirElemListaOrd(LISTA_DE_TAREFAS* l, TAREFA reg) {
    PONT_T elem;
    TIPOCHAVE ch;

    //Alocação de memória
    elem = (PONT_T) malloc(sizeof(ELEMENTO_T));
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
        ch = (l->final->reg.ch) + 1;
        elem->reg.ch = ch;

        l->final->prox = elem;
        l->final = elem;
        elem->prox = NULL;
    }

    return ch;
}

PONT_T TAREFAS_buscaSequencialExc(LISTA_DE_TAREFAS* l, TIPOCHAVE ch, PONT_T* ant){
    *ant = NULL;
    PONT_T atual = l->inicio;

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

//MYSQL
void tarefas_atualizaBanco(MYSQL *conexao, int chave) {

    char query[100];
    sprintf(query, "UPDATE tarefas SET chave = '%i' WHERE chave = '%i';", chave-1, chave);

    if(mysql_query(conexao,query)) {
        
        mysql_error(conexao);
    }
}
//

void TAREFAS_reenumeraChaves(MYSQL *conexao,PONT_T i) {
    PONT_T end = i->prox;

    while(end != NULL) {
        //Atualizar o dado no banco
        tarefas_atualizaBanco(conexao,end->reg.ch);

        end->reg.ch-=1;

        end = end->prox;
    }
}

int TAREFAS_excluirElemLista(MYSQL *conexao,LISTA_DE_TAREFAS* l, TIPOCHAVE ch) {
    PONT_T ant, i;
    i = TAREFAS_buscaSequencialExc(l,ch,&ant);

    if (i == NULL) return false;
    if (ant == NULL) l->inicio = i->prox;
    else ant->prox = i->prox;

    /**
     * Todos os elementos apartir do sucessor do elemento i
     * que será apagado terão que ter suas chaves reenumeradas
    */
    TAREFAS_reenumeraChaves(conexao,i);

    free(i);

    return true;
}

//MYSQL
void tarefas_leituraDoBanco_construcaoDaLista(MYSQL *conexao, LISTA_DE_TAREFAS *l) {
    MYSQL_RES *result;
    MYSQL_ROW row;

    if(mysql_query(conexao, "SELECT * FROM tarefas")) {
        mysql_error(conexao);
    }

    result = mysql_store_result(conexao);
    if(result == NULL) {
        mysql_error(conexao);
    }

    //Configuração da Lista de tarefas
    TAREFAS_inicializarLista(l);

    //Contato auxiliar 
    TAREFA aux_T;

    while((row = mysql_fetch_row(result)) != NULL) {
        strcpy(aux_T.text,row[0]);
        aux_T.ch = atoi(row[1]);

        //Insere elemento da lsita ligada do programa
        TAREFAS_inserirElemListaOrd(l,aux_T);
    }

    mysql_free_result(result);
}

void tarefas_insereNoBanco(MYSQL *conexao, char *texto, int chave) {

    char query[100];
    sprintf(query, "INSERT INTO tarefas(texto,chave) VALUES ('%s', '%i');", texto, chave);

    if(mysql_query(conexao,query)) {
        mysql_error(conexao);
    }
}

void tarefas_apagarDoBanco(MYSQL *conexao, int chave) {
    
    char query[100];
    sprintf(query, "DELETE FROM tarefas WHERE chave = '%i';", chave);

    if(mysql_query(conexao,query)) {
        
        mysql_error(conexao);
    }
}