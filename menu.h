#define STRING_LENGTH 256

typedef struct menu Menu;
struct menu
{
    char **option_mat;
    int size;
};

Menu *addOption(Menu *menu, char *str)																										;
Menu *removeOption(Menu *menu, int option)																									;
Menu *menu_gen(int menu_size, ...)																											;
int getch()																																	;
int menu_mechanics(char *select_vect, char move, int selected_pos, int menu_size)															;
int show_menu(char* menu_title, Menu *menu, void (*func)(), int debug_mode)																	;
int menu_mechanics_rolagem(char move, void *vect_option, int option_index, int vect_option_len)												;
int show_menu_rolagem_int(char* menu_title, Menu *menu, int *vect_option, int vect_option_len, void (*func)(), int debug_mode, int two_dig)	;
int show_menu_rolagem_char(char* menu_title, Menu *menu, char **vect_option, int vect_option_len, void (*func)(), int debug_mode)			;
int pos_option(Menu *menu, char *str)																										;
void free_menu(Menu *menu)																													;