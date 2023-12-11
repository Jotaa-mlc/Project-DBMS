#include "definitions.h"
//Auxiliar Funtions
int try_again();
int checar_nome(char *nome);
int existe_id(unsigned int id, Tabela * tb);
int checar_tipo(char *tipo);
int existe_dupla_pk(Tabela *tb);
char * get_nome_tabela(int deve_existir);
//Main Funtions
int criar_tabela();
void inserir_registro();
int remover_registro();
void remover_tabela();
void listar_tabelas();
void exibir_tabela();