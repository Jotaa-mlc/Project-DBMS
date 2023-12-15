#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "headers/tables_func.h"

void print_main_menu()//exibe o menu principal do programa
{
    printf("/----------------------------------------\\\n");
    printf("|            0 - Criar Tabela            |\n");
    printf("|            1 - Listar Tabelas          |\n");
    printf("|            2 - Inserir Registro        |\n");
    printf("|            3 - Exibir Tabela           |\n");
    printf("|            4 - Pesquisar               |\n");
    printf("|            5 - Excluir Registro        |\n");
    printf("|            6 - Excluir Tabela          |\n");
    printf("|            7 - Sair do DBSM            |\n");
    printf("\\----------------------------------------/\n");
}

int sair()//confirmação de saida
{
    char resposta = ' ';
    printf("Certeza que deseja deixar o programa?\nDigite 's' para confirmar\n");

    scanf("\n%c", &resposta);
    resposta = tolower(resposta);
    if(resposta == 's')
        return 1;
    else
        return 0;
    
}

int main()
{
    int logout = 0;
    int cmd;

    while (!logout)
    {
        print_main_menu();

        scanf("%d", &cmd);

        switch (cmd)
        {
            case 0://cria tabela
                criar_tabela();
                break;
            
            case 1://listar tabelas
                listar_tabelas();
                break;
            
            case 2://inserir registro
                inserir_registro();
                break;
            
            case 3://exibir tabela
                exibir_tabela();
                break;
            
            case 4://pesquisar
                pesquisar_tabela();
                break;
            
            case 5://excluir registro
                remover_registro();
                break;
            
            case 6://excluir tabela
                remover_tabela();
                break;
            
            case 7://sair do programa
                logout = sair();
                break;
            
            default:
                printf("Comando inválido!\nFavor insira um comando descrito no menu.\n");
                break;
        }
        printf("\n\n");
    }
    return 0;
}