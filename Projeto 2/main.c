#include "function.h"

int main() {
    FILE* arquivo_leitura;
    FILE* arquivo_saida;

    char linha[50];
    char cmd[10];
    int valor;
    int grau_t;

    printf("Digite o grau minimo t da Arvore B (minimo 2): ");
    scanf("%d", &grau_t);

    BTree* arvore = create_tree(grau_t);
    if (arvore == NULL) {
        printf("Erro ao criar a arvore B com o grau %d\n", grau_t);
        return 1;
    }

    int escolha = 0;

    while (1) {

        printf("\nEscolha uma opcao:\n");
        printf("1 - Ler operacoes do arquivo\n");
        printf("2 - Escrever operacoes no arquivo\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);

        // Modo leitura: executa comandos do arquivo operacoes.txt
        if (escolha == 1) {

            arquivo_leitura = fopen("operacoes.txt", "r");
            if (!arquivo_leitura) {
                printf("Erro ao abrir operacoes.txt para leitura!\n");
                continue;
            }

            while (fgets(linha, sizeof(linha), arquivo_leitura)) {

                linha[strcspn(linha, "\n")] = 0;
                int tipo = ler_comando_insert_search(linha, &valor);

                if (tipo == 1) {
                    printf("Executando: INSERT %d\n", valor);
                    btree_insert(arvore, valor);
                }
                else if (tipo == 2) {
                    printf("Executando: SEARCH %d\n", valor);

                    if (arvore->root_id == -1) {
                        printf("Resultado: Arvore vazia\n");
                    } else {
                        if (btree_search(arvore, arvore->root_id, valor))
                            printf("Resultado: Encontrado\n");
                        else
                            printf("Resultado: Nao encontrado\n");
                    }
                }
                else {
                    printf("Linha invalida: %s\n", linha);
                }

                printf("[IO] Leituras: %d | Escritas: %d\n", CONTA_LEITURA, CONTA_ESCRITA);
                CONTA_LEITURA = 0;
                CONTA_ESCRITA = 0;
            }

            fclose(arquivo_leitura);

            printf("\nArvore atual:\n");
            if (arvore->root_id != -1)
                imprimir_arvore(arvore->root_id, 0);
            else
                printf("Arvore vazia\n");
        }
        // Modo escrita: permite adicionar um comando ao arquivo operacoes.txt
        else if (escolha == 2) {

            while (1) {

                arquivo_saida = fopen("operacoes.txt", "a");
                if (!arquivo_saida) {
                    printf("Erro ao abrir arquivo!\n");
                    break;
                }

                printf("Digite o comando (INSERT ou SEARCH): ");
                scanf("%9s", cmd);

                printf("Digite o valor: ");
                scanf("%d", &valor);

                int tipo = identificar_comando(cmd);

                if (tipo == 1) {
                    EscreverInsert(arquivo_saida, valor);
                    printf("Executando: INSERT %d\n", valor);
                    btree_insert(arvore, valor);
                }
                else if (tipo == 2) {
                    EscreverSearch(arquivo_saida, valor);
                    printf("Executando: SEARCH %d\n", valor);

                    if (arvore->root_id == -1) {
                        printf("Resultado: Arvore vazia\n");
                    } else {
                        if (btree_search(arvore, arvore->root_id, valor))
                            printf("Resultado: Encontrado\n");
                        else
                            printf("Resultado: Nao encontrado\n");
                    }
                }
                else {
                    printf("Comando invalido!\n");
                }

                fclose(arquivo_saida);

                printf("[IO] Leituras: %d | Escritas: %d\n\n", CONTA_LEITURA, CONTA_ESCRITA);
                CONTA_LEITURA = 0;
                CONTA_ESCRITA = 0;

                int continuar;
                printf("Deseja continuar escrevendo? (1-Sim / 2-Nao): ");
                scanf("%d", &continuar);

                if (continuar != 1)
                    break;
            }

            printf("\nArvore atual:\n");
            if (arvore->root_id != -1)
                imprimir_arvore(arvore->root_id, 0);
            else
                printf("Arvore vazia\n");
        }

        else if (escolha == 3) {
            printf("Saindo...\n");
            break;
        }

        else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
