#define TAM_STR_NOME 			30
#define TAM_STR_DATA_NASC		11
#define TAM_STR_TEL				30
#define TAM_STR_EMAIL			30
#define PORCENTAGEM_SEMELHANCA 0.05

typedef struct contato Contato;
struct contato
{
    char	nome[TAM_STR_NOME]				;
    char    telefone[TAM_STR_TEL]			;
    char    data_nasc[TAM_STR_DATA_NASC]	;
    char 	email[TAM_STR_EMAIL]			;
    int 	id								;
};

extern Contato *lista_contatos  ;
extern int     tam_lista_cont   ;

void 	carregar_lista();
void 	salvar_lista_cont();   
void 	cadastrar_contato()	;
void 	mostrar_contatos(int *vect, char *nome_menu);
void 	mostrar_todos_contatos();
void 	pesquisar_contato();
void 	editar_contato(int id);
int 	*busca_lista_cont_semelhantes(char *nome_buscado, int *encontrado);
int 	busca_id_lista_cont_principal(int id);
char 	*str_dados_contato(char *str, int tamanho_str, Contato contato);
double 	compara_nome(char *nome_1, char *nome_2);
int 	gerar_id();
void 	limpar_str(char *str, int tamanho);
void 	excluir_contato(int indice);
void    free_lista_cont();
