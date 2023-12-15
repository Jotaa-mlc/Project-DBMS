#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_COLUMNS 50
#define MAX_COLUMN_NAME_LENGTH 256
#define MAX_FILENAME_LENGTH 256
#define MAX_DATA_ROWS 1000

// Estrutura para armazenar os dados da coluna
typedef struct {
    char data[MAX_DATA_ROWS][MAX_COLUMN_NAME_LENGTH];
    int numRows;
} ColumnData;

// Protótipo da função
bool isStringColumn(char *data);

// Função para ler as colunas do arquivo CSV
void readColumns(FILE *file, char columns[MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH], int *numColumns) {
    char line[1024]; // Tamanho máximo da linha do arquivo
    *numColumns = 0;

    if (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL && *numColumns < MAX_COLUMNS) {
            strcpy(columns[*numColumns], token);
            (*numColumns)++;
            token = strtok(NULL, ",");
        }
    }
}

// Função para imprimir os dados de uma coluna específica e armazenar os valores
void printAndStoreColumnData(FILE *file, int columnNumber, int numColumns, ColumnData *columnData) {
    char line[1024];
    char *token;

    while (fgets(line, sizeof(line), file) != NULL) {
        int currentColumn = 0;
        token = strtok(line, ",");

        while (token != NULL && currentColumn < numColumns) {
            if (currentColumn == columnNumber - 1) {
                strcpy(columnData->data[columnData->numRows], token);
                columnData->numRows++;
                printf("%s\n", token);
                break;
            }

            currentColumn++;
            token = strtok(NULL, ",");
        }
    }
}

// Função para pesquisar valores na coluna
void searchColumnValues(ColumnData *columnData, int option, char *value) {
    switch (option) {
        case 1: // Valores maiores que o valor informado
            for (int i = 0; i < columnData->numRows; i++) {
                if (atoi(columnData->data[i]) > atoi(value)) {
                    printf("%s\n", columnData->data[i]);
                }
            }
            break;
        case 2: // Valores maiores ou iguais ao valor informado
            for (int i = 0; i < columnData->numRows; i++) {
                if (strcmp(columnData->data[i], value) >= 0) {
                    printf("%s\n", columnData->data[i]);
                }
            }
            break;
        case 3: // Valores iguais ao valor informado
            for (int i = 0; i < columnData->numRows; i++) {
                if (atoi(columnData->data[i]) == atoi(value)) {
                    printf("%s\n", columnData->data[i]);
                }
            }
            break;
        case 4: // Valores menores que o valor informado
            for (int i = 0; i < columnData->numRows; i++) {
                if (strcmp(columnData->data[i], value) < 0) {
                    printf("%s\n", columnData->data[i]);
                }
            }
            break;
        case 5: // Valores menores ou iguais ao valor informado
            for (int i = 0; i < columnData->numRows; i++) {
                if (atoi(columnData->data[i]) <= atoi(value)) {
                    printf("%s\n", columnData->data[i]);
                }
            }
            break;
        case 6: // Valores próximos ao valor informado (apenas para colunas do tipo string)
            if (isStringColumn(columnData->data[0])) {
                for (int i = 0; i < columnData->numRows; i++) {
                    if (strstr(columnData->data[i], value) != NULL) {
                        printf("%s\n", columnData->data[i]);
                    }
                }
            } else {
                fprintf(stderr, "Opção de pesquisa disponível apenas para colunas do tipo string.\n");
            }
            break;
        default:
            fprintf(stderr, "Opção de pesquisa inválida.\n");
    }
}

// Função para verificar se a coluna contém dados do tipo string
bool isStringColumn(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        if (!(data[i] >= '0' && data[i] <= '9') && data[i] != ' ') {
            return true; // Retorna true se encontrar algum caractere que não seja um número ou espaço
        }
    }
    return false; // Retorna false se todos os caracteres são números ou espaços
}

// Função para listar os arquivos CSV no diretório "../data_base"
void listCSVFiles() {
    DIR *dir;
    struct dirent *ent;
    int count = 1;

    if ((dir = opendir("../data_base/")) != NULL) {
        printf("Arquivos CSV disponíveis no diretório 'data_base':\n");
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".csv") != NULL) {
                printf("%d - %s\n", count, ent->d_name);
                count++;
            }
        }
        closedir(dir);
    } else {
        perror("Erro ao abrir o diretório");
        exit(EXIT_FAILURE);
    }
}

int main() {
    listCSVFiles();

    char filename[MAX_FILENAME_LENGTH];
    printf("Digite o nome do arquivo CSV desejado: ");
    scanf("%s", filename);

    char filepath[MAX_FILENAME_LENGTH + 3]; // Tamanho do nome do arquivo + "../" + '\0'
    snprintf(filepath, sizeof(filepath), "../data_base/%s", filename);

    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filepath);
        return 1;
    }

    char columns[MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH];
    int numColumns;

    // Lê as colunas do arquivo CSV e imprime os dados
    readColumns(file, columns, &numColumns);

    // Exibe as colunas
    printf("Colunas disponíveis:\n");
    for (int i = 0; i < numColumns; i++) {
        printf("%d. %s\n", i + 1, columns[i]);
    }

    // Solicita a seleção da coluna
    int selectedColumn;
    printf("Selecione o número da coluna para exibir os dados: ");
    scanf("%d", &selectedColumn);

    // Verifica se a seleção é válida
    if (selectedColumn < 1 || selectedColumn > numColumns) {
        fprintf(stderr, "Seleção inválida.\n");
        fclose(file);
        return 1;
    }

    // Reposiciona o cursor do arquivo para o início dos dados
    fseek(file, 0, SEEK_SET);

    // Pula a linha de cabeçalho
    fgets(columns[0], sizeof(columns[0]), file);

    // Exibe os dados da coluna escolhida
    printf("Dados da coluna \"%s\":\n", columns[selectedColumn - 1]);

    // Inicializa a estrutura para armazenar os dados da coluna
    ColumnData columnData;
    columnData.numRows = 0;

    // Lê e armazena os dados da coluna escolhida
    printAndStoreColumnData(file, selectedColumn, numColumns, &columnData);

    // Exibe as opções de pesquisa
    printf("\nOpções de pesquisa:\n");
    printf("1. Valores maiores que o valor informado\n");
    printf("2. Valores maiores ou iguais ao valor informado\n");
    printf("3. Valores iguais ao valor informado\n");
    printf("4. Valores menores que o valor informado\n");
    printf("5. Valores menores ou iguais ao valor informado\n");
    printf("6. Valores próximos ao valor informado (apenas para colunas do tipo string)\n");

    // Solicita a opção de pesquisa
    int searchOption;
    printf("Selecione a opção de pesquisa: ");
    scanf("%d", &searchOption);

    // Solicita o valor para pesquisa
    char searchValue[MAX_COLUMN_NAME_LENGTH];
    printf("Digite o valor para pesquisa: ");
    scanf("%s", searchValue);

    // Realiza a pesquisa na coluna
    searchColumnValues(&columnData, searchOption, searchValue);

    fclose(file);

    return 0;
}