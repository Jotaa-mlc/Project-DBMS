#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/tables_func.h"
#include "headers/io_files.h"

extern char sep[];
extern char file_extension[];
extern char * tipos_list[];

void listar_tabelas()
{
    char buffer[MAX_NAME_LENGTH] = {0};
    int qte_tabelas = 0;

    FILE * tb_config = load_tb_config("r");

    printf("Listando tabelas:\n\n");

    while (fscanf(tb_config, "%s\n", buffer) != EOF)
    {
        strtok(buffer, sep);
        qte_tabelas++;
        printf("%i - %s\n", qte_tabelas, buffer);
    }

    fclose(tb_config);
}

void exibir_tabela()
{
    char * nome_tb;
    int tb_ok = 0;

    while (!tb_ok)
    {
        printf("Qual tabela deseja exibir?\n");
        nome_tb = get_nome_tabela(1);

        if (nome_tb != NULL)
            tb_ok = 1;
        else
        break;  
    }

    Tabela * tb = NULL;

    if (tb_ok)
    {
        tb = carregar_tabela(nome_tb);

        printf("Nome: %s\n\n", tb->nome_tb);

        //print cabeçalho
        printf("%s | ", tb->nome_pk);
        for (unsigned int i = 0; i < tb->qte_at; i++) printf("%s | ", tb->nomes_at[i]);
        printf("\n");

        for (unsigned int i = 0; i < tb->qte_reg; i++)
        {
            printf("%u | ", tb->registros[i].id);
            for (unsigned int j = 0; j < tb->qte_at; j++)
            {
                switch (tb->tipos_at[j])
                {
                    case 0:
                        printf("%d | ", tb->registros[i].at[j].inteiro);
                        break;
                    case 1:
                        printf("%f | ", tb->registros[i].at[j].real);
                        break;
                    case 2:
                        printf("%lf | ", tb->registros[i].at[j].dupla);
                        break;
                    case 3:
                        printf("%c | ", tb->registros[i].at[j].caractere);
                        break;
                    case 4:
                        printf("%s | ", tb->registros[i].at[j].string);
                        break;
                    default:
                        break;
                }
            }
            printf("\n");
        }
    }

    free_tabela(tb);
}