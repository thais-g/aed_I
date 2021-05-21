#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h> // compilar gcc -o main main.c $(mysql_config --libs)

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
    CONTATO aux;

    while((row = mysql_fetch_row(result)) != NULL) {
        strcpy(aux.nome,row[0]);
        strcpy(aux.numero_de_telefone,row[1]);

        //Insere elemento da lsita ligada do programa
        LCONTATO_inserirElemListaOrd(l,aux);
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