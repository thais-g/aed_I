#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> // compilar gcc -o main main.c $(mysql_config --libs)
#include "./contato/contato.h"
#include "contato/contato_mysql.h"
#include "anotacao.h"

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
}

#define ACTION_SIZE 10

int main(void) {

    char action[ACTION_SIZE];

    MYSQL *conexao = obterConexao();

    system("clear");
    printf("    ###### Agenda Pessoal #######\n");
    for(;;) {

        printf("\n    -Contatos (c)\n\n");
        printf("    -Tarefas (t)\n\n");
        printf("    -Diario (d)\n\n")/

        //Leitura de ação
        printf("    > ");
        scanf(" %[^\n]s", action);
        //

        if(strcmp(action,"c") == 0) {
            //Lista de Contatos 

            //Puxar dados do banco
            LISTA_DE_CONTATOS lista_de_contatos;
            contatos_leituraDoBanco_construcaoDaLista(conexao,&lista_de_contatos);
            //---//
            
            //Contato auxiliar 
            CONTATO aux;
            //---//

            system("clear");
            printf("    ###### Agenda Pessoal #######\n");

            printf("\n    (Contatos)\n\n");
            
            printf("    -Para ver todos os contatos registrados digite (show)\n\n");
            printf("    -Para adicionar um novo contato digite (add)\n\n");
            printf("    -Para apagar um contato existente digite (remove)\n\n");
            printf("    -Para atualizar um contato existente digite (update)\n\n");

            //Leitura de ação
            printf("    > ");
            scanf(" %[^\n]s", action);
            //

            if(strcmp(action,"show") == 0) {
                system("clear");
                printf("    ###### Agenda Pessoal #######\n");

                printf("\n    (Contatos)\n\n");

                LCONTATO_exibirLista(&lista_de_contatos);

            } else if(strcmp(action,"add") == 0) {

                printf("\n    Me informe o nome do novo contato: ");
                scanf(" %[^\n]s", aux.nome);
                printf("\n    Me informe o numero do novo contato: ");
                scanf(" %[^\n]s", aux.numero_de_telefone);

                //Inserir na lista do programa
                LCONTATO_inserirElemListaOrd(&lista_de_contatos,aux);
                //Inserir no banco de dados
                contatos_insereNoBanco(conexao,aux.nome,aux.numero_de_telefone);
                system("clear");
                printf("    ###### Agenda Pessoal #######\n");

            } else if(strcmp(action,"remove") == 0) {

                printf("\n    Me informe o nome do contato que será removido: ");
                scanf(" %[^\n]s", aux.nome);

                //Remove da lista do programa
                LCONTATO_excluirElemLista(&lista_de_contatos,aux.nome);
                //Remover do banco de dados 
                contatos_apagarDoBanco(conexao,aux.nome);
                system("clear");
                printf("    ###### Agenda Pessoal #######\n");

            } else if(strcmp(action,"update") == 0) {

                printf("\n    Me informe o nome do contato que será atualizado: ");
                scanf(" %[^\n]s", aux.nome);
                printf("\n    Me informe o novo numero do contato: ");
                scanf(" %[^\n]s", aux.numero_de_telefone);

                //Atualiza o elemento da lista 
                LCONTATO_atualizaContato(&lista_de_contatos,aux);
                //Atualiz o registro do banco
                contatos_atualizarContato(conexao,aux.nome,aux.numero_de_telefone);
                system("clear");
                printf("    ###### Agenda Pessoal #######\n");

            }

        } else if(strcmp(action,"t") == 0) {

        } else if(strcmp(action, "d") == 0)
        {
            diario_func();
        }
        
         else break;
    }

    return 0;
}