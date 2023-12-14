//Auxiliar functions

/**
 * Carregar um arquivo de uma tabela:
 * @param nome_tb Nome da tabela a ser carregada;
 * @param open_mode Parametro do modo de abertura do arquivo (fopen);
 * @return Ponteiro para o arquivo da tabela [nome_tb]; NULL: em caso de erro;
*/
FILE * load_tb_file(char *nome_tb, char *open_mode);
/**
 * Carrega o arquivo tables.config
 * @param open_mode Parametro do modo de abertura do arquivo (fopen);
 * @return Ponteiro para o arquivo tables.config; NULL: em caso de erro;
*/
FILE * load_tb_config(char *open_mode);
/**
 * Atualiza o arquivo tables.config
 * @param tb Tabela cuja info será atualizada;
 * @param excluir_tb parametro se a planilha deve ou não ser excluida (0||1);
*/
void update_tables_config(Tabela *tb, int excluir_tb);
/**
 * Checa se existe uma tabela com determinado nome
 * @param nome_tb Nome a ser conferido;
 * @return 0: NÃO existe; 1: Existe;
*/
int existe_tabela(char *nome_tb);
/**
 * Aloca memória para todos os atributos de uma tabela com:
 * @param qte_at Quantidade de atributos a serem alocados;
 * @param qte_reg Quantidade de registros a serem alocados;
 * @return Ponteiro de uma tabela vazia;
*/
Tabela * alocar_tabela(unsigned int qte_at, unsigned int qte_reg);
/**
 * Libera toda a memória alocada pela Tabela
 * @param tb Tabela a ser liberada da memória;
*/
void free_tabela(Tabela *tb);


//Main Functions


/**
 * Cria/Atualiza o arquivo de uma Tabela
 * @param tb Tabela a ser arquivada;
*/
int arquivar_tabela(Tabela *tb);
/**
 * Carrega uma Tabela de um arquivo
 * @param nome_tb Nome da tabela a ser carregada;
 * @return Ponteiro para a Tabela especificada;
*/
Tabela * carregar_tabela(char *nome_tb);
/**
 * Remove o arquivo da tabela e atualiza tables.config
 * @param tb Tabela a ser removida;
*/
void remover_arq_tb(Tabela * tb);