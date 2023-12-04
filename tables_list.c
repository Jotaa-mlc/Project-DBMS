#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 250
#define MAX_REGISTROS 100

typedef enum { INTEGER, FLOAT, STRING } TipoAtributo;

typedef struct {
    union {
        int inteiro;
        float real;
        char string[MAX_NAME_LENGTH];
    } valor;
} Atributo;

typedef struct {
    unsigned int id;
    Atributo *at;
} Registro;

typedef struct {
    char *nome_tb;
    char **nomes_at;
    TipoAtributo *tipos_at;
    unsigned int qte_at, qte_reg;
    Registro *registros;
} Tabela;

void liberarMemoria(Tabela *tabela) {
    for (unsigned int i = 0; i < tabela->qte_at; i++) {
        free(tabela->nomes_at[i]);
    }
    free(tabela->nomes_at);

    for (unsigned int i = 0; i < tabela->qte_reg; i++) {
        free(tabela->registros[i].at);
    }
    free(tabela->registros);
    free(tabela->tipos_at);
}

void listarTabela(const char *nomeArquivo, const char *valorBuscado) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Tabela tabela;
    char buffer[MAX_NAME_LENGTH];

    if (fscanf(arquivo, "%s", buffer) != 1) {
        fprintf(stderr, "Erro ao ler o cabeçalho.\n");
        fclose(arquivo);
        return;
    }

    tabela.qte_at = 0;
    tabela.nomes_at = malloc(sizeof(char *));
    tabela.nomes_at[tabela.qte_at] = strdup(buffer);
    tabela.tipos_at = malloc(sizeof(TipoAtributo));

    while (fscanf(arquivo, ",%[^,\n]", buffer) == 1) {
        tabela.nomes_at = realloc(tabela.nomes_at, (tabela.qte_at + 1) * sizeof(char *));
        tabela.nomes_at[tabela.qte_at] = strdup(buffer);
        tabela.qte_at++;

        tabela.tipos_at = realloc(tabela.tipos_at, tabela.qte_at * sizeof(TipoAtributo));
        if (strcmp(buffer, "int") == 0) {
            tabela.tipos_at[tabela.qte_at - 1] = INTEGER;
        } else if (strcmp(buffer, "float") == 0) {
            tabela.tipos_at[tabela.qte_at - 1] = FLOAT;
        } else if (strcmp(buffer, "string") == 0) {
            tabela.tipos_at[tabela.qte_at - 1] = STRING;
        } else {
            fprintf(stderr, "Tipo de atributo não suportado: %s\n", buffer);
            fclose(arquivo);
            liberarMemoria(&tabela);
            return;
        }
    }

    tabela.registros = malloc(MAX_REGISTROS * sizeof(Registro));
    tabela.qte_reg = 0;

    while (fscanf(arquivo, "%u", &tabela.registros[tabela.qte_reg].id) == 1) {
        tabela.registros[tabela.qte_reg].at = malloc(tabela.qte_at * sizeof(Atributo));

        for (unsigned int j = 0; j < tabela.qte_at; j++) {
            switch (tabela.tipos_at[j]) {
            case INTEGER:
                if (fscanf(arquivo, ",%d", &tabela.registros[tabela.qte_reg].at[j].valor.inteiro) != 1) {
                    fprintf(stderr, "Erro ao ler o atributo %s do registro %u.\n", tabela.nomes_at[j], tabela.qte_reg + 1);
                    fclose(arquivo);
                    liberarMemoria(&tabela);
                    return;
                }
                break;
            case FLOAT:
                if (fscanf(arquivo, ",%f", &tabela.registros[tabela.qte_reg].at[j].valor.real) != 1) {
                    fprintf(stderr, "Erro ao ler o atributo %s do registro %u.\n", tabela.nomes_at[j], tabela.qte_reg + 1);
                    fclose(arquivo);
                    liberarMemoria(&tabela);
                    return;
                }
                break;
            case STRING:
                if (fscanf(arquivo, ",%[^,\n]", tabela.registros[tabela.qte_reg].at[j].valor.string) != 1) {
                    fprintf(stderr, "Erro ao ler o atributo %s do registro %u.\n", tabela.nomes_at[j], tabela.qte_reg + 1);
                    fclose(arquivo);
                    liberarMemoria(&tabela);
                    return;
                }
                break;
            }
        }

        tabela.qte_reg++;
    }

    printf("Registros:\n");
    for (unsigned int i = 0; i < tabela.qte_reg; i++) {
        printf("Registro %u:\n", i + 1);

        int registroEncontrado = 1;

        for (unsigned int j = 0; j < tabela.qte_at; j++) {
            printf("  Atributo: %s\t", tabela.nomes_at[j]);

            if (strncmp(tabela.nomes_at[j], valorBuscado, strlen(tabela.nomes_at[j])) != 0) {
                registroEncontrado = 0;
            } else {
                switch (tabela.tipos_at[j]) {
                case INTEGER:
                    if (tabela.registros[i].at[j].valor.inteiro != atoi(valorBuscado)) {
                        registroEncontrado = 0;
                    } else {
                        printf("Tipo: int\tValor: %d\n", tabela.registros[i].at[j].valor.inteiro);
                    }
                    break;
                case FLOAT:
                    if (tabela.registros[i].at[j].valor.real != atof(valorBuscado)) {
                        registroEncontrado = 0;
                    } else {
                        printf("Tipo: float\tValor: %f\n", tabela.registros[i].at[j].valor.real);
                    }
                    break;
                case STRING:
                    if (strcmp(tabela.registros[i].at[j].valor.string, valorBuscado) != 0) {
                        registroEncontrado = 0;
                    } else {
                        printf("Tipo: string\tValor: %s\n", tabela.registros[i].at[j].valor.string);
                    }
                    break;
                }
            }

            if (!registroEncontrado) {
                break;
            }
        }
    }

    liberarMemoria(&tabela);
    fclose(arquivo);
}

int main() {
    char nomeArquivo[MAX_NAME_LENGTH];

    char currentDir[MAX_NAME_LENGTH];
    if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
        printf("Diretório atual: %s\n", currentDir);
    } else {
        perror("Erro ao obter o diretório atual");
    }

    printf("Informe o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    char valorBuscado[MAX_NAME_LENGTH];
    printf("Informe o valor desejado: ");
    scanf(" %[^\n]", valorBuscado);

    listarTabela(nomeArquivo, valorBuscado);

    return 0;
}
