int existe_tabela(char *nome_tb);
int arquivar_tabela(Tabela *tb);
Tabela *carregar_tabela(char *nome_tb);
Tabela *alocar_tabela(unsigned int qte_at, unsigned int qte_reg);
void free_tabela(Tabela *tb);