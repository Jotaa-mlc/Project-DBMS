#include <stdio.h>
#include <errno.h>
#include <string.h>
 
#include "headers/definitions.h"
#include "headers/tables_func.h"

char tables_config[] = "tables/tables.config";

/**
 * Confere no arquivo tables/tables.config se a tabela já existe
 * 
 * @return -1: ERRO fopen(); 0 || 1: try_again(); 2: Tabela NÃO existe;
*/
int existe_tabela(char *nome_tb)
{
    FILE * tb_config;
    tb_config = fopen(tables_config, "r");
    if (tb_config == NULL)
    {
        printf("ERRO: não foi possível abrir um arquivo essencial para o programa\nCaminho para o arquivo: tables/tables.config\n");
        printf("ERRO: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        char nome_tb_lida[MAX_NAME_LENGTH] = {0};
        char str_formatada[] = "%%s";
        strcat(str_formatada, sep);
        while (tb_config != EOF)
        {
            fscanf(tb_config, str_formatada, nome_tb_lida);
            if (strcmp(nome_tb, nome_tb_lida) == 0)
            {
                printf("A tabela já existe!\n");
                return try_again();
            }
        }

        return 2;   
    }
}

/**
 * Cria/sobreescreve o arquivo da tabela indicada
 * 
 * @return 2: sucesso; -1: erro ao abrir o arquivo;
*/
int arquivar_tabela(Tabela tb)
{
    char table_path[MAX_NAME_LENGTH+15] = "tables/";
    strcat(tb.nome_tb, ".itp");
    strcat(table_path, tb.nome_tb);

    FILE * tb_file;
    tb_file = fopen(table_path, "w");

    if (tb_file != NULL)
    {
        fprintf(tb_file,"id%s", sep);

        for (int i = 0; i < tb.qte_at; i++)//insere os atributos no cabeçalho do arquivo
        {
            fprintf(tb_file,"%s%s", tb.nomes_at[i], sep);
        }
        fprintf(tb_file,"\n");
        
        for (int i = 0; i < tb.qte_reg; i++)//insere os registros
        {
            fprintf(tb_file,"%u%s", tb.registros[i].id, sep);
            for (int i = 0; i < tb.qte_at; i++)
            {
                switch (tb.tipos_at[i])
                {
                    case 0:
                        fprintf(tb_file,"%d%s", tb.registros[i].at->inteiro, sep);
                        break;
                    case 1:
                        fprintf(tb_file,"%f%s", tb.registros[i].at->real, sep);
                        break;
                    case 2:
                        fprintf(tb_file,"%f%s", tb.registros[i].at->dupla, sep);
                        break;
                    case 3:
                        fprintf(tb_file,"%c%s", tb.registros[i].at->caractere, sep);
                        break;
                    case 4:
                        fprintf(tb_file,"%s%s", tb.registros[i].at->string, sep);
                        break;
                    default:
                        break;
                }
            }
            fprintf(tb_file,"\n");
        }
        
        fclose(tb_file);
        if (update_tables_config(tb) != 2) 
        {
            printf("Cancelando operação...\n");
            return -1;
        }
        
        return 2;
    }
    else
    {
        printf("ERRO: não foi possível abrir o arquivo da tabela %s\n", tb.nome_tb);
        printf("ERRO: %s\n", strerror(errno));
        return -1;
    }    
}

int update_tables_config(Tabela tb)
{
    FILE * tb_config;
    tb_config = fopen(tables_config, "r+");

    if (tb_config == NULL)
    {
        printf("ERRO: não foi possível abrir um arquivo essencial para o programa\nCaminho para o arquivo: tables/tables.config\n");
        printf("ERRO: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        char nome_tb_lida[MAX_NAME_LENGTH] = {0};
        char str_formatada[] = "%%s";
        strcat(str_formatada, sep);
        while (tb_config != EOF)
        {
            fscanf(tb_config, str_formatada, nome_tb_lida);
            if (strcmp(tb.nome_tb, nome_tb_lida) == 0)
            {
                fprintf(tb_config, "%s%s%i%s%i%s\n", tb.nome_tb, sep, tb.qte_at, sep, tb.qte_reg, sep);
                fclose(tb_config);
                return 2;
            }
        }
    }
    
    fprintf(tb_config, "%s%s%i%s%i%s\n", tb.nome_tb, sep, tb.qte_at, sep, tb.qte_reg, sep);
    fclose(tb_config);
    return 2;
}