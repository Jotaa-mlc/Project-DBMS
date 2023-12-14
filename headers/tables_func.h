#include "definitions.h"
//Auxiliar Funtions
int try_again();
int checar_nome(char *nome);
int existe_id(unsigned int id, Tabela * tb);
int checar_tipo(char *tipo);
int existe_dupla_pk(Tabela *tb);
int nome_repetido(Tabela * tb, char * nome_at);
char * get_nome_tabela(int deve_existir);
int get_opcao_pesquisa();
double convert_at_double(int tipo_at, Atributo atri);
//Main Funtions
void criar_tabela();
void inserir_registro();
int remover_registro();
void remover_tabela();
void listar_tabelas();
void exibir_tabela();
void pesquisar_tabela();