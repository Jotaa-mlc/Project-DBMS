#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
 
#include "headers/definitions.h"

extern char sep[];
extern char file_extension[];
extern char tables_folder_path[];
extern char tables_config[];

/**
 * Recebe o nome da tabela e o modo de abertura;
 * @return ptr para o arquivo OU NULL em caso de erro;
*/
FILE * load_tb_file(char *nome_tb, char *open_mode)
{
    char table_path[MAX_NAME_LENGTH] = {0};
    strcpy(table_path, tables_folder_path);
    strcat(table_path, nome_tb);
    strcat(table_path, file_extension);

    FILE * tb_file = fopen(table_path, open_mode);

    if (tb_file == NULL)
    {
        printf("ERRO: não foi possível abrir o arquivo da tabela %s\n", nome_tb);
        printf("ERRO: %s\n", strerror(errno));
        return NULL;
    }
    else
    {
        return tb_file;
    }
}

/**
 * Carrega o arquivo tables.config
 * @return ptr para o arquivo OU NULL em caso de erro
*/
FILE * load_tb_config(char *open_mode)
{
    FILE * tb_config;
    tb_config = fopen(tables_config, open_mode);
    if (tb_config == NULL)
    {
        printf("ERRO: não foi possível abrir um arquivo essencial para o programa\nCaminho para o arquivo: tables/tables.config\n");
        printf("ERRO: %s\n", strerror(errno));
        return NULL;
    }
    else
    {
        return tb_config;
    }
}

/**
 * Atualiza o arquivo tables.config baseado na tabela passada
 * @param excluir_tb (0 || 1)
*/
void update_tables_config(Tabela *tb, int excluir_tb)
{
    char path_new_tb_config[MAX_NAME_LENGTH];
    strcpy(path_new_tb_config, tables_folder_path);
    strcat(path_new_tb_config, "tables.config.temp");

    FILE * tb_config = load_tb_config("r");
    FILE * new_tb_config = fopen(path_new_tb_config, "w");

    char nome_tb_lida[MAX_NAME_LENGTH] = {0};
    char linha[MAX_NAME_LENGTH] = {0};

    while (fscanf(tb_config, "%s\n", linha) != EOF)
    {
        strcpy(nome_tb_lida, linha);
        strtok(nome_tb_lida, sep);
        if (!(strcmp(tb->nome_tb, nome_tb_lida) == 0)) 
        {
            fprintf(new_tb_config, "%s\n", linha);
        }
    }
    
    if (!excluir_tb)
    {
        fprintf(new_tb_config, "%s%s%i%s%i%s\n", tb->nome_tb, sep, tb->qte_at, sep, tb->qte_reg, sep);
    }
    
    fclose(new_tb_config);
    fclose(tb_config);

    remove(tables_config);
    rename(path_new_tb_config, tables_config);
}

int existe_tabela(char *nome_tb)
{
    int existe = 0;
    FILE * tb_config;
    tb_config = load_tb_config("r");
        char nome_tb_lida[MAX_NAME_LENGTH] = {0};
        while (fscanf(tb_config, "%s\n", nome_tb_lida) != EOF)
        {
            strtok(nome_tb_lida, sep);
            existe = (strcmp(nome_tb, nome_tb_lida) == 0) ? 1 : existe;
        }

    fclose(tb_config);
    return existe;   
}

Tabela * alocar_tabela(unsigned int qte_at, unsigned int qte_reg)
{   
    Tabela * tb;
    tb = calloc(1, sizeof(Tabela));
    tb->qte_at = qte_at;
    tb->qte_reg = qte_reg;
    tb->nome_tb = calloc(MAX_NAME_LENGTH, sizeof(char));
    tb->nome_pk = calloc(MAX_NAME_LENGTH, sizeof(char));
    tb->nomes_at = calloc(qte_at, sizeof(char *));
    for (unsigned int i = 0; i < qte_at; i++) tb->nomes_at[i] = calloc(MAX_NAME_LENGTH, sizeof(char));
    tb->tipos_at = calloc(qte_at, sizeof(int));

    tb->registros = calloc(qte_reg, sizeof(Registro));
    for(unsigned int i = 0; i < qte_reg; i++) tb->registros[i].at = calloc(qte_at, sizeof(Atributo));

    return tb;
}

void free_tabela(Tabela *tb)
{
    free(tb->nome_tb);
    free(tb->nome_pk);
    for (unsigned int i = 0; i < tb->qte_at; i++) free(tb->nomes_at[i]);
    free(tb->nomes_at);
    for (unsigned int i = 0; i < tb->qte_reg; i++) free(tb->registros[i].at);    
    free(tb->tipos_at);
    free(tb->registros);
    free(tb);
}