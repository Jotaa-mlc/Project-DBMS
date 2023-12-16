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
            print_registro(tb->registros[i], tb->qte_at, tb->tipos_at);
    }
    free_tabela(tb);
}

void pesquisar_tabela()
{
    char * nome_tb;
    int comparacao = 0;
    unsigned int index_at = 0;
    int tb_ok = 0, at_ok = 0, cmp_ok = 0;
    Tabela * tb = NULL;
    Atributo item_pesquisa;

    while (!tb_ok)
    {
        printf("Em qual tabela deseja pesquisar?\n");
        nome_tb = get_nome_tabela(1);

        if (nome_tb != NULL)
            tb_ok = 1;
        else
            break;
    }

    if (tb_ok)
    {
        tb = carregar_tabela(nome_tb);

        while (!at_ok)
        {
            printf("Escolha um atributo dentre os listados abaixo para pesquisar.\n");
            //print atributos
            for (unsigned int i = 0; i < tb->qte_at; i++)
                printf("%u - %s\n", i, tb->nomes_at[i]);

            scanf("\n%u", &index_at);

            if (index_at < tb->qte_at)
                at_ok = 1;
            else
            {
                printf("Atributo inválido!\n");
                if (!try_again())
                    break;
            }
        }
    }

    if (at_ok)
    {
        printf("\nColuna %s - (%s) selecionada.\n", tb->nomes_at[index_at], tipos_list[tb->tipos_at[index_at]]);
        printf("Por qual valor deseja pesquisar?\n");

        switch (tb->tipos_at[index_at])
        {
            case 0:
                scanf("%d", &item_pesquisa.inteiro);
                break;
            case 1:
                scanf("%f", &item_pesquisa.real);
                break;
            case 2:
                scanf("%lf", &item_pesquisa.dupla);
                break;
            case 3:
                scanf("\n%c", &item_pesquisa.caractere);
                break;
            case 4:
                scanf("\n%s", item_pesquisa.string);
                break;
        }

        while (!cmp_ok)
        {
            comparacao = get_opcao_pesquisa();

            if (comparacao == 5 && tb->tipos_at[index_at] != 4)
            {
                printf("A opção de comparação selecionada só é válida para atributos do tipo string.\n");
                if (!try_again())
                {
                    printf("Cancelando operação...\n");
                    break;
                }
            }
            else
                cmp_ok = 1;
        }
    }

    if (cmp_ok)
    {
        printf("Resultados:\n");
        printf("%s | ", tb->nome_pk);
        for (unsigned int i = 0; i < tb->qte_at; i++) printf("%s | ", tb->nomes_at[i]);
        printf("\n");

        for (unsigned int i = 0; i < tb->qte_reg; i++)
        {
            int valido = 0;
            if (tb->tipos_at[index_at] != 4)//se não for string
            {
                double reg_tb = convert_at_double(tb->tipos_at[index_at], tb->registros[i].at[index_at]);
                double pesqui = convert_at_double(tb->tipos_at[index_at], item_pesquisa);
                
                switch (comparacao)
                {
                    case 0://>
                        valido = (reg_tb > pesqui) ? 1 : 0;
                        break;
                    case 1://>=
                        valido = (reg_tb >= pesqui) ? 1 : 0;
                        break;
                    case 2://=
                        valido = (reg_tb == pesqui) ? 1 : 0;
                        break;
                    case 3://<
                        valido = (reg_tb < pesqui) ? 1 : 0;
                        break;
                    case 4://<=
                        valido = (reg_tb <= pesqui) ? 1 : 0;
                        break;
                }
            }
            else
            {
                int result_strcmp = strcmp(tb->registros[i].at[index_at].string, item_pesquisa.string);
                switch (comparacao)
                {
                    case 0://>
                        valido = (result_strcmp > 0) ? 1 : 0;
                        break;
                    case 1://>=
                        valido = (result_strcmp > 0 || result_strcmp == 0) ? 1 : 0;
                        break;
                    case 2://=
                        valido = (result_strcmp == 0) ? 1 : 0;
                        break;
                    case 3://<
                        valido = (result_strcmp < 0) ? 1 : 0;
                        break;
                    case 4://<=
                        valido = (result_strcmp < 0 || result_strcmp == 0) ? 1 : 0;
                        break;
                    case 5://+/-
                        valido = (strstr(tb->registros[i].at[index_at].string, item_pesquisa.string) != NULL) ? 1 : 0;
                        break;
                }
            }
            
            if(valido)
                print_registro(tb->registros[i], tb->qte_at, tb->tipos_at);
        }
    }
    if (tb != NULL) free_tabela(tb);
}