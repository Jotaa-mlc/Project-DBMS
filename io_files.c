#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
 
#include "headers/definitions.h"
#include "headers/io_files.h"

char sep[] = "|#@!";//separador dos atributos das tabelas
char file_extension[] = ".itp";
char tables_folder_path[] = "tables/";
char tables_config[] = "tables/tables.config";

/**
 * Cria/sobreescreve o arquivo da tabela indicada
 * 
 * @return 2: sucesso; -1: erro ao abrir o arquivo;
*/
int arquivar_tabela(Tabela *tb)
{
    FILE * tb_file;
    tb_file = load_tb_file(tb->nome_tb, "w");

    if (tb_file != NULL)
    {
        fprintf(tb_file,"%s%s", tb->nome_pk, sep);

        for (unsigned int i = 0; i < tb->qte_at; i++)//insere os atributos no cabeçalho do arquivo
        {
            fprintf(tb_file,"%s%s%i%s", tb->nomes_at[i], sep, tb->tipos_at[i], sep);
        }
        fprintf(tb_file,"\n");
        
        for (unsigned int i = 0; i < tb->qte_reg; i++)//insere os registros
        {
            fprintf(tb_file,"%u%s", tb->registros[i].id, sep);
            for (unsigned int j = 0; j < tb->qte_at; j++)
            {
                switch (tb->tipos_at[j])
                {
                    case 0:
                        fprintf(tb_file,"%d%s", tb->registros[i].at[j].inteiro, sep);
                        break;
                    case 1:
                        fprintf(tb_file,"%f%s", tb->registros[i].at[j].real, sep);
                        break;
                    case 2:
                        fprintf(tb_file,"%lf%s", tb->registros[i].at[j].dupla, sep);
                        break;
                    case 3:
                        fprintf(tb_file,"%c%s", tb->registros[i].at[j].caractere, sep);
                        break;
                    case 4:
                        fprintf(tb_file,"%s%s", tb->registros[i].at[j].string, sep);
                        break;
                    default:
                        break;
                }
            }
            fprintf(tb_file,"\n");
        }
        
        fclose(tb_file);
        update_tables_config(tb, 0);
        return 2;
    }
    else
    {
        printf("ERRO: não foi possível abrir o arquivo da tabela %s\n", tb->nome_tb);
        printf("ERRO: %s\n", strerror(errno));
        return -1;
    }    
}

Tabela * carregar_tabela(char *nome_tb)
{
    unsigned int qte_reg = 0, qte_at = 0;
    char *buffer = calloc(MAX_NAME_LENGTH, sizeof(char));

    FILE * tb_config = load_tb_config("r");
    //busca pelo nome da tabela e lê qte_at && qte_reg
    while (fscanf(tb_config, "%s\n", buffer) != EOF)
    {
        strtok(buffer, sep);
        if (strcmp(nome_tb, buffer) == 0)
        {
            strcpy(buffer, strtok(NULL, sep));
            sscanf(buffer, "%u", &qte_at);
            strcpy(buffer, strtok(NULL, sep));
            sscanf(buffer, "%u", &qte_reg);
            break;
        }
        memset(buffer, 0, MAX_NAME_LENGTH);
    }

    memset(buffer, 0, MAX_NAME_LENGTH);
    
    Tabela *tb = alocar_tabela(qte_at, qte_reg);
    
    strcpy(tb->nome_tb, nome_tb);
    
    FILE * tb_file =  load_tb_file(nome_tb, "r");
    //Lê os nomes dos atributos e seus tipos
    fscanf(tb_file, "%s\n", buffer);
    char * slice = strtok(buffer, sep);
    strcpy(tb->nome_pk, slice);
    slice = strtok(NULL, sep);
    for (unsigned int i = 0; i < qte_at; i++)
    {   
        strcpy(tb->nomes_at[i], slice);
        slice = strtok(NULL, sep);
        sscanf(slice, "%i", &tb->tipos_at[i]);
        slice = strtok(NULL, sep);
    }

    memset(buffer, 0, MAX_NAME_LENGTH);
    
    //Lê os registros com base nos tipos de atributos
    for (unsigned int i = 0; i < qte_reg; i++)
    {
        fscanf(tb_file, "%s\n", buffer);
        slice = strtok(buffer, sep);
        sscanf(slice, "%u", &tb->registros[i].id);

        for (unsigned int j = 0; j < qte_at; j++)
        {
            slice = strtok(NULL, sep);
            switch (tb->tipos_at[j])
            {
                case 0:
                    sscanf(slice,"%d", &tb->registros[i].at[j].inteiro);
                    break;
                case 1:
                    sscanf(slice,"%f", &tb->registros[i].at[j].real);
                    break;
                case 2:
                    sscanf(slice,"%lf", &tb->registros[i].at[j].dupla);
                    break;
                case 3:
                    sscanf(slice,"%c", &tb->registros[i].at[j].caractere);
                    break;
                case 4:
                    sscanf(slice,"%s", tb->registros[i].at[j].string);
                    break;
                default:
                    break;
            }
        }
    }

    free(nome_tb);
    free(buffer);
    fclose(tb_config);
    fclose(tb_file);
    
    return tb;
}

void remover_arq_tb(Tabela * tb)
{
    char tb_file_path[MAX_NAME_LENGTH] = {0};
    strcpy(tb_file_path, tables_folder_path);
    strcat(tb_file_path, tb->nome_tb);
    strcat(tb_file_path, file_extension);

    update_tables_config(tb, 1);
    remove(tb_file_path);
}