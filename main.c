#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> // compilar gcc -o main main.c $(mysql_config --libs)
#include "./contato/contato.h"

#define ACTION_SIZE 10

MYSQL* obterConexao() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "projeto";
    char *password = "aIPAa89AKS23qda!asd";
    char *database = "agenda_dados";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
        return 0;
    } else {
        printf("Conexão realizada\n");
        return conn;
    }
};

int main(void) {

    char action[ACTION_SIZE];

    MYSQL *conexao = obterConexao();

    /*system("clear");
    printf("\n                        ");
    printf("###### Agenda Pessoal #######\n\n");
    printf("                        ");
    printf("-Contatos (c)\n\n");
    printf("                        ");
    printf("-Tarefas (t)\n\n");
    

    for(;;) {

        //Leitura de ação
        printf("                        ");
        printf("-> ");
        scanf(" %[^\n]s", action);
        //

        if(strcmp(action,"c") == 0) {
            //Lista de Contatos 

            system("clear");
            printf("\n                        ");
            printf("###### Agenda Pessoal #######\n");
            printf("                        ");
            printf("###### Lista de Contatos ####\n\n");
            printf("                        ");
            printf("Para ver todos os contatos registrados digite (show)\n\n");
            printf("                        ");
            printf("Para adicionar um novo contato digite (add)\n\n");
            printf("                        ");
            printf("Para apagar um contato existente digite (remove)\n\n");

            //Leitura de ação
            printf("                        ");
            printf("-> ");
            scanf(" %[^\n]s", action);
            //

            if(strcmp(action,"show") == 0) {
                
            } else if(strcmp(action,"add") == 0) {

            } else if(strcmp(action,"remove") == 0) {

            }

        } else if(strcmp(action,"t") == 0) {

        } else break;
    }*/

    return 0;
}