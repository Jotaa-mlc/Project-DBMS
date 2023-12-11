//Auxiliar functions
FILE * load_tb_file(char *nome_tb, char *open_mode);
FILE * load_tb_config(char *open_mode);
void update_tables_config(Tabela *tb, int excluir_tb);
int existe_tabela(char *nome_tb);
Tabela * alocar_tabela(unsigned int qte_at, unsigned int qte_reg);
void free_tabela(Tabela *tb);
//Main Functions
int arquivar_tabela(Tabela *tb);
Tabela * carregar_tabela(char *nome_tb);
void remover_arq_tb(Tabela * tb);