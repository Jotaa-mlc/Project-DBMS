#include "definitions.h"
//Auxiliar Funtions
/**
 * Pergunta ao user "tentar novamente?"
 * @return 0: Cancelar operação; 1: Tentar novamente;
*/
int try_again();
/**
 * Confere se o nome está válido, i.e.
 * Não contém o [sep]
 * 
 * @return 2: sucesso; 1: repetir processo; 0: cancelar operação;
*/
int checar_nome(char *nome);
/**
 * Confere se a Chave_Primária já está em uso nos registros da tabela
 * @param id Chave_Primária a ser conferida;
 * @param tb Tabela a ser consultada;
 * @return 0: Não existe; 1: Existe;
*/
int existe_id(unsigned int id, Tabela * tb);
/**
 * confere a entrada do tipo do atributo
 * 
 * @return 0: Cancelar; 1: Tentar novamente; [2: int, 3: float, 4: double, 5: char, 6: string]
*/
int checar_tipo(char *tipo);
/**
 * Confere se nome_at já existe na lista de nomes dos atributos
 * @param tb Tabela que será conferida;
 * @param nome_at Nome checado;
 * @return 0: NÃO é repetido; 1: Repetido;
*/
int nome_repetido(Tabela * tb, char * nome_at);
/**
 * Recebe um nome de uma tabela do usuário, realiza os testes necessários considerando
 * se a tabela deve existir ou não (0, 1)
 * @return String: informada pelo usuário; NULL: usuário cancelou a operação;
*/
char * get_nome_tabela(int deve_existir);
/**
 * Recebe do usuário um registro para determinada tabela
 * @param qte_at Quantidade de atributos;
 * @param tipos_at Lista (int) com os tipos de atributos;
*/
Registro * get_registro(unsigned int qte_at, int * tipos_at);
/**
 * Recebe do usuário a opção de pesquisa
 * @return 0: >; 1: >=; 2: =; 3: <; 4: <=; 5: +/-;
*/
int get_opcao_pesquisa();
/**
 * Converte qualquer tipo de atributo (Exceto string) em double
 * @param tipo_at Indicativo do tipo de atributo;
 * @param atri Atributo a ser convertido;
*/
double convert_at_double(int tipo_at, Atributo atri);
/**
 * Exibe PK e todos os atributos de um registro
 * @param reg Registro a ser exibido;
 * @param qte_at Quantidade de atributos do registro;
 * @param lista Lista com os tipos dos atributos do registro;
*/
void print_registro(Registro reg, unsigned int qte_at, int * tipos_at);


//Main Funtions
void criar_tabela();
void inserir_registro();
void remover_registro();
void remover_tabela();
void listar_tabelas();
void exibir_tabela();
void pesquisar_tabela();