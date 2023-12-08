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

int sair()//confirmação de saido
{
    char resposta = ' ';
    printf("Certeza que deseja deixar o programa?\nDigite 's' para confirmar\n");

    scanf("\n%c", &resposta);
    resposta = tolower(resposta);
    if(resposta == 's'){
        return 1;
    }else{
        return 0;
    }
}

int main()
{
    int logout = 0;
    int cmd;

    while (!logout)
    {
        system("clear");
        fflush(stdin);
        print_main_menu();

        scanf("%d", &cmd);

        switch (cmd)
        {
            case 0://cria tabela
                criar_tabela();
                break;
            
            case 1://listar tabelas
                /* code */
                break;
            
            case 2://inserir registro
                inserir_registro();
                break;
            
            case 3://exibir tabela
                /* code */
                break;
            
            case 4://pesquisar
                /* code */
                break;
            
            case 5://excluir registro
                /* code */
                break;
            
            case 6://excluir tabela
                /* code */
                break;
            
            case 7://sair do programa
                logout = sair();
                break;
            
            default:
                printf("Comando inválido!\nFavor insira um comando descrito no menu.\n");
                break;
        }
    }

    return 0;
}