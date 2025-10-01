#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------- FUNÇÕES DE SUPORTE -----------
// Gera um número aleatório no intervalo [0, 999]
int gerarChave() {
    return rand() % 1000;
}

// Ordena um vetor com Selection Sort
void selectionSort(int *vet, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vet[i] > vet[j]) {
                int tmp = vet[i];
                vet[i] = vet[j];
                vet[j] = tmp;
            }
        }
    }
}

// Salva um vetor de inteiros em um arquivo
void salvarBloco(const char *nomeArquivo, int *vet, int n) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao criar bloco!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", vet[i]);
    }
    fclose(fp);
}

// ----------- ETAPA 1: GERAR ARQUIVO DE TESTE -----------
void gerarArquivo(const char *nomeArquivo, int n) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    srand(time(NULL)); // inicializa aleatórios
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", gerarChave());
    }

    fclose(fp);
    printf("Arquivo '%s' criado com %d chaves.\n", nomeArquivo, n);
}

// ----------- ETAPA 2: CRIAR BLOCOS ORDENADOS -----------
int criarBlocos(const char *nomeArquivo, int tamanhoBloco) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir arquivo de entrada!\n");
        exit(1);
    }

    int *buffer = malloc(tamanhoBloco * sizeof(int));
    if (!buffer) {
        printf("Erro de memória!\n");
        exit(1);
    }

    int count, bloco = 0;
    while (1) {
        count = 0;
        while (count < tamanhoBloco && fscanf(fp, "%d", &buffer[count]) == 1) {
            count++;
        }
        if (count == 0) break; // fim do arquivo

        selectionSort(buffer, count);

        char nomeBloco[30];
        sprintf(nomeBloco, "bloco%d.txt", bloco++);
        salvarBloco(nomeBloco, buffer, count);
    }

    free(buffer);
    fclose(fp);
    printf("%d blocos criados.\n", bloco);
    return bloco;
}

// ----------- ETAPA 3: INTERCALAR BLOCOS (K-WAY MERGE) -----------
void abrirBlocos(FILE **blocos, int *valores, int *ativos, int numBlocos) {
    for (int i = 0; i < numBlocos; i++) {
        char nome[30];
        sprintf(nome, "bloco%d.txt", i);
        blocos[i] = fopen(nome, "r");
        if (fscanf(blocos[i], "%d", &valores[i]) == 1) {
            ativos[i] = 1;
        } else {
            ativos[i] = 0;
        }
    }
}

int encontrarMenor(int *valores, int *ativos, int numBlocos) {
    int menor = 9999999;
    int idx = -1;
    for (int i = 0; i < numBlocos; i++) {
        if (ativos[i] && valores[i] < menor) {
            menor = valores[i];
            idx = i;
        }
    }
    return idx;
}

void intercalarBlocos(int numBlocos, const char *saidaFinal) {
    FILE *blocos[numBlocos];
    int valores[numBlocos];
    int ativos[numBlocos];

    abrirBlocos(blocos, valores, ativos, numBlocos);

    FILE *saida = fopen(saidaFinal, "w");
    if (!saida) {
        printf("Erro ao criar arquivo final!\n");
        exit(1);
    }

    while (1) {
        int idx = encontrarMenor(valores, ativos, numBlocos);
        if (idx == -1) break;

        fprintf(saida, "%d\n", valores[idx]);
        if (fscanf(blocos[idx], "%d", &valores[idx]) != 1) {
            ativos[idx] = 0;
        }
    }

    for (int i = 0; i < numBlocos; i++) fclose(blocos[i]);
    fclose(saida);

    printf("Arquivo final '%s' criado com sucesso.\n", saidaFinal);
}

void visualizarEntrada(){
    int valor;
    FILE *arquivo = fopen("entrada.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(1);
    }
    printf("Conteudo de entrada.txt:\n");
    while (fscanf(arquivo, "%d", &valor) == 1) {
        printf("%d\n", valor);
    }
    fclose(arquivo);
}

void visualizarSaida(){
    int valor;
    FILE *arquivo = fopen("saida.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de saida!\n");
        return;
    }
    printf("Conteudo de saida.txt:\n");
    while (fscanf(arquivo, "%d", &valor) == 1) {
        printf("%d\n", valor);
    }
    fclose(arquivo);
}

void visualizarBlocoEspec(){
    int blocoDef, valor;
    char qualBloco[25];
    printf("Digite qual bloco deseja visualizar: ");
    scanf("%d", &blocoDef);
    sprintf(qualBloco, "bloco%d.txt", blocoDef);
    FILE *arquivo = fopen(qualBloco, "r");
    if (!arquivo) {
        printf("Erro ao abrir o bloco %d!\n", blocoDef);
        return;
    }
    printf("Conteudo de %s:\n", qualBloco);
    // lê cada número do arquivo até o fim
    while (fscanf(arquivo, "%d", &valor) == 1) {
        printf("%d\n", valor);
    }

    fclose(arquivo);

}
void menu(){
        printf("--------------------------------------------\n");
        printf("Menu:\n");
        printf("--------------------------------------------\n");
        printf("1. Visualizar a entrada\n");
        printf("2. Visualizar a saida\n");
        printf("3. Visualizar um bloco especifico\n");
        printf("4. Sair\n");
        printf("--------------------------------------------\n\n");
}

// ----------- MAIN -----------
int main() {
    int n = 150;           // número total de registros
    int tamanhoBloco = 10; // tamanho de cada bloco
    int opcao;

    printf("--------------------------------------------\n");
    gerarArquivo("entrada.txt", n);
    int numBlocos = criarBlocos("entrada.txt", tamanhoBloco);
    intercalarBlocos(numBlocos, "saida.txt");
    do
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    switch (opcao) {
            case 1:
                system("cls");
                visualizarEntrada();
                system("Pause");
                system("cls");
                break;
            case 2:
                system("cls");
                visualizarSaida();
                system("Pause");
                system("cls");
                break;
            case 3:
                system("cls");
                visualizarBlocoEspec();
                system("Pause");
                system("cls");
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                system("Pause");
                system("cls");
        }
    } while (opcao != 4);

    return 0;
}